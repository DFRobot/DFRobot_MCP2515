/*!
 * @file  receiveCheck.ino
 * @brief  CAN-BUS Shield, receive data with check mode
 * @n  send data coming to fast, such as less than 10ms, you can use this way
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Arduinolibrary
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;
DFRobot_MCP2515 CAN(SPI_CS_PIN);   // Set CS pin

void setup()
{
    Serial.begin(115200);

    while( CAN.begin(CAN_500KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("DFROBOT's CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(3000);
    }
    Serial.println("DFROBOT's CAN BUS Shield init ok!\n");

}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())   // check if data coming
    {
        CAN.readMsgBuf(&len, buf);   // read data,  len: data length, buf: data buf

        for(int i = 0; i<len; i++)   // print the data
        {
            Serial.write(buf[i]);
            Serial.print("\t");
        }
        Serial.println();
    }
}