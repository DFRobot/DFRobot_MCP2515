/*!
 * @file  DFRobot_MCP2515.h
 * @brief  Define infrastructure of DFRobot_MCP2515 class
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  Arduinolibrary
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2022-05-25
 * @url  https://github.com/DFRobot/DFRobot_MCP2515
 */
#ifndef _DFROBOT_MCP2515_H_
#define _DFROBOT_MCP2515_H_

#include <Arduino.h>
#include <SPI.h>
#include <inttypes.h>

#define TIMEOUTVALUE   50
#define MCP2515_SIDH   0
#define MCP2515_SIDL   1
#define MCP2515_EID8   2
#define MCP2515_EID0   3

#define MCP2515_TXB_EXIDE_M     0x08
#define MCP2515_DLC_MASK        0x0F
#define MCP2515_RTR_MASK        0x40

#define MCP2515_RXB_RX_ANY      0x60
#define MCP2515_RXB_RX_EXT      0x40
#define MCP2515_RXB_RX_STD      0x20
#define MCP2515_RXB_RX_STDEXT   0x00
#define MCP2515_RXB_RX_MASK     0x60
#define MCP2515_RXB_BUKT_MASK   (1<<2)

#define MCP2515_TXB_TXBUFE_M    0x80
#define MCP2515_TXB_ABTF_M      0x40
#define MCP2515_TXB_MLOA_M      0x20
#define MCP2515_TXB_TXERR_M     0x10
#define MCP2515_TXB_TXREQ_M     0x08
#define MCP2515_TXB_TXIE_M      0x04
#define MCP2515_TXB_TXP10_M     0x03

#define MCP2515_TXB_RTR_M       0x40
#define MCP2515_RXB_IDE_M       0x08
#define MCP2515_RXB_RTR_M       0x40

#define MCP2515_STAT_RXIF_MASK (0x03)
#define MCP2515_STAT_RX0IF     (1<<0)
#define MCP2515_STAT_RX1IF     (1<<1)

#define MCP2515_EFLG_RX1OVR    (1<<7)
#define MCP2515_EFLG_RX0OVR    (1<<6)
#define MCP2515_EFLG_TXBO      (1<<5)
#define MCP2515_EFLG_TXEP      (1<<4)
#define MCP2515_EFLG_RXEP      (1<<3)
#define MCP2515_EFLG_TXWAR     (1<<2)
#define MCP2515_EFLG_RXWAR     (1<<1)
#define MCP2515_EFLG_EWARN     (1<<0)
#define MCP2515_EFLG_ERRORMASK (0xF8)

#define MCP2515_RXF0SIDH    0x00
#define MCP2515_RXF0SIDL    0x01
#define MCP2515_RXF0EID8    0x02
#define MCP2515_RXF0EID0    0x03
#define MCP2515_RXF1SIDH    0x04
#define MCP2515_RXF1SIDL    0x05
#define MCP2515_RXF1EID8    0x06
#define MCP2515_RXF1EID0    0x07
#define MCP2515_RXF2SIDH    0x08
#define MCP2515_RXF2SIDL    0x09
#define MCP2515_RXF2EID8    0x0A
#define MCP2515_RXF2EID0    0x0B
#define MCP2515_CANSTAT      0x0E
#define MCP2515_CANCTRL      0x0F
#define MCP2515_RXF3SIDH    0x10
#define MCP2515_RXF3SIDL    0x11
#define MCP2515_RXF3EID8    0x12
#define MCP2515_RXF3EID0    0x13
#define MCP2515_RXF4SIDH    0x14
#define MCP2515_RXF4SIDL    0x15
#define MCP2515_RXF4EID8    0x16
#define MCP2515_RXF4EID0    0x17
#define MCP2515_RXF5SIDH    0x18
#define MCP2515_RXF5SIDL    0x19
#define MCP2515_RXF5EID8    0x1A
#define MCP2515_RXF5EID0    0x1B
#define MCP2515_TEC         0x1C
#define MCP2515_REC         0x1D
#define MCP2515_RXM0SIDH    0x20
#define MCP2515_RXM0SIDL    0x21
#define MCP2515_RXM0EID8    0x22
#define MCP2515_RXM0EID0    0x23
#define MCP2515_RXM1SIDH    0x24
#define MCP2515_RXM1SIDL    0x25
#define MCP2515_RXM1EID8    0x26
#define MCP2515_RXM1EID0    0x27
#define MCP2515_CNF3        0x28
#define MCP2515_CNF2        0x29
#define MCP2515_CNF1        0x2A
#define MCP2515_CANINTE      0x2B
#define MCP2515_CANINTF      0x2C
#define MCP2515_EFLG        0x2D
#define MCP2515_TXB0CTRL    0x30
#define MCP2515_TXB1CTRL    0x40
#define MCP2515_TXB2CTRL    0x50
#define MCP2515_RXB0CTRL    0x60
#define MCP2515_RXB0SIDH    0x61
#define MCP2515_RXB1CTRL    0x70
#define MCP2515_RXB1SIDH    0x71

#define MCP2515_TX_INT          0x1C
#define MCP2515_TX01_INT        0x0C
#define MCP2515_RX_INT          0x03
#define MCP2515_NO_INT          0x00

#define MCP2515_TX01_MASK       0x14
#define MCP2515_TX_MASK         0x54

#define MCP2515_WRITE           0x02

#define MCP2515_READ            0x03

#define MCP2515_BITMOD          0x05

#define MCP2515_LOAD_TX0        0x40
#define MCP2515_LOAD_TX1        0x42
#define MCP2515_LOAD_TX2        0x44

#define MCP2515_RTS_TX0         0x81
#define MCP2515_RTS_TX1         0x82
#define MCP2515_RTS_TX2         0x84
#define MCP2515_RTS_ALL         0x87

#define MCP2515_READ_RX0        0x90
#define MCP2515_READ_RX1        0x94

#define MCP2515_READ_STATUS     0xA0

#define MCP2515_RX_STATUS       0xB0

/* Rx STATUS INSTRUCTION */
/* bit 7:6 */
#define MCP2515_MESGE_NO_MSK    (3 << 6)
#define MCP2515_MESGE_RXB0_MSK  (1 << 6)
#define MCP2515_MESGE_RXB1_MSK  (2 << 6)
#define MCP2515_MESGE_RXB01_MSK (3 << 6)
/* bit 4:3 */
#define MCP2515_FRAME_STDDF_MASK    (0 << 3)
#define MCP2515_FRAME_REMOTERF_MASK (1 << 3)
#define MCP2515_FRAME_EXTDF_MASK    (2 << 3)
#define MCP2515_FRAME_EXTRF_MASK    (3 << 3)
/* bit 2:0 */
#define MCP2515_FILMATCH_STD_MSK   (0x7FF < 0)
#define MCP2515_FILMATCH_EXT_MSK   (0x7FFFF < 0)

#define MCP2515_RESET   0xC0

#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP    0xE0
#define MODE_MASK       0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT    0x08
#define CLKOUT_ENABLE   0x04
#define CLKOUT_DISABLE  0x00
#define CLKOUT_PS1      0x00
#define CLKOUT_PS2      0x01
#define CLKOUT_PS4      0x02
#define CLKOUT_PS8      0x03

#define SJW1            0x00
#define SJW2            0x40
#define SJW3            0x80
#define SJW4            0xC0

#define BTLMODE         0x80
#define SAMPLE_1X       0x00
#define SAMPLE_3X       0x40

#define SOF_ENABLE      0x80
#define SOF_DISABLE     0x00
#define WAKFIL_ENABLE   0x40
#define WAKFIL_DISABLE  0x00

#define MCP2515_RX0IF   0x01
#define MCP2515_RX1IF   0x02
#define MCP2515_TX0IF   0x04
#define MCP2515_TX1IF   0x08
#define MCP2515_TX2IF   0x10
#define MCP2515_ERRIF   0x20
#define MCP2515_WAKIF   0x40
#define MCP2515_MERRF   0x80

#define MCP2515_16MHz_1000kBPS_CFG1 (0x00)
#define MCP2515_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP2515_16MHz_1000kBPS_CFG3 (0x82)

#define MCP2515_16MHz_500kBPS_CFG1  (0x00)
#define MCP2515_16MHz_500kBPS_CFG2  (0xF0)
#define MCP2515_16MHz_500kBPS_CFG3  (0x86)

#define MCP2515_16MHz_250kBPS_CFG1  (0x41)
#define MCP2515_16MHz_250kBPS_CFG2  (0xF1)
#define MCP2515_16MHz_250kBPS_CFG3  (0x85)

#define MCP2515_16MHz_200kBPS_CFG1  (0x01)
#define MCP2515_16MHz_200kBPS_CFG2  (0xFA)
#define MCP2515_16MHz_200kBPS_CFG3  (0x87)

#define MCP2515_16MHz_125kBPS_CFG1  (0x03)
#define MCP2515_16MHz_125kBPS_CFG2  (0xF0)
#define MCP2515_16MHz_125kBPS_CFG3  (0x86)

#define MCP2515_16MHz_100kBPS_CFG1  (0x03)
#define MCP2515_16MHz_100kBPS_CFG2  (0xFA)
#define MCP2515_16MHz_100kBPS_CFG3  (0x87)

#define MCP2515_16MHz_95kBPS_CFG1   (0x03)
#define MCP2515_16MHz_95kBPS_CFG2   (0xAD)
#define MCP2515_16MHz_95kBPS_CFG3   (0x07)

#define MCP2515_16MHz_83k3BPS_CFG1  (0x03)
#define MCP2515_16MHz_83k3BPS_CFG2  (0xBE)
#define MCP2515_16MHz_83k3BPS_CFG3  (0x07)

#define MCP2515_16MHz_80kBPS_CFG1   (0x03)
#define MCP2515_16MHz_80kBPS_CFG2   (0xFF)
#define MCP2515_16MHz_80kBPS_CFG3   (0x87)

#define MCP2515_16MHz_50kBPS_CFG1   (0x07)
#define MCP2515_16MHz_50kBPS_CFG2   (0xFA)
#define MCP2515_16MHz_50kBPS_CFG3   (0x87)

#define MCP2515_16MHz_40kBPS_CFG1   (0x07)
#define MCP2515_16MHz_40kBPS_CFG2   (0xFF)
#define MCP2515_16MHz_40kBPS_CFG3   (0x87)

#define MCP2515_16MHz_33kBPS_CFG1   (0x09)
#define MCP2515_16MHz_33kBPS_CFG2   (0xBE)
#define MCP2515_16MHz_33kBPS_CFG3   (0x07)

#define MCP2515_16MHz_31k25BPS_CFG1 (0x0F)
#define MCP2515_16MHz_31k25BPS_CFG2 (0xF1)
#define MCP2515_16MHz_31k25BPS_CFG3 (0x85)

#define MCP2515_16MHz_20kBPS_CFG1   (0x0F)
#define MCP2515_16MHz_20kBPS_CFG2   (0xFF)
#define MCP2515_16MHz_20kBPS_CFG3   (0x87)

#define MCP2515_16MHz_10kBPS_CFG1   (0x1F)
#define MCP2515_16MHz_10kBPS_CFG2   (0xFF)
#define MCP2515_16MHz_10kBPS_CFG3   (0x87)

#define MCP2515_16MHz_5kBPS_CFG1    (0x3F)
#define MCP2515_16MHz_5kBPS_CFG2    (0xFF)
#define MCP2515_16MHz_5kBPS_CFG3    (0x87)

#define MCP2515DEBUG        (0)
#define MCP2515DEBUG_TXBUF  (0)
#define MCP2515_N_TXBUFFERS (3)

#define MCP2515_RXBUF_0 (MCP2515_RXB0SIDH)
#define MCP2515_RXBUF_1 (MCP2515_RXB1SIDH)

#define MCP2515_OK         (0)
#define MCP2515_FAIL       (1)
#define MCP2515_ALLTXBUSY  (2)

#define CANDEBUG   1

#define CANUSELOOP 0

#define CANSENDTIMEOUT (200)

#define CANAUTOPROCESS (1)
#define CANAUTOON      (1)
#define CANAUTOOFF     (0)

#define CAN_STDID      (0)
#define CAN_EXTID      (1)

#define CANDEFAULTIDENT    (0x55CC)
#define CANDEFAULTIDENTEXT (CAN_EXTID)

#define CAN_5KBPS    1
#define CAN_10KBPS   2
#define CAN_20KBPS   3
#define CAN_31K25BPS 4
#define CAN_33KBPS   5
#define CAN_40KBPS   6
#define CAN_50KBPS   7
#define CAN_80KBPS   8
#define CAN_83K3BPS  9
#define CAN_95KBPS   10
#define CAN_100KBPS  11
#define CAN_125KBPS  12
#define CAN_200KBPS  13
#define CAN_250KBPS  14
#define CAN_500KBPS  15
#define CAN_1000KBPS 16

#define CAN_OK                  (0)
#define CAN_FAILINIT            (1)
#define CAN_FAILTX              (2)
#define CAN_MSGAVAIL            (3)
#define CAN_NOMSG               (4)
#define CAN_CTRLERROR           (5)
#define CAN_GETTXBFTIMEOUT      (6)
#define CAN_SENDMSGTIMEOUT      (7)
#define CAN_FAIL                (0xff)

#define CAN_MAX_MESSAGE_LENGTH (8)

#define MAX_MESSAGE_LENGTH 8   ///< Maximum information length

/**
 * @enum eFilter_t
 * @brief Filter parameter
 */
typedef enum {
   MCP2515_RXF0 = 0,
   MCP2515_RXF1,
   MCP2515_RXF2,
   MCP2515_RXF3,
   MCP2515_RXF4,
   MCP2515_RXF5,
}eFilter_t;

/**
 * @enum eMasker_t
 * @brief  Mask register parameter
 */
typedef enum {
   MCP2515_RXM0 = 0,
   MCP2515_RXM1,
}eMasker_t;

class DFRobot_MCP2515
{
public:
    /**
     * @fn DFRobot_MCP2515
     * @brief the DFRobot_MCP2515 class' constructor.
     * @param csPin - indicate the spi select pin when mcu commication with the can controler e.i MCP2515
     * @return None
     */
    DFRobot_MCP2515(uint8_t csPin);

    /**
     * @fn begin
     * @brief config the the Can baud rate,  buffer, and interrupt.
     * @param speedset - MCP2515 can config rate
     * @return if successful, it return CAN_OK, or CAN_FAILINIT
     */
    uint8_t begin(uint8_t speedset);

    /**
     * @fn initMask
     * @brief initialize the mask register. 
     * @param maskerNum - maybe set MCP2515_RXM0 or MCP2515_RXM1.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param ulData - initialization data
     * @return the status. if success, return MCP2515_OK.
     */
    uint8_t initMask(eMasker_t maskerNum, uint8_t ext, uint32_t ulData);

    /**
     * @fn initFilter
     * @brief initialize the fileter register. 
     * @param filterNum - maybe set MCP2515_RXF0、 MCP2515_RXF1、 MCP2515_RXF2、 MCP2515_RXF3、 MCP2515_RXF4、 MCP2515_RXF5.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param Data - fileter data
     * @return the status. if success, return MCP2515_OK.
     */
    uint8_t initFilter(eFilter_t filterNum, uint8_t ext, uint32_t Data);

    /**
     * @fn getCanId
     * @brief get the id of the data cached in Can controller currently.
     * @return return the id number.
     */
    uint32_t getCanId(void);

    /**
     * @fn isRemoteRequest
     * @brief tell whether the current data frame buffered in Can controller is remote requestion frame.
     * @return return the id number.
     */
    uint8_t isRemoteRequest(void);

    /**
     * @fn isExtendedFrame
     * @brief tell whether the current data frame buffered in Can controller is extended frame.
     * @return return the id number.
     */
    uint8_t isExtendedFrame(void);

    /**
     * @fn checkReceive
     * @brief check whether data is cached by Can controler.
     * @return if there are some data received by Can controller. the return value is CAN_MSGAVAIL, or CAN_NOMSG.
     */
    uint8_t checkReceive(void);

    /**
     * @fn checkError
     * @brief check whether there is the control error on the Can bus line.
     * @return if control error don't occur, return CAN_OK, or return CAN_CTRLERROR.
     */
    uint8_t checkError(void);

    /**
     * @fn sendMsgBuf
     * @brief send one data frame.
     * @param id - the message id num.
     * @param ext - extend flag. if ext = 1, indicate the frame is extended frame.
     * @param len - the len of the data to send.
     * @param buf - the data to send.
     * @return the status. if success, return MCP2515_OK.
     */
    uint8_t sendMsgBuf(uint32_t id, uint8_t ext, uint8_t len, uint8_t *buf);

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
    uint8_t sendMsgBuf(uint32_t id, uint8_t ext, uint8_t rtr, uint8_t len, uint8_t *buf);

    /**
     * @fn readMsgBuf
     * @brief read one data frame from the cache in inner can controler. 
     * @param len - the len of the data to read.
     * @param buf - the data out from the Can controler store into the buf.
     * @return the status. if success, return MCP2515_OK.
     */
    uint8_t readMsgBuf(uint8_t *len, uint8_t *buf);

    /**
     * @fn readMsgBufID
     * @brief read one data frame from the cache in inner Can controler with the indicated ID, 
     * @n  if Can controler has not cached the ID's Frame the return value is not CAN_OK.
     * @param ID - ID number.
     * @param len - the len of the data to read.
     * @param buf - the data out from the Can controler store into the buf.
     * @return the status. if success, return MCP2515_OK. or this read operation is failed.
     */
    uint8_t readMsgBufID(uint32_t *ID, uint8_t *len, uint8_t *buf);

private:

    void mcpReset(void);
    void readReg(const uint8_t RegAddr, uint8_t *buf, uint8_t len);
    void writeReg(const uint8_t RegAddr, const uint8_t *buf, const uint8_t len);
    void modifyReg(const uint8_t RegAddr, const uint8_t mask, const uint8_t data);
    void mcpInitBuffers(void);
    uint8_t mcpReadStatus(void);
    uint8_t mcpSetMode(const uint8_t newMode);
    uint8_t mcpConfigRate(const uint8_t canSpeed);
    uint8_t mcpInit(const uint8_t canSpeed);
    void mcpWriteid( const uint8_t mcpAddr, const uint8_t ext, const uint32_t id );
    void mcpReadid( const uint8_t mcpAddr, uint8_t* ext, uint32_t* id );
    void mcpWritecanMsg( const uint8_t sidhAddr );
    void mcpReadcanMsg( const uint8_t sidhAddr);
    void mcpStarttransmit(const uint8_t mcpAddr);
    uint8_t mcpGetNextFreeTXBuf(uint8_t *txbuf_n);
    uint8_t setMsg(uint32_t id, uint8_t ext, uint8_t len, uint8_t rtr, uint8_t *pData);
    uint8_t setMsg(uint32_t id, uint8_t ext, uint8_t len, uint8_t *pData);
    uint8_t clearMsg(void);
    uint8_t readMsg(void);
    uint8_t sendMsg(void);

private:

    uint8_t   canExtFlg;
    uint32_t  canID;
    uint8_t   canDlc;
    uint8_t   canData[MAX_MESSAGE_LENGTH];
    uint8_t   canRtr;
    uint8_t   canFilhit;
    uint8_t   _csPin;
};

#endif
