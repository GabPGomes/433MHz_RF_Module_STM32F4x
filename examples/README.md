# Transmitter example
In the transmitter example, `exemplo_RFModSTM32f4x_transmissor`, the STM32F401RE is programmed to send a message containing the number of packets/messages already sent since startup.
##### Steps
1. Connect the module's transmitter to the STM32F401RE;
2. Load the example to SW4STM32 and then to the STM board;
3. Connect the module's receiver to the board that will receive the message (in this example an Arduino nano with an adapted RadioHead library);
   - Don't forget to configure the other board correctly. You can use another STM32F401RE with the receiver example loaded as the second board too.
4. Open the receiver's terminal (it can be the Serial Port terminal) to see the messages sent.
##### Message sent and the one that was received
The code snippet that writes the number of messages sent. The counter shown resets every ten messages.
![TesteTransmissor2])(https://github.com/GabPGomes/433MHz_RF_Module_STM32F4x/blob/main/images/TesteTransmissor2.jpg)
