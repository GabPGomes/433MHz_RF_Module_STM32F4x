# 433MHz_RF_Module_STM32F4x
This repository contains an API and examples for the use of a FS1000A(transmitter) + MK-RM-5V(receiver) [433MHz radio frequency module](https://www.filipeflop.com/produto/modulo-rf-transmissor-receptor-433mhz-am/) with a [STM Nucleo-F401RE Board](https://www.st.com/en/evaluation-tools/nucleo-f401re.html). It includes funtions to receive, transmit and manage messages going through the media.

This API was an assignment for UFMG's course "Embbedded Systems Programing" instructed by Prof. Ricardo de Oliveira Duarte - Departamento de Engenharia Eletrônica (Electronics Engineering).

API inspired in [RadioHead's library](https://www.airspayce.com/mikem/arduino/RadioHead/) made by AirSpace Pty Ltd. Copyright (C) 2011-2020 Mike McCauley.

**Be careful!** Since the RF modules use 5V, make sure you: 
- put the GPIO output to (Open-Drain, no pullup no pulldown) mode at STM32CubeMX and use an external pull-up resistor;
- put the GPIO input to (input, no pullup no pulldown) mode;  
- also take a look at your device's datasheet and check the requirements for 5V use, since the misuse of 5V can **damage** your device.

# API Guide and examples
## Guide:
1. [Requirements and hardware setup](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/Requirements-and-hardware-setup)
2. [Software configuration using STM32CubeMX](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/Software-configuration-using--STM32CubeMX-(before-SW4STM32-configuration))
3. [Software configuration using SW4STM32](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/Software-configuration-using--SW4STM32-(after-STM32CubeMX-configuration))
4. [RealTerm configuration](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/RealTerm-configuration)

## Examples
[Receiver](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/tree/main/examples/example_RFModSTM32f4x_receiver)
[Transmitter](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/tree/main/examples/example_RFModSTM32f4x_transmitter)

# Documentation
[Library Documentation](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/Library-Documentation)\
[Related Documents](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/tree/main/RelatedDocuments)
