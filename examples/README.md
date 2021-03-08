# Transmitter example
In the transmitter example `example_AN_RFMod_CRC_transmitter`, the STM32F401RE is programmed to send a message containing the number of packets/messages already sent since startup.
##### Steps
1. Connect the RF module's transmitter to the STM32F401RE;
2. Import the example to SW4STM32 and then load it to the STM board;
3. Connect the RF module's receiver to the board that will receive the message (in this example an Arduino nano with an adapted RadioHead library);
   - Don't forget to configure the other board correctly. You can use another STM32F401RE with the receiver example loaded as the second board too.
4. Load your code to the second board;
5. Open the receiver's terminal (RealTerm in this case) to see the messages sent.
##### Results
The code snippet that writes the number of messages sent. The counter shown resets every ten messages:
![TesteTransmissor2](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteTransmissor2.jpg)

The receiver's terminal with the message received:
![TesteTransmissor1](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteTransmissor1.jpg)

# Receiver example
In the receiver example `example_RFModSTM32f4x_receiver`, the STM32F401RE is programmed to receive a message and print it in the RealTerm terminal. It also prints the number of successfully received messages `_rxBom`, as well as the number of the ones that have failed `_rxRuim` since startup.
##### Steps
1. Connect the RF module's receiver to the STM32F401RE;
2. Import the example to SW4STM32 and then load it to the STM board;
3. Connect the RF module's transmitter to the board that will send the message (in this example an Arduino nano with an adapted RadioHead library);
   - Don't forget to configure the other board correctly. You can use another STM32F401RE with the transmitter example loaded as the second board too.
4. Load your code to the second board;
5. Open and configure RealTerm as in the [guide](https://github.com/AN_RFMod_CRC/wiki/RealTerm-configuration).
##### Results
Messages sent by the Arduino nano at the right. `Enviei: 'x'` means that the 'x' character has been sent.\
Messages received by the STM32F401RE at the left. `Recebi: 'x'` means that the 'x' character has been received.
![TesteReceptor](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteReceptor.jpg)
