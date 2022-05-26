/*!
 * @file  DFRobot_MCP2515.h
 * @brief  Define infrastructure of DFRobot_MCP2515 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Jansion
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#ifndef _DFROBOT_MCP2515_H_
#define _DFROBOT_MCP2515_H_

#include "DFRobot_MCP2515DFS.h"

#define MAX_MESSAGE_LENGTH 8   ///< Maximum information length

class DFRobot_MCP2515
{
public:

    /**
     * @fn DFRobot_MCP2515
     * @brief the DFRobot_MCP2515 class' constructor.
     * @param csPin - indicate the spi select pin when mcu commication with the can controler e.i MCP2515
     * @return None
     */
    DFRobot_MCP2515(INT8U csPin);

    /**
     * @fn begin
     * @brief config the the Can baud rate,  buffer, and interrupt.
     * @param speedset - MCP2515 can config rate
     * @return if successful, it return CAN_OK, or CAN_FAILINIT
     */
    INT8U begin(INT8U speedset);

    /**
     * @fn init
     * @brief initialize the Can controler.
     * @return None
     */
    void  init(void);

    /**
     * @fn initMask
     * @brief initialize the mask register. 
     * @param maskerNum - maybe set MCP2515_RXM0 or MCP2515_RXM1.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param ulData - initialization data
     * @return the status. if success, return MCP2515_OK.
     */
    INT8U initMask(eMasker_t maskerNum, INT8U ext, INT32U ulData);

    /**
     * @fn initFilter
     * @brief initialize the fileter register. 
     * @param filterNum - maybe set MCP2515_RXF0, MCP2515_RXF1、 MCP2515_RXF2、 MCP2515_RXF3、 MCP2515_RXF4、 MCP2515_RXF5.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param Data - fileter data
     * @return the status. if success, return MCP2515_OK.
     */
    INT8U initFilter(eFilter_t filterNum, INT8U ext, INT32U Data);

    /**
     * @fn getCanId
     * @brief get the id of the data cached in Can controller currently.
     * @return return the id number.
     */
    INT32U getCanId(void);

    /**
     * @fn isRemoteRequest
     * @brief tell whether the current data frame buffered in Can controller is remote requestion frame.
     * @return return the id number.
     */
    INT8U isRemoteRequest(void);

    /**
     * @fn isExtendedFrame
     * @brief tell whether the current data frame buffered in Can controller is extended frame.
     * @return return the id number.
     */
    INT8U isExtendedFrame(void);

    /**
     * @fn checkReceive
     * @brief check whether data is cached by Can controler.
     * @return if there are some data received by Can controller. the return value is CAN_MSGAVAIL, or CAN_NOMSG.
     */
    INT8U checkReceive(void);

    /**
     * @fn checkError
     * @brief check whether there is the control error on the Can bus line.
     * @return if control error don't occur, return CAN_OK, or return CAN_CTRLERROR.
     */
    INT8U checkError(void);

    /**
     * @fn sendMsgBuf
     * @brief send one data frame.
     * @param id - the message id num.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param len - the len of the data to send.
     * @param buf - the data to send.
     * @return the status. if success, return MCP2515_OK.
     */
    INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf);

    /**
     * @fn sendMsgBuf
     * @brief send the remote requestion message. 
     * @param id - the message id num. 
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param len - the len of the data to send.
     * @param rtr - the flag of the remote requestion. if rtr = 1, the frame seem as the remote requestion frame , or the frame is the normal data frame..
     * @param buf - the data to send.
     * @return the status. if success, return MCP2515_OK.
     */
    INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U rtr, INT8U len, INT8U *buf);

    /**
     * @fn readMsgBuf
     * @brief read one data frame from the cache in inner can controler. 
     * @param len - the len of the data to read.
     * @param buf - the data out from the Can controler store into the buf.
     * @return the status. if success, return MCP2515_OK.
     */
    INT8U readMsgBuf(INT8U *len, INT8U *buf);

    /**
     * @fn readMsgBufID
     * @brief read one data frame from the cache in inner Can controler with the indicated ID, 
     * @n  if Can controler has not cached the ID's Frame the return value is not CAN_OK.
     * @param ID - ID number.
     * @param len - the len of the data to read.
     * @param buf - the data out from the Can controler store into the buf.
     * @return the status. if success, return MCP2515_OK. or this read operation is failed.
     */
    INT8U readMsgBufID(INT32U *ID, INT8U *len, INT8U *buf);

private:

    void mcpReset(void);
    INT8U mcpReadRegister(const INT8U RegAddr);
    void mcpReadMulitiRegisters(const INT8U RegAddr, INT8U *buf, INT8U len);
    void mcpSetRegister(const INT8U RegAddr, const INT8U value);
    void mcpSetMulitRegisterS(const INT8U RegAddr, const INT8U *buf, const INT8U len);
    void mcpInitBuffers(void);
    void mcpModifyRegister(const INT8U RegAddr, const INT8U mask, const INT8U data);
    INT8U mcpReadStatus(void);
    INT8U mcpSetMode(const INT8U newMode);
    INT8U mcpConfigRate(const INT8U canSpeed);
    INT8U mcpInit(const INT8U canSpeed);
    void mcpWriteid( const INT8U mcpAddr, const INT8U ext, const INT32U id );
    void mcpReadid( const INT8U mcpAddr, INT8U* ext, INT32U* id );
    void mcpWritecanMsg( const INT8U sidhAddr );
    void mcpReadcanMsg( const INT8U sidhAddr);
    void mcpStarttransmit(const INT8U mcpAddr);
    INT8U mcpGetNextFreeTXBuf(INT8U *txbuf_n);
    INT8U setMsg(INT32U id, INT8U ext, INT8U len, INT8U rtr, INT8U *pData);
    INT8U setMsg(INT32U id, INT8U ext, INT8U len, INT8U *pData);
    INT8U clearMsg(void);
    INT8U readMsg(void);
    INT8U sendMsg(void);

private:

    INT8U   canExtFlg;
    INT32U  canID;
    INT8U   canDlc;
    INT8U   canData[MAX_MESSAGE_LENGTH];
    INT8U   canRtr;
    INT8U   canFilhit;
    INT8U   _csPin;
};

#endif
