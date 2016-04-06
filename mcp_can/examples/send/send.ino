  // demo: CAN-BUS Shield, send data
  #include <df_can.h>
  #include <SPI.h>
  
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
  
  unsigned char data[8] = {'D', 'F', 'R', 'O', 'B', 'O', 'T', '!'};
  void loop()
  {
      // send data:  id = 0x06, standrad flame, data len = 8, data: data buf
      CAN.sendMsgBuf(0x06, 0, 8, data);
      delay(100);                       // send data per 100ms
  }
  
  
  
  

