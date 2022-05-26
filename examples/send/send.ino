/*!
 * @file  send.ino
 * @brief  CAN-BUS Shield, send data
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Jansion
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#include "DFRobot_MCP2515.h"

const int SPI_CS_PIN = 10;

DFRobot_MCP2515 CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);
    int count = 50;                                     // the max numbers of initializint the CAN-BUS, if initialize failed first!.  
    do {
        CAN.init();   //must initialize the Can interface here! 
        if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
        {
            Serial.println("DFROBOT's CAN BUS Shield init ok!");
            break;
        }
        else
        {
            Serial.println("DFROBOT's CAN BUS Shield init fail");
            Serial.println("Please Init CAN BUS Shield again");

            delay(100);
            if (count <= 1)
                Serial.println("Please give up trying!, trying is useless!");
        }

    }while(count--);

}

unsigned char data[8] = {'D', 'F', 'R', 'O', 'B', 'O', 'T', '!'};
void loop()
{
    // send data:  id = 0x06, standrad flame, data len = 8, data: data buf
    CAN.sendMsgBuf(0x06, 0, 8, data);
    delay(100);                       // send data per 100ms
}
