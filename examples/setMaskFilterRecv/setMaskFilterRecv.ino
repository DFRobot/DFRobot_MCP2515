/*!
 * @file  setMaskFilterRecv.ino
 * @brief  CAN-BUS Shield, receive data with interrupt mode, and set mask and filter
 * @n  when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
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

unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];
void setup()
{
    Serial.begin(115200);

    while( CAN.begin(CAN_500KBPS) ){   // init can bus : baudrate = 500k
        Serial.println("DFROBOT's CAN BUS Shield init fail");
        Serial.println("Please Init CAN BUS Shield again");
        delay(3000);
    }
    Serial.println("DFROBOT's CAN BUS Shield init ok!\n");

    CAN.initMask(MCP2515_RXM0, 0, 0x3ff);                         // there are 2 mask in mcp2515, you need to set both of them
    CAN.initMask(MCP2515_RXM1, 0, 0x3ff);
    /*
     * set filter, we can receive id from 0x04 ~ 0x09 except for 0x06
     * // there are 6 filter in mcp2515,so it can filter six id,i.e.0x04~0x09.
     */
    CAN.initFilter(MCP2515_RXF0, 0, 0x04);                         // filter 0 for id = 0x04
    CAN.initFilter(MCP2515_RXF1, 0, 0x05);                         // filter 1 for id = 0x05
    // CAN.initFilter(MCP2515_RXF2, 0, 0x06);                         // filter 2 for id = 0x06
    CAN.initFilter(MCP2515_RXF3, 0, 0x07);                         // filter 3 for id = 0x07
    CAN.initFilter(MCP2515_RXF4, 0, 0x08);                         // filter 4 for id = 0x08
    CAN.initFilter(MCP2515_RXF5, 0, 0x09);                         // filter 5 for id = 0x09

    attachInterrupt(0, MCP2515_ISR, FALLING); // start interrupt
    /*
     * set mask, set both the mask to 0x3ff
     */

}

void MCP2515_ISR()
{
    flagRecv = 1;
}

void loop()
{
    if(flagRecv)                   // check if get data
    {

        flagRecv = 0;                // clear flag
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        Serial.println("\r\n------------------------------------------------------------------");
        Serial.print("Get Data From id: ");
        Serial.println(CAN.getCanId());
        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print("0x");
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();

    }
}
