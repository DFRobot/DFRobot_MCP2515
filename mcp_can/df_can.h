/*
  mcp_can.h
  2015 Copyright (c) DFROBOT Technology Inc.  All right reserved.

  Author:Jansion	
  Contributor:
  2015-5-25
  
*/
#ifndef _MCP_H_
#define _MCP_H_

#include "df_candfs.h"

#define MAX_MESSAGE_LENGTH 8

class MCPCAN
{
    private:
    
    INT8U   can_ExtFlg;                                                 
                                                                       
                                                                        
    INT32U  can_ID;                                                      
    INT8U   can_Dlc;                                                     
    INT8U   can_Dta[MAX_MESSAGE_LENGTH];                            	
    INT8U   can_Rtr;                                                    
    INT8U   can_filhit;
    INT8U   SPI_CS;

private:

    void mcp_reset(void);                                           

    INT8U mcp_readRegister(const INT8U RegAddr);                   
    
    void mcp_readMulitiRegisters(const INT8U RegAddr, 
	                       INT8U *buf, 
                                INT8U len);
    void mcp_setRegister(const INT8U RegAddr,                      
                             const INT8U value);

    void mcp_setMulitRegisterS(const INT8U RegAddr,                     
                              const INT8U *buf,
                              const INT8U len);
    
    void mcp_initBuffers(void);
    
    void mcp_modifyRegister(const INT8U RegAddr,                   
                                const INT8U mask,
                                const INT8U data);

    INT8U mcp_readStatus(void);                                    
    INT8U mcp_setMode(const INT8U newMode);                
    INT8U mcp_configRate(const INT8U canSpeed);                     
    INT8U mcp_init(const INT8U canSpeed);                           

    void mcp_writeid( const INT8U mcp_addr,                       
                               const INT8U ext,
                               const INT32U id );

    void mcp_readid( const INT8U mcp_addr,                        
                                    INT8U* ext,
                                    INT32U* id );

    void mcp_writecanMsg( const INT8U sidh_addr );          
    void mcp_readcanMsg( const INT8U sidh_addr);            
    void mcp_starttransmit(const INT8U mcp_addr);                  
    INT8U mcp_getNextFreeTXBuf(INT8U *txbuf_n);                     

 

    INT8U setMsg(INT32U id, INT8U ext, INT8U len, INT8U rtr, INT8U *pData);   
    INT8U setMsg(INT32U id, INT8U ext, INT8U len, INT8U *pData);           
    INT8U clearMsg();                                               
    INT8U readMsg();                                               
    INT8U sendMsg();                                               

public:
    MCPCAN(INT8U _CS);
	void  init(void);
    INT8U begin(INT8U speedset);    
	INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf);   
    INT8U isRemoteRequest(void);                                   

	INT8U init_Mask(Masker_t Masker_num, INT8U ext, INT32U Data);          
    INT8U checkReceive(void);                                      

	
	INT8U init_Filter(Filter_t Filter_num, INT8U ext, INT32U Data);

	INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U rtr, INT8U len, INT8U *buf);  
  
    INT8U readMsgBuf(INT8U *len, INT8U *buf);                      
    INT8U readMsgBufID(INT32U *ID, INT8U *len, INT8U *buf);         
    INT8U checkError(void);                                         
    INT32U getCanId(void);                                         
    INT8U isExtendedFrame(void);                                   
};

#endif
