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
 * More information at the Github page:  https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x
 *******************************************************************************************************
 */

#ifndef SRC_RFMODSTM32F4X_H_
#define SRC_RFMODSTM32F4X_H_

/*
 *****************************************************************************************************************************
 *Adaptado de RH_ASK.h
 *****************************************************************************************************************************
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

//definições de tamanhos dos pacotes.
#define TAM_MAX_PACOTE 67
#define TAM_MAX_MSG (TAM_MAX_PACOTE - 3)

//definições de amostragem e para a rampa do RX
#define AMOSTRAS_POR_BIT 8
#define COMP_RAMPA 160
#define INCR_RAMPA (COMP_RAMPA/AMOSTRAS_POR_BIT)
#define TRANSICAO_RAMPA COMP_RAMPA/2
#define AJUSTE_RAMPA 9
#define INCR_RAMPA_ATRASO (INCR_RAMPA - AJUSTE_RAMPA)
#define INCR_RAMPA_AVANCO (INCR_RAMPA + AJUSTE_RAMPA)

//bytes do preambulo: 36 bits de treinamento + 12 bits de início
#define TAM_PREAMBULO 8

bool disponivel();

bool recb(uint8_t* buf, uint8_t* len);

bool envia(const uint8_t* data, uint8_t len);

void poeModoTx();

void poeModoRx();

void poeModoParado();

//traduz o símbolo de 6 bits para o nibble de 4 bits
uint8_t simbolo_para_nibble(uint8_t simbolo);

//função que executa a cada estouro do timer se em modo Rx
void TimerRecb();

//função que executa a cada estouro do timer se em modo Tx
void TimerEnvia();

//deve ser colocada na rotina de interrupção do timer de amostragem
void TimerRotinaInterrupcao();

//função que confere se o CRC deu certo
void validaRxBuf();
//depuração---------------
//uint8_t marca;
//------------------------

//flags de leitura e de escrita
volatile bool _rxBufCheio;

volatile bool _rxBufValido;

volatile bool _rxUltAmostra; //ultima amostra

volatile uint8_t _rxIntegrador;

volatile uint8_t _rxRampa;

volatile uint8_t _rxAtivo;
//ultimos 12 bits recebidos pra ver simbolo de inicio
volatile uint16_t _rxBits;

volatile uint8_t _rxBitCount;
//onde fica guardada a mensagem recebida
uint8_t _rxBuf[TAM_MAX_PACOTE];
//tamanho esperado da mensagem
volatile uint8_t _rxCount;
//tamanho do buffer de recebimento até o momento
volatile uint8_t _rxBufTam;

uint8_t _txIndex;

uint8_t _txBit;

uint8_t _txAmostra;

uint8_t _txBuf[(TAM_MAX_PACOTE * 2) + TAM_PREAMBULO];

uint8_t _txBufTam;

/*
 *****************************************************************************************************************************
 *Adaptado de RHGenericDriver.h
 *****************************************************************************************************************************
 */

typedef enum
{
ModoParado,
ModoTx,
ModoRx,
} Modo;

bool Inicia_Mod_RF();//coloca o preâmbulo (bits de treino + palavra de início) no _txBuf e ModoParado

bool esperaEnvio();
//não implementado - diagnóstico do buffer. buf seleciona o buffer
//static void printBuffer(const char* prompt, const uint8_t* buf, uint8_t len);

uint16_t _txBom;

uint16_t _rxBom;

uint16_t _rxRuim;

volatile Modo _modo;

uint16_t rxRuim();

uint16_t rxBom();

uint16_t txBom();


/*
 *****************************************************************************************************************************
 *Adaptado de RHCRC.h
 *****************************************************************************************************************************
 */
extern uint16_t atualiza_crc_xmodem(uint16_t crc, uint8_t data);

#endif /* SRC_RFMODSTM32F4X_H_ */
