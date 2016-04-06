  /***********************************************************
   *demo: CAN-BUS Shield, receive data with interrupt mode
   * when in interrupt mode, the data coming can't be too fast, must >20ms, or else you can use check mode
   * Jansion, 2015-5-27
   ***********************************************************/
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
  }
  
  void MCP2515_ISR()
  {
      flagRecv = 1;
  }
  
  void loop()
  {
      if(flagRecv) 
      {                                   // check if get data
  
          flagRecv = 0;                   // clear flag
  
          // iterate over all pending messages
          // If either the bus is saturated or the MCU is busy,
          // both RX buffers may be in use and after having read a single
          // message, MCU does  clear the corresponding IRQ conditon.
          while (CAN_MSGAVAIL == CAN.checkReceive()) 
          {
              // read data,  len: data length, buf: data buf
              CAN.readMsgBuf(&len, buf);
  
              // print the data
              for(int i = 0; i<len; i++)
              {
                  Serial.write(buf[i]);Serial.print("\t");
              }
              Serial.println();
          }
      }
  }
  

