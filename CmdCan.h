/*
 * CmdCan.h
 *
 *  Created on: 2011-12-21
 *      Author: kaishui
 */

#ifndef CMDCAN_H_
#define CMDCAN_H_


#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <linux/can/raw.h>
#include "can/ioctl.h"
#include <arpa/inet.h>


using namespace std;


#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

#define ARMID           1
#define SHAND           2
#define RHAND           3
#define SAMPLEDISK      4
#define REAGENTDISK     5
#define REACTIONDISK    6
#define WASHUNIT        7
#define ADDCUP          8
#define LIGHT           9
#define SENSOR          0xA
#define RCOLD           0xB
#define MIXUNIT         0xC
#define MSYSTIME        0xF


class can_cmd
{
public:

	unsigned char dev:4;   //设备ID
	unsigned char head:4;  //头
    unsigned char command;  //命令
    unsigned short value1;  //数值
    unsigned short value2;  //数值
    unsigned char check;  //校验
    can_cmd()
    {
    	head=0xA;
    	value1=0;
    	value2=0;
    }
    unsigned char getcheck()
    {return ((head<<4|dev)+command+value1+value2+0x78);}

}__attribute__((packed,aligned(1)));


struct posc_cmd
{

	unsigned char dev:4;   //设备ID
	unsigned char head:4;  //自身ID
	unsigned char error;  //错误码
    unsigned int value;  //数值
    unsigned char check;  //校验
    unsigned char getcheck(){return ((head<<4|dev)+value+error+0x78);}
}__attribute__((packed,aligned(1)));   //一个字节对齐，(系统不同函数不同)


class CmdCan
{
public:

	bool Open(short id);
	int Send(can_cmd *command);
	int ReSend(can_cmd *command);
	int Recv(void * buf,int& len,double timeout=-1);
	void Close();

    bool isRecvError(posc_cmd *feeback);

	bool m_bFeeback;  //是否已返回


private:
	int m_can;
	short m_id;  //设备ID
	struct sockaddr_can addr;

	bool ClearBuf();

	//inline unsigned short byte_seque_short(unsigned short value);
	//inline unsigned int byte_seque_int(unsigned int  value);

};

#endif /* CMDCAN_H_ */
