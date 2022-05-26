# DFRobot_MCP2515
* [English Version](./README.md)

CAN-BUS由于其传输距离长、通信速度中等、可靠性高等特点，是一种常用的工业总线。它在现代机床和汽车诊断总线上普遍存在。该CAN总线屏蔽采用带有SPI接口的MCP2515 CAN总线控制器和MCP2551 CAN收发器，实现Arduino/Seeeduino CAN总线功能。随着OBD-II转换器电缆的添加和OBD-II库的导入，您可以准备构建一个板载诊断设备或数据记录器。

![产品实物图](./resources/images/MCP2515.png)


## 产品链接 (https://www.dfrobot.com.cn/goods-1264.html)
    SKU: DFR0370

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述

* 支持标准帧、扩展帧收发，支持轮询和中断两种接收方式
* 提供uart、I2C、DB9及接线柱等多种接口
* 支持SD卡数据存储
* 支持Arduino主板供电以及DB9接口供电


## 库安装

这里有2种安装方法：

1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_MCP2515 库。


## 方法

```C++

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

```


## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |


## 历史

- 2022/05/25 - 1.0.0 版本


## 创作者

This software is written by loovee ([luweicong@seeed.cc](luweicong@seeed.cc "luweicong@seeed.cc")) for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>


[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/CAN_BUS_Shield)](https://github.com/igrigorik/ga-beacon)

