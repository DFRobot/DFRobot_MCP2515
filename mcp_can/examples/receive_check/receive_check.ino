  /******************************************************************************
   * demo: CAN-BUS Shield, receive data with check mode
   * send data coming to fast, such as less than 10ms, you can use this way
   * Jansion, 2015.5.27
   ******************************************************************************/
  
  #include <SPI.h>
  #include "df_can.h"
  
  const int SPI_CS_PIN = 10;
  MCPCAN CAN(SPI_CS_PIN);                                    // Set CS pin
  
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
  
  
  void loop()
  {
      unsigned char len = 0;
      unsigned char buf[8];
  
      if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
      {
          CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
  
          for(int i = 0; i<len; i++)    // print the data
          {
              Serial.write(buf[i]);
              Serial.print("\t");
          }
          Serial.println();
      }
  }

