  /**************************************************************************************************************
   *demo: CAN-BUS Shield, receive data with interrupt mode, and set mask and filter
   * when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
   * Jansion, 2015-5-27
   ****************************************************************************************************************/
  #include <SPI.h>
  #include "df_can.h"
  
  const int SPI_CS_PIN = 10;
  MCPCAN CAN(SPI_CS_PIN);                                    // Set CS pin
  unsigned char flagRecv = 0;
  unsigned char len = 0;
  unsigned char buf[8];
  char str[20];
  void setup()
  {
      Serial.begin(115200);
      int count = 50;                                     // the max numbers of initializint the CAN-BUS, if initialize failed first!. 
  
      do {
          CAN.init();   //must initialize the Can interface here! 
          CAN.init_Mask(MCP_RXM0, 0, 0x3ff);                         // there are 2 mask in mcp2515, you need to set both of them
          CAN.init_Mask(MCP_RXM1, 0, 0x3ff);
          /*
           * set filter, we can receive id from 0x04 ~ 0x09 except for 0x06
           * // there are 6 filter in mcp2515,so it can filter six id,i.e.0x04~0x09.
           */
          CAN.init_Filter(MCP_RXF0, 0, 0x04);                         // filter 0 for id = 0x04
          CAN.init_Filter(MCP_RXF1, 0, 0x05);                         // filter 1 for id = 0x05
          // CAN.init_Filter(MCP_RXF2, 0, 0x06);                         // filter 2 for id = 0x06
          CAN.init_Filter(MCP_RXF3, 0, 0x07);                         // filter 3 for id = 0x07
          CAN.init_Filter(MCP_RXF4, 0, 0x08);                         // filter 4 for id = 0x08
          CAN.init_Filter(MCP_RXF5, 0, 0x09);                         // filter 5 for id = 0x09 
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

