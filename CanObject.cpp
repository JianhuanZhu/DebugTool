/*
 * CanObject.cpp
 *
 *  Created on: 2015-2-4
 *      Author: kaishui
 */

#include "CanObject.h"

CanObject::CanObject(unsigned char uCanID)
{
	m_pCmdCan=new CmdCan();
	m_pCmdCan->Open(uCanID);
//    printf("启动CANID:%d\n",(int)uCanID);
	m_uCANID=uCanID;
}

CanObject::~CanObject()
{
	m_pCmdCan->Close();
	delete m_pCmdCan;

}



int CanObject::param_read(unsigned short iPos,unsigned int& iValue)
{
    command.command=0xE1;
	command.value1=0;
	command.value2=iPos;
	cout<<"参数读取 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
	 return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	iValue=feeback.value;
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

int CanObject::param_adjust(unsigned short iPos,short iParam)
{
    command.command=0xC1;
	command.value1=iParam;
	command.value2=iPos;
	cout<<"参数调整 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
	 return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

int CanObject::param_save(unsigned short iPos, short iParam)
{
	command.command=0xD1;
	command.value1=iParam;
	command.value2=iPos;
	cout<<"参数保存 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
	 return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

int CanObject::read_psoc_temp(unsigned int& iValue)
{
	command.command=0xAD;
	command.value1=0;
	command.value2=0;
	cout<<"读单片机温度 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
		return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	iValue=feeback.value;
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

int CanObject::read_psoc_edition(unsigned int& iValue)
{
	command.command=0xAF;
	command.value1=0;
	command.value2=0;
	cout<<"读单片机版本 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
	 return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	iValue=feeback.value;
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

int CanObject::led_star()
{
	command.command=0xAA;
	command.value1=0;
	command.value2=0;
	cout<<"led点灯测试 ";
	if(m_pCmdCan->Send(&command)<0)
	{
		return  (m_uCANID<<16)+(1<<8);   //发送失败
	}
	posc_cmd feeback;
	int len=sizeof(posc_cmd);
	if(m_pCmdCan->Recv(&feeback,len,5)<(int)sizeof(posc_cmd))
	{
	 return  (m_uCANID<<16)+(2<<8);   //接收信息不全
	}
	cout<<"Recv Feeback OK "<<feeback.value<<endl;
	if(feeback.error!=0xFF) return  (m_uCANID<<16)+feeback.error;  //执行错误
	return 0;
}

