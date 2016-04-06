/*
  mcp_can.h
  2015 Copyright (c) DFROBOT Technology Inc.  All right reserved.

  Author:Jansion	
  Contributor:
  2015-5-25
  
*/

#include "df_can.h"

#define ReadWriteOneByte SPI.transfer
#define Read() SPI.transfer(0x00)




void MCPCAN::mcp_reset(void)
{
    MCPSPI_SELECT();
    ReadWriteOneByte(MCP_RESET);
    MCPSPI_UNSELECT();
    delay(10);
}


INT8U MCPCAN::mcp_readRegister(const INT8U RegAddr)                                                                     
{
    INT8U ret;

    MCPSPI_SELECT();
    ReadWriteOneByte(MCP_READ);
    ReadWriteOneByte(RegAddr);
    ret = Read();
    MCPSPI_UNSELECT();

    return ret;
}

void MCPCAN::mcp_readMulitiRegisters(const INT8U RegAddr, INT8U *buf, INT8U len)
{
	INT8U i;

	if ( len > CAN_MAX_MESSAGE_LENGTH)
	{
		len = CAN_MAX_MESSAGE_LENGTH;
	}
	
	MCPSPI_SELECT();
	ReadWriteOneByte(MCP_READ);
	ReadWriteOneByte(RegAddr);

	for (i=0; i < len; i++) {
		buf[i] = Read();
	}
	MCPSPI_UNSELECT();
}

 
void MCPCAN::mcp_setRegister(const INT8U RegAddr, const INT8U value)
{
    MCPSPI_SELECT();
    ReadWriteOneByte(MCP_WRITE);
    ReadWriteOneByte(RegAddr);
    ReadWriteOneByte(value);
    MCPSPI_UNSELECT();
}


void MCPCAN::mcp_setMulitRegisterS(const INT8U RegAddr, const INT8U *buf, const INT8U len)
{
    INT8U i;
	
    MCPSPI_SELECT();
    ReadWriteOneByte(MCP_WRITE);
    ReadWriteOneByte(RegAddr);
       
    for (i=0; i < len; i++) 
    {
        ReadWriteOneByte(buf[i]);
    }
    MCPSPI_UNSELECT();
}



void MCPCAN::mcp_modifyRegister(const INT8U RegAddr, const INT8U mask, const INT8U data)
{
    MCPSPI_SELECT();
    ReadWriteOneByte(MCP_BITMOD);
    ReadWriteOneByte(RegAddr);
    ReadWriteOneByte(mask);
    ReadWriteOneByte(data);
    MCPSPI_UNSELECT();
}

INT8U MCPCAN::mcp_readStatus(void)                             
{
	INT8U ret;
	
	MCPSPI_SELECT();
	ReadWriteOneByte(MCP_RX_STATUS);
	ret = Read();
	MCPSPI_UNSELECT();
	
	return ret;
}


INT8U MCPCAN::mcp_setMode(const INT8U newMode)
{
    INT8U ret;

    mcp_modifyRegister(MCPCANCTRL, MODE_MASK, newMode);
    ret = mcp_readRegister(MCPCANCTRL);
    ret &= MODE_MASK;

    if ( ret == newMode ) 
    {
        return MCP_OK;
    }

    return MCP_FAIL;

}

INT8U MCPCAN::mcp_configRate(const INT8U canSpeed)            
{
    INT8U preSet, cfg1, cfg2, cfg3;
	
    preSet = 0;
    switch (canSpeed) 
    {
        case (CAN_5KBPS):
        cfg1 = MCP_16MHz_5kBPS_CFG1;
        cfg2 = MCP_16MHz_5kBPS_CFG2;
        cfg3 = MCP_16MHz_5kBPS_CFG3;
        break;

        case (CAN_10KBPS):
        cfg1 = MCP_16MHz_10kBPS_CFG1;
        cfg2 = MCP_16MHz_10kBPS_CFG2;
        cfg3 = MCP_16MHz_10kBPS_CFG3;
        break;

        case (CAN_20KBPS):
        cfg1 = MCP_16MHz_20kBPS_CFG1;
        cfg2 = MCP_16MHz_20kBPS_CFG2;
        cfg3 = MCP_16MHz_20kBPS_CFG3;
        break;
        
        case (CAN_31K25BPS):
        cfg1 = MCP_16MHz_31k25BPS_CFG1;
        cfg2 = MCP_16MHz_31k25BPS_CFG2;
        cfg3 = MCP_16MHz_31k25BPS_CFG3;
        break;

        case (CAN_33KBPS):
        cfg1 = MCP_16MHz_33kBPS_CFG1;
        cfg2 = MCP_16MHz_33kBPS_CFG2;
        cfg3 = MCP_16MHz_33kBPS_CFG3;
        break;

        case (CAN_40KBPS):
        cfg1 = MCP_16MHz_40kBPS_CFG1;
        cfg2 = MCP_16MHz_40kBPS_CFG2;
        cfg3 = MCP_16MHz_40kBPS_CFG3;
        break;

        case (CAN_50KBPS):
        cfg1 = MCP_16MHz_50kBPS_CFG1;
        cfg2 = MCP_16MHz_50kBPS_CFG2;
        cfg3 = MCP_16MHz_50kBPS_CFG3;
        break;

        case (CAN_80KBPS):
        cfg1 = MCP_16MHz_80kBPS_CFG1;
        cfg2 = MCP_16MHz_80kBPS_CFG2;
        cfg3 = MCP_16MHz_80kBPS_CFG3;
        break;

        case (CAN_83K3BPS):
        cfg1 = MCP_16MHz_83k3BPS_CFG1;
        cfg2 = MCP_16MHz_83k3BPS_CFG2;
        cfg3 = MCP_16MHz_83k3BPS_CFG3;
        break;  

        case (CAN_95KBPS):
        cfg1 = MCP_16MHz_95kBPS_CFG1;
        cfg2 = MCP_16MHz_95kBPS_CFG2;
        cfg3 = MCP_16MHz_95kBPS_CFG3;
        break;

        case (CAN_100KBPS):                                           
        cfg1 = MCP_16MHz_100kBPS_CFG1;
        cfg2 = MCP_16MHz_100kBPS_CFG2;
        cfg3 = MCP_16MHz_100kBPS_CFG3;
        break;

        case (CAN_125KBPS):
        cfg1 = MCP_16MHz_125kBPS_CFG1;
        cfg2 = MCP_16MHz_125kBPS_CFG2;
        cfg3 = MCP_16MHz_125kBPS_CFG3;
        break;

        case (CAN_200KBPS):
        cfg1 = MCP_16MHz_200kBPS_CFG1;
        cfg2 = MCP_16MHz_200kBPS_CFG2;
        cfg3 = MCP_16MHz_200kBPS_CFG3;
        break;

        case (CAN_250KBPS):
        cfg1 = MCP_16MHz_250kBPS_CFG1;
        cfg2 = MCP_16MHz_250kBPS_CFG2;
        cfg3 = MCP_16MHz_250kBPS_CFG3;
        break;

        case (CAN_500KBPS):
        cfg1 = MCP_16MHz_500kBPS_CFG1;
        cfg2 = MCP_16MHz_500kBPS_CFG2;
        cfg3 = MCP_16MHz_500kBPS_CFG3;
        break;
        
        case (CAN_1000KBPS):
        cfg1 = MCP_16MHz_1000kBPS_CFG1;
        cfg2 = MCP_16MHz_1000kBPS_CFG2;
        cfg3 = MCP_16MHz_1000kBPS_CFG3;
        break;  

        default:
        preSet = 1;
        break;
    }

    if (!preSet) {
        mcp_setRegister(MCP_CNF1, cfg1);
        mcp_setRegister(MCP_CNF2, cfg2);
        mcp_setRegister(MCP_CNF3, cfg3);
        return MCP_OK;
    }
    else {
        return MCP_FAIL;
    }
}


void MCPCAN::mcp_initBuffers(void)
{
    INT8U i, a1, a2, a3;
 
    a1 = MCP_TXB0CTRL;
    a2 = MCP_TXB1CTRL;
    a3 = MCP_TXB2CTRL;
    for (i = 0; i < 14; i++) {                                        
        mcp_setRegister(a1, 0);
        mcp_setRegister(a2, 0);
        mcp_setRegister(a3, 0);
        a1++;
        a2++;
        a3++;
    }
    mcp_setRegister(MCP_RXB0CTRL, 0);
    mcp_setRegister(MCP_RXB1CTRL, 0);
}

INT8U MCPCAN::mcp_init(const INT8U canSpeed)                    
{

  INT8U res;

   
    res = mcp_setMode(MODE_CONFIG);
    if(res > 0)
    {
      delay(10);
      return res;
    }
	delay(10);


                                                                       
    if(mcp_configRate(canSpeed))
    {
	  delay(10);
      return res;
    }
	delay(10);


    if ( res == MCP_OK ) {

                                                                       
        mcp_initBuffers();

                                                                       
        mcp_setRegister(MCPCANINTE, MCP_RX0IF | MCP_RX1IF);

                                                                 
        mcp_modifyRegister(MCP_RXB0CTRL,
        MCP_RXB_RX_MASK | MCP_RXB_BUKT_MASK,
        MCP_RXB_RX_STDEXT | MCP_RXB_BUKT_MASK );
        mcp_modifyRegister(MCP_RXB1CTRL, MCP_RXB_RX_MASK,
        MCP_RXB_RX_STDEXT);
                                                                       
        res = mcp_setMode(MODE_NORMAL);                                                                
        if(res)
        {  
          delay(10);
          return res;
        }

        delay(10);

    }
    return res;

}


void MCPCAN::mcp_writeid( const INT8U mcp_addr, const INT8U ext, const INT32U id )
{
    uint16_t canid;
    INT8U tbufdata[4];

    canid = (uint16_t)(id & 0x0FFFF);

    if ( ext == 1) 
    {
        tbufdata[MCP_EID0] = (INT8U) (canid & 0xFF);
        tbufdata[MCP_EID8] = (INT8U) (canid >> 8);
        canid = (uint16_t)(id >> 16);
        tbufdata[MCP_SIDL] = (INT8U) (canid & 0x03);
        tbufdata[MCP_SIDL] += (INT8U) ((canid & 0x1C) << 3);
        tbufdata[MCP_SIDL] |= MCP_TXB_EXIDE_M;
        tbufdata[MCP_SIDH] = (INT8U) (canid >> 5 );
    }
    else 
    {
        tbufdata[MCP_SIDH] = (INT8U) (canid >> 3 );
        tbufdata[MCP_SIDL] = (INT8U) ((canid & 0x07 ) << 5);
        tbufdata[MCP_EID0] = 0;
        tbufdata[MCP_EID8] = 0;
    }
    mcp_setMulitRegisterS( mcp_addr, tbufdata, 4 );
}

void MCPCAN::mcp_readid( const INT8U mcp_addr, INT8U* ext, INT32U* id )
{
    INT8U id_Buf[4];

    mcp_readMulitiRegisters( mcp_addr, (INT8U *)id_Buf, 4 );

    *id = (id_Buf[MCP_SIDH]<< 3) + (id_Buf[MCP_SIDL]>>5);

    if ( (id_Buf[MCP_SIDL] & 1 << 3)) 
    {
                                                                       
        *id = (*id<<2) + (id_Buf[MCP_SIDL] & 0x03);
        *id = (*id<<8) + id_Buf[MCP_EID8];
        *id = (*id<<8) + id_Buf[MCP_EID0];
        *ext = 1;
    }
}

void MCPCAN::mcp_writecanMsg( const INT8U sidh_addr)
{
    INT8U mcp_addr;
    mcp_addr = sidh_addr;
    mcp_setMulitRegisterS(mcp_addr+5, can_Dta, can_Dlc );                 
    if ( can_Rtr == 1)                                                   
    {
        can_Dlc |= MCP_RTR_MASK;  
    }
    mcp_setRegister((mcp_addr+4), can_Dlc );                        
    mcp_writeid(mcp_addr, can_ExtFlg, can_ID );                     
}





void MCPCAN::mcp_readcanMsg( const INT8U idh_addr)        
{

    mcp_readid( idh_addr, &can_ExtFlg,&can_ID );   

    can_Rtr = mcp_readRegister( idh_addr - 1 );
    can_Dlc = mcp_readRegister( idh_addr + 4 );

    if ((can_Rtr & (1 << 3))) {
        can_Rtr = 1;
    }
    else {
        can_Rtr = 0;
    }

    can_Dlc &= MCP_DLC_MASK;
    mcp_readMulitiRegisters( idh_addr+5, (INT8U *)can_Dta, can_Dlc);
}

void MCPCAN::mcp_starttransmit(const INT8U mcp_addr)              
{
    mcp_modifyRegister( mcp_addr-1 , MCP_TXB_TXREQ_M, MCP_TXB_TXREQ_M );
}


INT8U MCPCAN::mcp_getNextFreeTXBuf(INT8U *txbuf_n)                 
{
    INT8U res, i, ctrlval;
    INT8U ctrlregs[MCP_N_TXBUFFERS] = { MCP_TXB0CTRL, MCP_TXB1CTRL, MCP_TXB2CTRL };

    res = MCP_ALLTXBUSY;
    *txbuf_n = 0x00;

                                                                       
    for (i=0; i < MCP_N_TXBUFFERS; i++) {
        ctrlval = mcp_readRegister( ctrlregs[i] );
        if ( (ctrlval & MCP_TXB_TXREQ_M) == 0 ) {
            *txbuf_n = ctrlregs[i]+1;                                   
                                                                        
            res = MCP_OK;
            return res;                                                 
        }
    }
    return res;
}




 

/*!
* @brief the MCPCAN class' constructor. 
*
* @parameter: 
		@_CS:
			indicate the spi select pin when mcu commication with the can controler e.i MCP2515
*
* @return void
*/ 



MCPCAN::MCPCAN(INT8U _CS)
{
   
    SPI_CS = _CS;
    pinMode(SPI_CS, OUTPUT);
	
    MCPSPI_UNSELECT();

}


/*!
* @brief: initialize the Can controler. 
*
* @parameter:  void
*
* @return void
*/ 

void MCPCAN::init(void)
{
	SPI.begin();
    mcp_reset();

}

/*!
* @brief: config the the Can baud rate,  buffer, and interrupt. 
*
* @parameter:  void
*
* @return if successful, it return CAN_OK, or CAN_FAILINIT
*/
INT8U MCPCAN::begin(INT8U speedset)
{
    INT8U res;
	
    res = mcp_init(speedset);
    if (res == MCP_OK) return CAN_OK;
    else return CAN_FAILINIT;
}



/*!
* @brief: initialize the mask register. 
*
* @parameter:  
		@Masker_num: 
			maybe set MCP_RXM0 or MCP_RXM1.
		@ext:
			extend flag. if ext = 1, indicate the frame is extended frame.
*
* @return the status. if success, return MCP_OK.
*/
INT8U MCPCAN::init_Mask(Masker_t Masker_num, INT8U ext, INT32U ulData)
{
    INT8U res = MCP_OK;  
	
	delay(10);
    res = mcp_setMode(MODE_CONFIG);
    if(res > 0){  
	delay(10);
    return res;
    }
    
    if (Masker_num == MCP_RXM0){
        mcp_writeid(MCP_RXM0SIDH, ext, ulData);

    }
    else if(Masker_num == MCP_RXM1){
        mcp_writeid(MCP_RXM1SIDH, ext, ulData);
    }
    else res =  MCP_FAIL;
    
    res = mcp_setMode(MODE_NORMAL);
    if(res > 0){

	delay(10);
    return res;
  }  
    delay(10);
    return res;
}


/*!
* @brief: initialize the fileter register. 
*
* @parameter:  
		@Masker_num: 
			maybe set MCP_RXF0, MCP_RXF1、 MCP_RXF2、 MCP_RXF3、 MCP_RXF4、 MCP_RXF5.
		@ext:
			extend flag. if ext = 1, indicate the frame is extended frame.
*
* @return the status. if success, return MCP_OK.
*/


INT8U MCPCAN::init_Filter(Filter_t Filter_num, INT8U ext, INT32U Data)
{
    INT8U res = MCP_OK;  
	delay(10);
	
    res = mcp_setMode(MODE_CONFIG);
	
    if(res > 0)
    {  
      delay(10);
      return res;
    }
    
    switch( Filter_num )
    {
        case MCP_RXF0:
	
        mcp_writeid(MCP_RXF0SIDH, ext, Data);
        break;

        case MCP_RXF1:
        mcp_writeid(MCP_RXF1SIDH, ext, Data);
        break;

        case MCP_RXF2:
        mcp_writeid(MCP_RXF2SIDH, ext, Data);
        break;

        case MCP_RXF3:
        mcp_writeid(MCP_RXF3SIDH, ext, Data);
        break;

        case MCP_RXF4:
        mcp_writeid(MCP_RXF4SIDH, ext, Data);
        break;

        case MCP_RXF5:
        mcp_writeid(MCP_RXF5SIDH, ext, Data);
        break;

        default:
        res = MCP_FAIL;
    }
    
    res = mcp_setMode(MODE_NORMAL);
    if(res > 0)
    {  
      delay(10);
      return res;
    }  
	
	delay(10);

    return res;
}





INT8U MCPCAN::setMsg(INT32U id, INT8U ext, INT8U len, INT8U rtr, INT8U *pData)
{
    int i = 0;
    can_ExtFlg = ext;
    can_ID     = id;
    can_Dlc    = len;
    can_Rtr    = rtr;
    for(i = 0; i < MAX_MESSAGE_LENGTH; i++)
    {
        can_Dta[i] = pData[i];
    }
    return MCP_OK;
}


INT8U MCPCAN::setMsg(INT32U id, INT8U ext, INT8U len, INT8U *pData)
{
    int i = 0;
    can_ExtFlg = ext;
    can_ID     = id;
    can_Dlc    = len;
    for(i = 0; i < MAX_MESSAGE_LENGTH; i++)
    {
        can_Dta[i] = *(pData+i);
    }
    return MCP_OK;
}

INT8U MCPCAN::clearMsg()
{

    can_ID       = 0;
    can_Rtr      = 0;
    can_ExtFlg   = 0;
    can_filhit   = 0;
    can_Dlc      = 0;
    for(int i = 0; i<can_Dlc; i++ )
      can_Dta[i] = 0x00;

    return MCP_OK;
}


INT8U MCPCAN::sendMsg()
{
    INT8U res, txindex;
    uint16_t uiTimeOut = 0;

    do {
        res = mcp_getNextFreeTXBuf(&txindex);                       
        uiTimeOut++;
    } while (res == MCP_ALLTXBUSY && (uiTimeOut < TIMEOUTVALUE));

    if(uiTimeOut == TIMEOUTVALUE) 
    {   
        return CAN_GETTXBFTIMEOUT;                                     
    }
    uiTimeOut = 0;
    mcp_writecanMsg( txindex);
    mcp_starttransmit( txindex );
    do
    {
        uiTimeOut++;        
        res = mcp_readRegister(txindex);  			                
        res = res & 0x08;                               		
    }while(res && (uiTimeOut < TIMEOUTVALUE));   
    if(uiTimeOut == TIMEOUTVALUE)                                       
    {
        return CAN_SENDMSGTIMEOUT;
    }
    return CAN_OK;

}

/*!
* @brief: send the remote requestion message. 
*
* @parameter:  
		@id: 
			the message id num. 
		@ext:
			extend flag. if ext = 1, indicate the frame is extended frame.
		@len:
			the len of the data to send.
		@rtr:
			the flag of the remote requestion. if rtr = 1, the frame seem as the remote requestion frame , or the frame is the normal data frame..
		@buf:
			the data to send.
			
*
* @return the status. if success, return MCP_OK.
*/

INT8U MCPCAN::sendMsgBuf(INT32U id, INT8U ext, INT8U rtr, INT8U len, INT8U *buf)
{
    setMsg(id, ext, len, rtr, buf);
    return sendMsg();
}



/*!
* @brief: send one data frame. 
*
* @parameter:  
		@id: 
			the message id num. 
		@ext:
			extend flag. if ext = 1, indicate the frame is extended frame.
		@len:
			the len of the data to send.
	
		@buf:
			the data to send.
			
*
* @return the status. if success, return MCP_OK.
*/

INT8U MCPCAN::sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf)
{
    setMsg(id, ext, len, buf);
    return sendMsg();
}


INT8U MCPCAN::readMsg()
{
    INT8U status, res;
   
	
    status = mcp_readStatus();
    
    if ( status & MCP_MESGE_RXB0_MSK )                        
    {
        mcp_readcanMsg( MCP_RXBUF_0);             //0x61
        mcp_modifyRegister(MCPCANINTF, MCP_RX0IF, 0);
        res = CAN_OK;
    }
    else if ( status & MCP_MESGE_RXB1_MSK )               //message in rx buf1                   
    {
        mcp_readcanMsg( MCP_RXBUF_1);
        mcp_modifyRegister(MCPCANINTF, MCP_RX1IF, 0);
        res = CAN_OK;
    }
    else if (status & MCP_MESGE_RXB01_MSK)
    {
        res = CAN_OK;
    }
	else
	{
		res = CAN_NOMSG;
	}
		
    return res;
}

/*!
* @brief: read one data frame from the cache in inner can controler. 
*
* @parameter:  
		
		@len:
			the len of the data to read.
	
		@buf:
			the data out from the Can controler store into the buf.
			
*
* @return the status. if success, return MCP_OK.
*/
INT8U MCPCAN::readMsgBuf(INT8U *len, INT8U *buf)
{
    INT8U  res, i;
    
    res= readMsg();
    
    if (res == CAN_OK) {
       *len = can_Dlc;
       for( i = 0; i<can_Dlc; i++) {
         buf[i] = can_Dta[i];
       } 
    } else {
       	 *len = 0;
    }
    return res;
}
/*!
* @brief: read one data frame from the cache in inner Can controler with the indicated ID, if Can controler has not cached the ID's Frame
	the return value is not CAN_OK.
*
* @parameter:  
		@ID：ID number.
		@len:
			the len of the data to read.
	
		@buf:
			the data out from the Can controler store into the buf.
			
*
* @return the status. if success, return MCP_OK. or this read operation is failed.
*/

INT8U MCPCAN::readMsgBufID(INT32U *ID, INT8U *len, INT8U *buf)
{
    INT8U ret;
	
    ret = readMsg();
    if (ret == CAN_OK) {
       *len = can_Dlc;
       *ID  = can_ID;
       for(int i = 0; i<can_Dlc && i < MAX_MESSAGE_LENGTH; i++) {
          buf[i] = can_Dta[i];
       }
    } else {
       *len = 0;
    }
    return ret;
}
/*!
* @brief: check whether data is cached by Can controler.
*
* @parameter:  
		@ID：ID number.
		@len:
			the len of the data to read.
	
		@buf:
			the data out from the Can controler store into the buf.
			
*
* @return: if there are some data received by Can controller. the return value is CAN_MSGAVAIL, or CAN_NOMSG.
*/

INT8U MCPCAN::checkReceive(void)
{
    INT8U res;
    res = mcp_readStatus();                                         
    if ( res & MCP_MESGE_NO_MSK ) 
    {
        return CAN_MSGAVAIL;
    }
    else 
    {
        return CAN_NOMSG;
    }
}


/*!
* @brief: check whether there is the control error on the Can bus line.
*
* @parameter:  void
			
*
* @return: if control error don't occur, return CAN_OK, or return CAN_CTRLERROR.
*/
INT8U MCPCAN::checkError(void)
{
    INT8U flag = mcp_readRegister(MCP_EFLG);

    if ( flag & MCP_EFLG_ERRORMASK ) 
    {
        return CAN_CTRLERROR;
    }
    else 
    {
        return CAN_OK;
    }
}

/*!
* @brief: get the id of the data cached in Can controller currently.
*
* @parameter: void 
			
*
* @return: return the id number.
*/

INT32U MCPCAN::getCanId(void)
{
    return can_ID;
} 

/*!
* @brief: tell whether the current data frame buffered in Can controller is remote requestion frame.
*
* @parameter: void 
			
*
* @return: return the id number.
*/
INT8U MCPCAN::isRemoteRequest(void)
{
    return can_Rtr;
} 
/*!
* @brief: tell whether the current data frame buffered in Can controller is extended frame.
*
* @parameter: void 
			
*
* @return: return the id number.
*/
INT8U MCPCAN::isExtendedFrame(void)
{
    return can_ExtFlg;
} 

