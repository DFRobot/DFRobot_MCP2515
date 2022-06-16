/*!
 * @file  DFRobot_MCP2515.cpp
 * @brief  Define infrastructure of DFRobot_MCP2515 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Arduinolibrary
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#include "DFRobot_MCP2515.h"


void DFRobot_MCP2515::mcpReset(void)
{
    digitalWrite(_csPin, LOW);
    SPI.transfer(MCP2515_RESET);
    digitalWrite(_csPin, HIGH);
    delay(10);
}

void DFRobot_MCP2515::readReg(const uint8_t RegAddr, uint8_t *buf, uint8_t len)
{
    uint8_t i;

    if ( len > CAN_MAX_MESSAGE_LENGTH)
    {
        len = CAN_MAX_MESSAGE_LENGTH;
    }
    
    digitalWrite(_csPin, LOW);
    SPI.transfer(MCP2515_READ);
    SPI.transfer(RegAddr);

    for (i=0; i < len; i++) {
        buf[i] = SPI.transfer(0x00);
    }
    digitalWrite(_csPin, HIGH);
}

void DFRobot_MCP2515::writeReg(const uint8_t RegAddr, const uint8_t *buf, const uint8_t len)
{
    uint8_t i;
    
    digitalWrite(_csPin, LOW);
    SPI.transfer(MCP2515_WRITE);
    SPI.transfer(RegAddr);
       
    for (i=0; i < len; i++) 
    {
        SPI.transfer(buf[i]);
    }
    digitalWrite(_csPin, HIGH);
}

void DFRobot_MCP2515::modifyReg(const uint8_t RegAddr, const uint8_t mask, const uint8_t data)
{
    digitalWrite(_csPin, LOW);
    SPI.transfer(MCP2515_BITMOD);
    SPI.transfer(RegAddr);
    SPI.transfer(mask);
    SPI.transfer(data);
    digitalWrite(_csPin, HIGH);
}

uint8_t DFRobot_MCP2515::mcpReadStatus(void)
{
    uint8_t ret;

    digitalWrite(_csPin, LOW);
    SPI.transfer(MCP2515_RX_STATUS);
    ret = SPI.transfer(0x00);
    digitalWrite(_csPin, HIGH);
    
    return ret;
}

uint8_t DFRobot_MCP2515::mcpSetMode(const uint8_t newMode)
{
    uint8_t ret;

    modifyReg(MCP2515_CANCTRL, MODE_MASK, newMode);
    readReg(MCP2515_CANCTRL, &ret, 1);
    ret &= MODE_MASK;

    if ( ret == newMode ) 
    {
        return MCP2515_OK;
    }

    return MCP2515_FAIL;

}

uint8_t DFRobot_MCP2515::mcpConfigRate(const uint8_t canSpeed)
{
    uint8_t preSet, cfg1, cfg2, cfg3;
    
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
        writeReg(MCP2515_CNF1, &cfg1, 1);
        writeReg(MCP2515_CNF2, &cfg2, 1);
        writeReg(MCP2515_CNF3, &cfg3, 1);
        return MCP2515_OK;
    }
    else {
        return MCP2515_FAIL;
    }
}

void DFRobot_MCP2515::mcpInitBuffers(void)
{
    uint8_t i, a1, a2, a3;
    uint8_t value = 0;
 
    a1 = MCP2515_TXB0CTRL;
    a2 = MCP2515_TXB1CTRL;
    a3 = MCP2515_TXB2CTRL;
    for (i = 0; i < 14; i++) {
        writeReg(a1, &value, 1);
        writeReg(a2, &value, 1);
        writeReg(a3, &value, 1);
        a1++;
        a2++;
        a3++;
    }
    writeReg(MCP2515_RXB0CTRL, &value, 1);
    writeReg(MCP2515_RXB1CTRL, &value, 1);
}

uint8_t DFRobot_MCP2515::mcpInit(const uint8_t canSpeed)
{
    uint8_t res, value;

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

        value = MCP2515_RX0IF | MCP2515_RX1IF;
        writeReg(MCP2515_CANINTE, &value, 1);

        modifyReg(MCP2515_RXB0CTRL,
        MCP2515_RXB_RX_MASK | MCP2515_RXB_BUKT_MASK,
        MCP2515_RXB_RX_STDEXT | MCP2515_RXB_BUKT_MASK );
        modifyReg(MCP2515_RXB1CTRL, MCP2515_RXB_RX_MASK,
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


void DFRobot_MCP2515::mcpWriteid( const uint8_t mcpAddr, const uint8_t ext, const uint32_t id )
{
    uint16_t canid;
    uint8_t tbufdata[4];

    canid = (uint16_t)(id & 0x0FFFF);

    if ( ext == 1)
    {
        tbufdata[MCP2515_EID0] = (uint8_t) (canid & 0xFF);
        tbufdata[MCP2515_EID8] = (uint8_t) (canid >> 8);
        canid = (uint16_t)(id >> 16);
        tbufdata[MCP2515_SIDL] = (uint8_t) (canid & 0x03);
        tbufdata[MCP2515_SIDL] += (uint8_t) ((canid & 0x1C) << 3);
        tbufdata[MCP2515_SIDL] |= MCP2515_TXB_EXIDE_M;
        tbufdata[MCP2515_SIDH] = (uint8_t) (canid >> 5 );
    }
    else 
    {
        tbufdata[MCP2515_SIDH] = (uint8_t) (canid >> 3 );
        tbufdata[MCP2515_SIDL] = (uint8_t) ((canid & 0x07 ) << 5);
        tbufdata[MCP2515_EID0] = 0;
        tbufdata[MCP2515_EID8] = 0;
    }
    writeReg( mcpAddr, tbufdata, 4 );
}

void DFRobot_MCP2515::mcpReadid( const uint8_t mcpAddr, uint8_t* ext, uint32_t* id )
{
    uint8_t id_Buf[4];

    readReg( mcpAddr, (uint8_t *)id_Buf, 4 );

    *id = (id_Buf[MCP2515_SIDH]<< 3) + (id_Buf[MCP2515_SIDL]>>5);

    if ( (id_Buf[MCP2515_SIDL] & 1 << 3)) 
    {
        *id = (*id<<2) + (id_Buf[MCP2515_SIDL] & 0x03);
        *id = (*id<<8) + id_Buf[MCP2515_EID8];
        *id = (*id<<8) + id_Buf[MCP2515_EID0];
        *ext = 1;
    }
}

void DFRobot_MCP2515::mcpWritecanMsg( const uint8_t sidhAddr)
{
    uint8_t mcpAddr;
    mcpAddr = sidhAddr;
    writeReg(mcpAddr+5, canData, canDlc );
    if ( canRtr == 1)
    {
        canDlc |= MCP2515_RTR_MASK;  
    }
    writeReg((mcpAddr+4), &canDlc, 1);
    mcpWriteid(mcpAddr, canExtFlg, canID );
}

void DFRobot_MCP2515::mcpReadcanMsg( const uint8_t idh_addr)
{

    mcpReadid( idh_addr, &canExtFlg,&canID );

    readReg(idh_addr - 1, &canRtr, 1);
    readReg(idh_addr + 4, &canDlc, 1);

    if ((canRtr & (1 << 3))) {
        canRtr = 1;
    }
    else {
        canRtr = 0;
    }

    canDlc &= MCP2515_DLC_MASK;
    readReg( idh_addr+5, (uint8_t *)canData, canDlc);
}

void DFRobot_MCP2515::mcpStarttransmit(const uint8_t mcpAddr)
{
    modifyReg( mcpAddr-1 , MCP2515_TXB_TXREQ_M, MCP2515_TXB_TXREQ_M );
}

uint8_t DFRobot_MCP2515::mcpGetNextFreeTXBuf(uint8_t *txbuf_n)
{
    uint8_t res, i, ctrlval;
    uint8_t ctrlregs[MCP2515_N_TXBUFFERS] = { MCP2515_TXB0CTRL, MCP2515_TXB1CTRL, MCP2515_TXB2CTRL };

    res = MCP2515_ALLTXBUSY;
    *txbuf_n = 0x00;

    for (i=0; i < MCP2515_N_TXBUFFERS; i++) {
        readReg( ctrlregs[i] , &ctrlval, 1);
        if ( (ctrlval & MCP2515_TXB_TXREQ_M) == 0 ) {
            *txbuf_n = ctrlregs[i]+1;
            res = MCP2515_OK;
            return res;
        }
    }
    return res;
}

DFRobot_MCP2515::DFRobot_MCP2515(uint8_t csPin)
{
    _csPin = csPin;
}

uint8_t DFRobot_MCP2515::begin(uint8_t speedset)
{
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);

    SPI.begin();

    mcpReset();

    uint8_t res;
    res = mcpInit(speedset);
    if (res == MCP2515_OK) return CAN_OK;
    else return CAN_FAILINIT;
}

uint8_t DFRobot_MCP2515::initMask(eMasker_t maskerNum, uint8_t ext, uint32_t ulData)
{
    uint8_t res = MCP2515_OK;  
    
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

uint8_t DFRobot_MCP2515::initFilter(eFilter_t filterNum, uint8_t ext, uint32_t Data)
{
    uint8_t res = MCP2515_OK;  
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

uint8_t DFRobot_MCP2515::setMsg(uint32_t id, uint8_t ext, uint8_t len, uint8_t rtr, uint8_t *pData)
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

uint8_t DFRobot_MCP2515::setMsg(uint32_t id, uint8_t ext, uint8_t len, uint8_t *pData)
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

uint8_t DFRobot_MCP2515::clearMsg(void)
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

uint8_t DFRobot_MCP2515::sendMsg(void)
{
    uint8_t res, txindex;
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
        readReg(txindex, &res, 1);
        res = res & 0x08;
    }while(res && (uiTimeOut < TIMEOUTVALUE));
    if(uiTimeOut == TIMEOUTVALUE)
    {
        return CAN_SENDMSGTIMEOUT;
    }
    return CAN_OK;

}

uint8_t DFRobot_MCP2515::sendMsgBuf(uint32_t id, uint8_t ext, uint8_t rtr, uint8_t len, uint8_t *buf)
{
    setMsg(id, ext, len, rtr, buf);
    return sendMsg();
}

uint8_t DFRobot_MCP2515::sendMsgBuf(uint32_t id, uint8_t ext, uint8_t len, uint8_t *buf)
{
    setMsg(id, ext, len, buf);
    return sendMsg();
}

uint8_t DFRobot_MCP2515::readMsg()
{
    uint8_t status, res;

    status = mcpReadStatus();

    if ( status & MCP2515_MESGE_RXB0_MSK )
    {
        mcpReadcanMsg( MCP2515_RXBUF_0);   // 0x61
        modifyReg(MCP2515_CANINTF, MCP2515_RX0IF, 0);
        res = CAN_OK;
    }
    else if ( status & MCP2515_MESGE_RXB1_MSK )   // message in rx buf1
    {
        mcpReadcanMsg( MCP2515_RXBUF_1);
        modifyReg(MCP2515_CANINTF, MCP2515_RX1IF, 0);
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

uint8_t DFRobot_MCP2515::readMsgBuf(uint8_t *len, uint8_t *buf)
{
    uint8_t  res, i;
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

uint8_t DFRobot_MCP2515::readMsgBufID(uint32_t *ID, uint8_t *len, uint8_t *buf)
{
    uint8_t ret;
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

uint8_t DFRobot_MCP2515::checkReceive(void)
{
    uint8_t res;
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

uint8_t DFRobot_MCP2515::checkError(void)
{
    uint8_t flag;
    readReg(MCP2515_EFLG, &flag, 1);

    if ( flag & MCP2515_EFLG_ERRORMASK ) 
    {
        return CAN_CTRLERROR;
    }
    else 
    {
        return CAN_OK;
    }
}

uint32_t DFRobot_MCP2515::getCanId(void)
{
    return canID;
} 

uint8_t DFRobot_MCP2515::isRemoteRequest(void)
{
    return canRtr;
}

uint8_t DFRobot_MCP2515::isExtendedFrame(void)
{
    return canExtFlg;
}
