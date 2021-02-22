/*******************************************************************************************************
 * file			: RFModSTM32f4x.h
 * API name 	: Radio Frequency Module for STM32F4x API
 * API files	: RFModSTM32f4x.h and RFModSTM32f4x.c
 * date 		: 02/22/2021
 * author		: Gabriel Pimentel Gomes
 * license		: GNU General Public License v3.0
 * university	: Universidade Federal de Minas Gerais (UFMG) - Brazil
 *
 * This API was an assignment for UFMG's course "Embbedded Systems Programing"
 * instructed by Prof. Ricardo de Oliveira Duarte -
 * - Departamento de Engenharia Eletrônica (Electronics Engineering)
 *
 * API inspired in RadioHead's library made by AirSpace Pty Ltd. Copyright (C) 2011-2020 Mike McCauley
 *******************************************************************************************************
 * API hardware and software requisites:
 *
 * STMicroelectronics' nucleo64 STM32F401 kit (code can be adapted to other kits)
 * 433MHz RF module Model MX-FS-03V(transmitter) e MX-05V(receiver) or similar
 * Computer capable of executing STM32CubeMX, System Workbench for STM32 and RealTerm
 *******************************************************************************************************
 * Reminder:
 * You must include "RFModSTM32f4x.h" in both 'main.c' and 'stm32f4xx_it.c'
 *******************************************************************************************************
 * More information at the Github page: https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x
 *******************************************************************************************************
 */
#include "RFModSTM32f4x.h"

/*
 *****************************************************************************************************************************
 *Adaptado de RH_ASK.cpp
 *****************************************************************************************************************************
 */
#define SIMBOLO_INICIO 0xb38
//tradução de 4bits para símbolo de 6bits
static uint8_t simbolos[] =
{
		0xd,  0xe,  0x13, 0x15, 0x16, 0x19, 0x1a, 0x1c,
		0x23, 0x25, 0x26, 0x29, 0x2a, 0x2c, 0x32, 0x34
};

/*Aqui deve-se ter o microcontrolador com um timer de 16kHz
 * para amostragem de 8 vezes por bit. A velocidade de
 * transmissão é de 2kbs
 */


void poeModoTx()
{
	if (_modo != ModoTx)
	{
		//zera os contadores de controle de envio
		_txIndex = 0;
		_txBit = 0;
		_txAmostra = 0;

		_modo = ModoTx;
	}
}

void poeModoRx()
{
	if (_modo != ModoRx)
	{
		HAL_GPIO_WritePin(Tx_RF_GPIO_Port, Tx_RF_Pin, 0);
		_modo = ModoRx;
	}
}

void poeModoParado()
{
	if (_modo != ModoParado)
	{
		HAL_GPIO_WritePin(Tx_RF_GPIO_Port, Tx_RF_Pin, 0);
		_modo = ModoParado;
	}
}

bool disponivel()
{
	if(_modo == ModoTx)
		return false;
	poeModoRx();
	if(_rxBufCheio)
	{
		validaRxBuf();
		_rxBufCheio= false;
	}
	return _rxBufValido;
}

bool recb(uint8_t* buf, uint8_t* len)
{
	if(!disponivel())
		return false;
	if(buf && len)
	{
		uint8_t tam_msg = _rxBufTam - 3;
		if(*len > tam_msg)
			*len = tam_msg;
	memcpy(buf, _rxBuf+1, *len);
	}
	_rxBufValido = false;
	return true;
}

bool envia (const uint8_t* data, uint8_t len)
{
	uint8_t i;
	uint16_t index = 0;
	uint16_t crc = 0xffff;
	uint8_t *p = _txBuf + TAM_PREAMBULO;
	uint8_t count = len + 3;

	if(len > TAM_MAX_MSG)
		return false;

	esperaEnvio();

	//codifica o tamanho da mensagem passando de 4bits para 6 bits
	crc = atualiza_crc_xmodem(crc, count);
	p[index++] = simbolos[count >> 4];
	p[index++] = simbolos[count & 0xf];

	//codifica a mensagem
	for(i=0; i<len; i++)
	{
		crc = atualiza_crc_xmodem(crc,data[i]);
		p[index++] = simbolos[data[i] >> 4];
		p[index++] = simbolos[data[i] & 0xf];
	}

	//codifica o crc
	p[index++] = simbolos[(crc >> 12) & 0xf];
	p[index++] = simbolos[(crc >> 8) & 0xf];
	p[index++] = simbolos[(crc >> 4) & 0xf];
	p[index++] = simbolos[crc & 0xf];

	//Cada simbolo de 6bits guardado em um byte,
	//número de simbolos para enviar
	_txBufTam = index + TAM_PREAMBULO;

	//liga o hardware para enviar
	poeModoTx();
	return true;
}

uint8_t simbolo_para_nibble(uint8_t simbolo)
{
	uint8_t i;
	uint8_t count;

	//busca linear, mas como o bit 5 da segunda metade é 1,
	//já da pra pesquisar só uma metade

	for (i = (simbolo>>2) & 8, count = 8; count-- ; i++)
		if(simbolo == simbolos[i]) return i;

	return -1;//não encontrou
}

void validaRxBuf()
{
	uint16_t crc = 0xffff;
	//o crc vai desde a contagem de bytes até o CRC anexado
	for(uint8_t i = 0; i < _rxBufTam; i++)
		crc = atualiza_crc_xmodem(crc, _rxBuf[i]);
	if(crc != 0)//espera-se que o crc seja zero
	{
		_rxRuim++;
		_rxBufValido = false;
		return;
	}
	_rxBom++;
	_rxBufValido = true;
}

void TimerRecb()
{

	bool rxAmostra;
	rxAmostra = HAL_GPIO_ReadPin(Rx_RF_GPIO_Port, Rx_RF_Pin);
	//depuração---------------
	//marca = 0;
	//------------------------

	if (rxAmostra)
		_rxIntegrador++;
	if (rxAmostra != _rxUltAmostra)
	{
	//quando o sinal mudou de estado, tem que reavaliar a sincronia
		if(_rxRampa < TRANSICAO_RAMPA)
			_rxRampa += INCR_RAMPA_ATRASO;
		else
			_rxRampa += INCR_RAMPA_AVANCO;
		_rxUltAmostra = rxAmostra;
	}
	else
		_rxRampa += INCR_RAMPA;

	if(_rxRampa >= COMP_RAMPA)//terminou o periodo de um bit
	{
		_rxBits >>= 1;
		// se a média for mais próxima de 1, o bit lido é 1
		if(_rxIntegrador >= 5)
			_rxBits |= 0x800;

		_rxRampa -= COMP_RAMPA;
		_rxIntegrador = 0;
		//depuração-------------------------------------
		//marca = 1;

		//----------------------------------------------

		if(_rxAtivo)
		{
		//já recebeu o símbolo de início, o que tá chegando é dado
			if(++_rxBitCount >= 12)
			{
				//12 bits = 2 sibolos de 6 = 1 byte de dado
				//6 lsb do símbolo chegaram primeiro, são o high nibble do byte
				uint8_t this_byte =
						(simbolo_para_nibble(_rxBits & 0x3f) << 4)
						| simbolo_para_nibble(_rxBits >> 6);
				//depuração-------------------------------------
				marca = 2; //recebi o byte de cima!

				//----------------------------------------------
				//se for o primeiro byte, ele é o número de bytes na mensagem
				if(_rxBufTam == 0)
				{
					_rxCount = this_byte;
					if(_rxCount < 4 || _rxCount > TAM_MAX_PACOTE)
					{
						//tamanhos menores que o mínimo e maiores que o máximo
						_rxAtivo = false;
						_rxRuim++;
						return;
					}
				}
				_rxBuf[_rxBufTam++] = this_byte;

				if(_rxBufTam >= _rxCount)
				{
					//já leu todos os bytes
					_rxAtivo = false;
					_rxBufCheio = true;
					poeModoParado();
				}
				_rxBitCount = 0;
			}
		}
		//se não estiver dentro de uma mensagem, só aguardando
		else if(_rxBits == SIMBOLO_INICIO)
		{
		//recebeu um síbolo de início
			//depuração-------------------------------------
			//marca = 3; //início!

			//----------------------------------------------
			_rxAtivo = true;
			_rxBitCount = 0;
			_rxBufTam = 0;
		}
	}
}

void TimerEnvia()
{
	if(_txAmostra++ == 0)//contador para esperar 8 amostras
	{
		if(_txIndex >= _txBufTam)//se terminou de mandar
		{
			poeModoParado();
			_txBom++;
		}
		else
		{
			bool  sinal;
			sinal = (_txBuf[_txIndex] & (1 << _txBit++));
			HAL_GPIO_WritePin(Tx_RF_GPIO_Port, Tx_RF_Pin, sinal);
			if(_txBit >= 6)
			{
				_txBit = 0;
				_txIndex++;
			}
		}
	}
	if(_txAmostra > 7)
		_txAmostra = 0;
}

//chamar essa função dentro da rotina de interrupção do timer
void TimerRotinaInterrupcao()
{
	if(_modo == ModoRx)
		TimerRecb();
	else if (_modo == ModoTx)
		TimerEnvia();
}

/*
 *****************************************************************************************************************************
 *Adaptado de RHGenericDriver.cpp
 *****************************************************************************************************************************
 */

bool Inicia_Mod_RF()
{
	 uint8_t preambulo[TAM_PREAMBULO] = {0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x38, 0x2c};
	 memcpy(_txBuf, preambulo, sizeof(preambulo));//inicia o _txbuf colocando o preambulo
	 _modo = ModoParado;
	return true;
}

bool esperaEnvio()
{
	while(_modo == ModoTx)//fica aqui até terminar a transmissão
	{
	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	//HAL_Delay(2000);
	}
	return true;
}

uint16_t rxRuim()
{
    return _rxRuim;
}

uint16_t rxBom()
{
    return _rxBom;
}

uint16_t txBom()
{
    return _txBom;
}

/*
 *****************************************************************************************************************************
 *Adaptado de RHCRC.c
 *****************************************************************************************************************************
 */

uint16_t atualiza_crc_xmodem(uint16_t crc, uint8_t data)
{
    //padrão crc xmodem ou ccitt, mas parece que ccitt é um nome errado
	//será usado com resto inicial crc = 0xffff
	//polinomio truncado = 0x1021
	//16 bits de crc
	//pega um byte e atualiza o crc com esse byte que foi "encaixado" na palavra
	int i;

    crc = crc ^ ((uint16_t)data << 8);
    for (i=0; i<8; i++)
    {
	if (crc & 0x8000)
	    crc = (crc << 1) ^ 0x1021;
	else
	    crc <<= 1;
    }

    return crc;
}

