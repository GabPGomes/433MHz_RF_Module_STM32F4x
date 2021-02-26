/*
 * RFModSTM32f4x.h da API Módulo Rádio Frequência para STM32F4x
 * A API contém: RFModSTM32f4x.h e RFModSTM32f4x.c
 *
 * 16/02/2021
 * Universidade Federal de Minas Gerais
 * Autor: Gabriel Pimentel Gomes
 *
 * Requisitos para uso da API:
 * Kit nucleo64 STM32F401 da STMicroelectronics (para usar outros kits é necessário adaptar o código)
 * Módulo RF 433MHz Modelo MX-FS-03V(transmissor) e MX-05V(receptor) ou similar
 * Computador com portas USB e capaz de executar os seguintes programas:
 * STM32CubeMX e SWB4STM32 (System Workbench for STM32)
 *
 * Esta API foi desenvolvida como trabalho da disciplina de Programação de Sistemas Embarcados da UFMG -
 * Prof. Ricardo de Oliveira Duarte - Departamento de Engenharia Eletrônica
 *
 * API inspirada na biblioteca RadioHead produzida por AirSpace Pty Ltd. Copyright (C) 2011-2020 Mike McCauley
 *
 * Licença Pública Creative Commons Atribuição-NãoComercial-CompartilhaIgual 4.0 Internacional
 * Disponível em <https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode.pt>
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
