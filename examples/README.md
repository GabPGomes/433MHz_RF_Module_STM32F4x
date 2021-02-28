# Transmitter example
In the transmitter example, `exemplo_RFModSTM32f4x_transmissor`, the STM32F401RE is programmed to send a message containing the number of packets/messages already sent since startup.
##### Steps
1. Connect the RF module's transmitter to the STM32F401RE;
2. Load the example to SW4STM32 and then to the STM board;
3. Connect the RF module's receiver to the board that will receive the message (in this example an Arduino nano with an adapted RadioHead library);
   - Don't forget to configure the other board correctly. You can use another STM32F401RE with the receiver example loaded as the second board too.
4. Load your code to the second board;
5. Open the receiver's terminal (it can be the Serial Port terminal) to see the messages sent.
##### Exchanged messages
The code snippet that writes the number of messages sent. The counter shown resets every ten messages:
![TesteTransmissor2](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteTransmissor2.jpg)

The code snippet with the message received:
![TesteTransmissor1](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteTransmissor1.jpg)

# Receiver example
In the receiver example, `exemplo_RFModSTM32f4x_receptor`, the STM32F401RE is programmed to receive a message and print it in the RealTerm terminal. It also prints the number of successfully received messages (_rxbom) as well as the number of the ones that have failed (_rxruim) since startup.
##### Steps
1. Connect the RF module's receiver to the STM32F401RE;
2. Load the example to SW4STM32 and then to the STM board;
3. Connect the RF module's transmitter to the board that will send the message (in this example an Arduino nano with an adapted RadioHead library);
   - Don't forget to configure the other board correctly. You can use another STM32F401RE with the transmitter example loaded as the second board too.
4. Load your code to the second board;
5. Open and configure RealTerm as in the [guide](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/wiki/RealTerm-configuration).
##### Exchanged messages
Messages sent by the Arduino nano at the right. "Enviei: 'x' " means that the 'x' character has been sent. Messages received by the STM32F401RE at the left. "Recebi: 'x' " means that the 'x' character has been received.
![TesteReceptor](https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteReceptor.jpg)
