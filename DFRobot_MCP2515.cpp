/*!
 * @file  DFRobot_MCP2515.cpp
 * @brief  Define infrastructure of DFRobot_MCP2515 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Jansion
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#include "DFRobot_MCP2515.h"

#define ReadWriteOneByte SPI.transfer
#define Read() SPI.transfer(0x00)

void DFRobot_MCP2515::mcpReset(void)
{
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_RESET);
    MCP2515_SPI_UNSELECT();
    delay(10);
}

INT8U DFRobot_MCP2515::mcpReadRegister(const INT8U RegAddr)
{
    INT8U ret;

    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_READ);
    ReadWriteOneByte(RegAddr);
    ret = Read();
    MCP2515_SPI_UNSELECT();

    return ret;
}

void DFRobot_MCP2515::mcpReadMulitiRegisters(const INT8U RegAddr, INT8U *buf, INT8U len)
{
    INT8U i;

    if ( len > CAN_MAX_MESSAGE_LENGTH)
    {
        len = CAN_MAX_MESSAGE_LENGTH;
    }
    
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_READ);
    ReadWriteOneByte(RegAddr);

    for (i=0; i < len; i++) {
        buf[i] = Read();
    }
    MCP2515_SPI_UNSELECT();
}

void DFRobot_MCP2515::mcpSetRegister(const INT8U RegAddr, const INT8U value)
{
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_WRITE);
    ReadWriteOneByte(RegAddr);
    ReadWriteOneByte(value);
    MCP2515_SPI_UNSELECT();
}

void DFRobot_MCP2515::mcpSetMulitRegisterS(const INT8U RegAddr, const INT8U *buf, const INT8U len)
{
    INT8U i;
    
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_WRITE);
    ReadWriteOneByte(RegAddr);
       
    for (i=0; i < len; i++) 
    {
        ReadWriteOneByte(buf[i]);
    }
    MCP2515_SPI_UNSELECT();
}

void DFRobot_MCP2515::mcpModifyRegister(const INT8U RegAddr, const INT8U mask, const INT8U data)
{
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_BITMOD);
    ReadWriteOneByte(RegAddr);
    ReadWriteOneByte(mask);
    ReadWriteOneByte(data);
    MCP2515_SPI_UNSELECT();
}

INT8U DFRobot_MCP2515::mcpReadStatus(void)
{
    INT8U ret;
    
    MCP2515_SPI_SELECT();
    ReadWriteOneByte(MCP2515_RX_STATUS);
    ret = Read();
    MCP2515_SPI_UNSELECT();
    
    return ret;
}

INT8U DFRobot_MCP2515::mcpSetMode(const INT8U newMode)
{
    INT8U ret;

    mcpModifyRegister(MCP2515_CANCTRL, MODE_MASK, newMode);
    ret = mcpReadRegister(MCP2515_CANCTRL);
    ret &= MODE_MASK;

    if ( ret == newMode ) 
    {
        return MCP2515_OK;
    }

    return MCP2515_FAIL;

}

INT8U DFRobot_MCP2515::mcpConfigRate(const INT8U canSpeed)
{
    INT8U preSet, cfg1, cfg2, cfg3;
    
    preSet = 0;
    switch (canSpeed) 
    {
        case (CAN_5KBPS):
        cfg1 = MCP2515_16MHz_5kBPS_CFG1;
        cfg2 = MCP2515_16MHz_5kBPS_CFG2;
        cfg3 = MCP2515_16MHz_5kBPS_CFG3;
        break;

        case (CAN_10KBPS):
        cfg1 = MCP2515_16MHz_10kBPS_CFG1;
        cfg2 = MCP2515_16MHz_10kBPS_CFG2;
        cfg3 = MCP2515_16MHz_10kBPS_CFG3;
        break;

        case (CAN_20KBPS):
        cfg1 = MCP2515_16MHz_20kBPS_CFG1;
        cfg2 = MCP2515_16MHz_20kBPS_CFG2;
        cfg3 = MCP2515_16MHz_20kBPS_CFG3;
        break;
        
        case (CAN_31K25BPS):
        cfg1 = MCP2515_16MHz_31k25BPS_CFG1;
        cfg2 = MCP2515_16MHz_31k25BPS_CFG2;
        cfg3 = MCP2515_16MHz_31k25BPS_CFG3;
        break;

        case (CAN_33KBPS):
        cfg1 = MCP2515_16MHz_33kBPS_CFG1;
        cfg2 = MCP2515_16MHz_33kBPS_CFG2;
        cfg3 = MCP2515_16MHz_33kBPS_CFG3;
        break;

        case (CAN_40KBPS):
        cfg1 = MCP2515_16MHz_40kBPS_CFG1;
        cfg2 = MCP2515_16MHz_40kBPS_CFG2;
        cfg3 = MCP2515_16MHz_40kBPS_CFG3;
        break;

        case (CAN_50KBPS):
        cfg1 = MCP2515_16MHz_50kBPS_CFG1;
        cfg2 = MCP2515_16MHz_50kBPS_CFG2;
        cfg3 = MCP2515_16MHz_50kBPS_CFG3;
        break;

        case (CAN_80KBPS):
        cfg1 = MCP2515_16MHz_80kBPS_CFG1;
        cfg2 = MCP2515_16MHz_80kBPS_CFG2;
        cfg3 = MCP2515_16MHz_80kBPS_CFG3;
        break;

        case (CAN_83K3BPS):
        cfg1 = MCP2515_16MHz_83k3BPS_CFG1;
        cfg2 = MCP2515_16MHz_83k3BPS_CFG2;
        cfg3 = MCP2515_16MHz_83k3BPS_CFG3;
        break;  

        case (CAN_95KBPS):
        cfg1 = MCP2515_16MHz_95kBPS_CFG1;
        cfg2 = MCP2515_16MHz_95kBPS_CFG2;
        cfg3 = MCP2515_16MHz_95kBPS_CFG3;
        break;

        case (CAN_100KBPS):
        cfg1 = MCP2515_16MHz_100kBPS_CFG1;
        cfg2 = MCP2515_16MHz_100kBPS_CFG2;
        cfg3 = MCP2515_16MHz_100kBPS_CFG3;
        break;

        case (CAN_125KBPS):
        cfg1 = MCP2515_16MHz_125kBPS_CFG1;
        cfg2 = MCP2515_16MHz_125kBPS_CFG2;
        cfg3 = MCP2515_16MHz_125kBPS_CFG3;
        break;

        case (CAN_200KBPS):
        cfg1 = MCP2515_16MHz_200kBPS_CFG1;
        cfg2 = MCP2515_16MHz_200kBPS_CFG2;
        cfg3 = MCP2515_16MHz_200kBPS_CFG3;
        break;

        case (CAN_250KBPS):
        cfg1 = MCP2515_16MHz_250kBPS_CFG1;
        cfg2 = MCP2515_16MHz_250kBPS_CFG2;
        cfg3 = MCP2515_16MHz_250kBPS_CFG3;
        break;

        case (CAN_500KBPS):
        cfg1 = MCP2515_16MHz_500kBPS_CFG1;
        cfg2 = MCP2515_16MHz_500kBPS_CFG2;
        cfg3 = MCP2515_16MHz_500kBPS_CFG3;
        break;
        
        case (CAN_1000KBPS):
        cfg1 = MCP2515_16MHz_1000kBPS_CFG1;
        cfg2 = MCP2515_16MHz_1000kBPS_CFG2;
        cfg3 = MCP2515_16MHz_1000kBPS_CFG3;
        break;  

        default:
        preSet = 1;
        break;
    }

    if (!preSet) {
        mcpSetRegister(MCP2515_CNF1, cfg1);
        mcpSetRegister(MCP2515_CNF2, cfg2);
        mcpSetRegister(MCP2515_CNF3, cfg3);
        return MCP2515_OK;
    }
    else {
        return MCP2515_FAIL;
    }
}

void DFRobot_MCP2515::mcpInitBuffers(void)
{
    INT8U i, a1, a2, a3;
 
    a1 = MCP2515_TXB0CTRL;
    a2 = MCP2515_TXB1CTRL;
    a3 = MCP2515_TXB2CTRL;
    for (i = 0; i < 14; i++) {
        mcpSetRegister(a1, 0);
        mcpSetRegister(a2, 0);
        mcpSetRegister(a3, 0);
        a1++;
        a2++;
        a3++;
    }
    mcpSetRegister(MCP2515_RXB0CTRL, 0);
    mcpSetRegister(MCP2515_RXB1CTRL, 0);
}

INT8U DFRobot_MCP2515::mcpInit(const INT8U canSpeed)
{
    INT8U res;

    res = mcpSetMode(MODE_CONFIG);
    if(res > 0)
    {
      delay(10);
      return res;
    }
    delay(10);

    if(mcpConfigRate(canSpeed))
    {
      delay(10);
      return res;
    }
    delay(10);

    if ( res == MCP2515_OK ) {

        mcpInitBuffers();

        mcpSetRegister(MCP2515_CANINTE, MCP2515_RX0IF | MCP2515_RX1IF);

        mcpModifyRegister(MCP2515_RXB0CTRL,
        MCP2515_RXB_RX_MASK | MCP2515_RXB_BUKT_MASK,
        MCP2515_RXB_RX_STDEXT | MCP2515_RXB_BUKT_MASK );
        mcpModifyRegister(MCP2515_RXB1CTRL, MCP2515_RXB_RX_MASK,
        MCP2515_RXB_RX_STDEXT);
        res = mcpSetMode(MODE_NORMAL);
        if(res)
        {  
          delay(10);
          return res;
        }

        delay(10);

    }
    return res;
}


void DFRobot_MCP2515::mcpWriteid( const INT8U mcpAddr, const INT8U ext, const INT32U id )
{
    uint16_t canid;
    INT8U tbufdata[4];

    canid = (uint16_t)(id & 0x0FFFF);

    if ( ext == 1)
    {
        tbufdata[MCP2515_EID0] = (INT8U) (canid & 0xFF);
        tbufdata[MCP2515_EID8] = (INT8U) (canid >> 8);
        canid = (uint16_t)(id >> 16);
        tbufdata[MCP2515_SIDL] = (INT8U) (canid & 0x03);
        tbufdata[MCP2515_SIDL] += (INT8U) ((canid & 0x1C) << 3);
        tbufdata[MCP2515_SIDL] |= MCP2515_TXB_EXIDE_M;
        tbufdata[MCP2515_SIDH] = (INT8U) (canid >> 5 );
    }
    else 
    {
        tbufdata[MCP2515_SIDH] = (INT8U) (canid >> 3 );
        tbufdata[MCP2515_SIDL] = (INT8U) ((canid & 0x07 ) << 5);
        tbufdata[MCP2515_EID0] = 0;
        tbufdata[MCP2515_EID8] = 0;
    }
    mcpSetMulitRegisterS( mcpAddr, tbufdata, 4 );
}

void DFRobot_MCP2515::mcpReadid( const INT8U mcpAddr, INT8U* ext, INT32U* id )
{
    INT8U id_Buf[4];

    mcpReadMulitiRegisters( mcpAddr, (INT8U *)id_Buf, 4 );

    *id = (id_Buf[MCP2515_SIDH]<< 3) + (id_Buf[MCP2515_SIDL]>>5);

    if ( (id_Buf[MCP2515_SIDL] & 1 << 3)) 
    {
        *id = (*id<<2) + (id_Buf[MCP2515_SIDL] & 0x03);
        *id = (*id<<8) + id_Buf[MCP2515_EID8];
        *id = (*id<<8) + id_Buf[MCP2515_EID0];
        *ext = 1;
    }
}

void DFRobot_MCP2515::mcpWritecanMsg( const INT8U sidhAddr)
{
    INT8U mcpAddr;
    mcpAddr = sidhAddr;
    mcpSetMulitRegisterS(mcpAddr+5, canData, canDlc );
    if ( canRtr == 1)
    {
        canDlc |= MCP2515_RTR_MASK;  
    }
    mcpSetRegister((mcpAddr+4), canDlc );
    mcpWriteid(mcpAddr, canExtFlg, canID );
}

void DFRobot_MCP2515::mcpReadcanMsg( const INT8U idh_addr)
{

    mcpReadid( idh_addr, &canExtFlg,&canID );

    canRtr = mcpReadRegister( idh_addr - 1 );
    canDlc = mcpReadRegister( idh_addr + 4 );

    if ((canRtr & (1 << 3))) {
        canRtr = 1;
    }
    else {
        canRtr = 0;
    }

    canDlc &= MCP2515_DLC_MASK;
    mcpReadMulitiRegisters( idh_addr+5, (INT8U *)canData, canDlc);
}

void DFRobot_MCP2515::mcpStarttransmit(const INT8U mcpAddr)
{
    mcpModifyRegister( mcpAddr-1 , MCP2515_TXB_TXREQ_M, MCP2515_TXB_TXREQ_M );
}

INT8U DFRobot_MCP2515::mcpGetNextFreeTXBuf(INT8U *txbuf_n)
{
    INT8U res, i, ctrlval;
    INT8U ctrlregs[MCP2515_N_TXBUFFERS] = { MCP2515_TXB0CTRL, MCP2515_TXB1CTRL, MCP2515_TXB2CTRL };

    res = MCP2515_ALLTXBUSY;
    *txbuf_n = 0x00;

    for (i=0; i < MCP2515_N_TXBUFFERS; i++) {
        ctrlval = mcpReadRegister( ctrlregs[i] );
        if ( (ctrlval & MCP2515_TXB_TXREQ_M) == 0 ) {
            *txbuf_n = ctrlregs[i]+1;
            res = MCP2515_OK;
            return res;
        }
    }
    return res;
}

DFRobot_MCP2515::DFRobot_MCP2515(INT8U csPin)
{
    _csPin = csPin;
    pinMode(_csPin, OUTPUT);
    MCP2515_SPI_UNSELECT();
}

void DFRobot_MCP2515::init(void)
{
    SPI.begin();
    mcpReset();
}

INT8U DFRobot_MCP2515::begin(INT8U speedset)
{
    INT8U res;
    
    res = mcpInit(speedset);
    if (res == MCP2515_OK) return CAN_OK;
    else return CAN_FAILINIT;
}

INT8U DFRobot_MCP2515::initMask(eMasker_t maskerNum, INT8U ext, INT32U ulData)
{
    INT8U res = MCP2515_OK;  
    
    delay(10);
    res = mcpSetMode(MODE_CONFIG);
    if(res > 0){
    delay(10);
    return res;
    }
    
    if (maskerNum == MCP2515_RXM0){
        mcpWriteid(MCP2515_RXM0SIDH, ext, ulData);

    }
    else if(maskerNum == MCP2515_RXM1){
        mcpWriteid(MCP2515_RXM1SIDH, ext, ulData);
    }
    else res =  MCP2515_FAIL;
    
    res = mcpSetMode(MODE_NORMAL);
    if(res > 0){

    delay(10);
    return res;
  }  
    delay(10);
    return res;
}

INT8U DFRobot_MCP2515::initFilter(eFilter_t filterNum, INT8U ext, INT32U Data)
{
    INT8U res = MCP2515_OK;  
    delay(10);

    res = mcpSetMode(MODE_CONFIG);

    if(res > 0)
    {
      delay(10);
      return res;
    }

    switch( filterNum )
    {
        case MCP2515_RXF0:

        mcpWriteid(MCP2515_RXF0SIDH, ext, Data);
        break;

        case MCP2515_RXF1:
        mcpWriteid(MCP2515_RXF1SIDH, ext, Data);
        break;

        case MCP2515_RXF2:
        mcpWriteid(MCP2515_RXF2SIDH, ext, Data);
        break;

        case MCP2515_RXF3:
        mcpWriteid(MCP2515_RXF3SIDH, ext, Data);
        break;

        case MCP2515_RXF4:
        mcpWriteid(MCP2515_RXF4SIDH, ext, Data);
        break;

        case MCP2515_RXF5:
        mcpWriteid(MCP2515_RXF5SIDH, ext, Data);
        break;

        default:
        res = MCP2515_FAIL;
    }
    
    res = mcpSetMode(MODE_NORMAL);
    if(res > 0)
    {  
      delay(10);
      return res;
    }  
    
    delay(10);

    return res;
}

INT8U DFRobot_MCP2515::setMsg(INT32U id, INT8U ext, INT8U len, INT8U rtr, INT8U *pData)
{
    int i = 0;
    canExtFlg = ext;
    canID     = id;
    canDlc    = len;
    canRtr    = rtr;
    for(i = 0; i < MAX_MESSAGE_LENGTH; i++)
    {
        canData[i] = pData[i];
    }
    return MCP2515_OK;
}

INT8U DFRobot_MCP2515::setMsg(INT32U id, INT8U ext, INT8U len, INT8U *pData)
{
    int i = 0;
    canExtFlg = ext;
    canID     = id;
    canDlc    = len;
    for(i = 0; i < MAX_MESSAGE_LENGTH; i++)
    {
        canData[i] = *(pData+i);
    }
    return MCP2515_OK;
}

INT8U DFRobot_MCP2515::clearMsg(void)
{

    canID       = 0;
    canRtr      = 0;
    canExtFlg   = 0;
    canFilhit   = 0;
    canDlc      = 0;
    for(int i = 0; i<canDlc; i++ )
      canData[i] = 0x00;

    return MCP2515_OK;
}

INT8U DFRobot_MCP2515::sendMsg(void)
{
    INT8U res, txindex;
    uint16_t uiTimeOut = 0;

    do {
        res = mcpGetNextFreeTXBuf(&txindex);
        uiTimeOut++;
    } while (res == MCP2515_ALLTXBUSY && (uiTimeOut < TIMEOUTVALUE));

    if(uiTimeOut == TIMEOUTVALUE)
    {   
        return CAN_GETTXBFTIMEOUT;
    }
    uiTimeOut = 0;
    mcpWritecanMsg( txindex);
    mcpStarttransmit( txindex );
    do
    {
        uiTimeOut++;
        res = mcpReadRegister(txindex);
        res = res & 0x08;
    }while(res && (uiTimeOut < TIMEOUTVALUE));
    if(uiTimeOut == TIMEOUTVALUE)
    {
        return CAN_SENDMSGTIMEOUT;
    }
    return CAN_OK;

}

INT8U DFRobot_MCP2515::sendMsgBuf(INT32U id, INT8U ext, INT8U rtr, INT8U len, INT8U *buf)
{
    setMsg(id, ext, len, rtr, buf);
    return sendMsg();
}

INT8U DFRobot_MCP2515::sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf)
{
    setMsg(id, ext, len, buf);
    return sendMsg();
}

INT8U DFRobot_MCP2515::readMsg()
{
    INT8U status, res;

    status = mcpReadStatus();

    if ( status & MCP2515_MESGE_RXB0_MSK )
    {
        mcpReadcanMsg( MCP2515_RXBUF_0);   // 0x61
        mcpModifyRegister(MCP2515_CANINTF, MCP2515_RX0IF, 0);
        res = CAN_OK;
    }
    else if ( status & MCP2515_MESGE_RXB1_MSK )   // message in rx buf1
    {
        mcpReadcanMsg( MCP2515_RXBUF_1);
        mcpModifyRegister(MCP2515_CANINTF, MCP2515_RX1IF, 0);
        res = CAN_OK;
    }
    else if (status & MCP2515_MESGE_RXB01_MSK)
    {
        res = CAN_OK;
    }
    else
    {
        res = CAN_NOMSG;
    }
    return res;
}

INT8U DFRobot_MCP2515::readMsgBuf(INT8U *len, INT8U *buf)
{
    INT8U  res, i;
    res= readMsg();
    if (res == CAN_OK) {
       *len = canDlc;
       for( i = 0; i<canDlc; i++) {
         buf[i] = canData[i];
       } 
    } else {
            *len = 0;
    }
    return res;
}

INT8U DFRobot_MCP2515::readMsgBufID(INT32U *ID, INT8U *len, INT8U *buf)
{
    INT8U ret;
    ret = readMsg();
    if (ret == CAN_OK) {
       *len = canDlc;
       *ID  = canID;
       for(int i = 0; i<canDlc && i < MAX_MESSAGE_LENGTH; i++) {
          buf[i] = canData[i];
       }
    } else {
       *len = 0;
    }
    return ret;
}

INT8U DFRobot_MCP2515::checkReceive(void)
{
    INT8U res;
    res = mcpReadStatus();
    if ( res & MCP2515_MESGE_NO_MSK ) 
    {
        return CAN_MSGAVAIL;
    }
    else 
    {
        return CAN_NOMSG;
    }
}

INT8U DFRobot_MCP2515::checkError(void)
{
    INT8U flag = mcpReadRegister(MCP2515_EFLG);

    if ( flag & MCP2515_EFLG_ERRORMASK ) 
    {
        return CAN_CTRLERROR;
    }
    else 
    {
        return CAN_OK;
    }
}

INT32U DFRobot_MCP2515::getCanId(void)
{
    return canID;
} 

INT8U DFRobot_MCP2515::isRemoteRequest(void)
{
    return canRtr;
}

INT8U DFRobot_MCP2515::isExtendedFrame(void)
{
    return canExtFlg;
}
