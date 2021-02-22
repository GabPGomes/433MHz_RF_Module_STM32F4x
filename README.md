# 433MHz_RF_Module_STM32F4x
This repository contains an API and examples for the use of a [433MHz radio frequency module](https://www.filipeflop.com/produto/modulo-rf-transmissor-receptor-433mhz-am/) with a [STM Nucleo-F401RE Board](https://www.st.com/en/evaluation-tools/nucleo-f401re.html). It includes funtions to receive, transmit and manage messages going through the media.

This API was an assignment for UFMG's course "Embbedded Systems Programing" instructed by Prof. Ricardo de Oliveira Duarte - Departamento de Engenharia Eletrônica (Electronics Engineering).

API inspired in [RadioHead's library](https://www.airspayce.com/mikem/arduino/RadioHead/) made by AirSpace Pty Ltd. Copyright (C) 2011-2020 Mike McCauley.

**Be careful:** since the RF modules use 5V, make sure you: 
- put the GPIO output to (Open-Drain, no pullup no pulldown) mode at STM32CubeMX and use an external pull-up resistor;
- put the GPIO input to (input, no pullup no pulldown) mode;  
- also take a look at your device's datasheet and check the requirements for 5V use, since the misuse of 5V can **damage** your device.

# Repository Contents
Requirements and hardware setup\
Examples\
Library Documentation\
Related Documents
