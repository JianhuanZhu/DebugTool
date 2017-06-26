/*
 * CmdCan.cpp
 *
 *  Created on: 2011-12-21
 *      Author: kaishui
 */

#include "CmdCan.h"
#include <ErrorInfo.h>

#include <unistd.h>
#include <fcntl.h>

#define PRN_DEGINFO
//#define DEBUG_EDIT
#define HANDSHAKE

bool CmdCan::Open(short id)
{
	struct ifreq ifr;

	m_can=socket(PF_CAN,SOCK_RAW,CAN_RAW);
	if(m_can<=0)
		return false;

	strcpy(ifr.ifr_name,"can0");
	ioctl(m_can,SIOCGIFINDEX,&ifr);
//	printf("can0 can_ifindex = %x\n",ifr.ifr_ifindex);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if(bind(m_can,(struct sockaddr*)&addr,sizeof(addr))<0)
		return false;
	m_id=id;

	//对ID进行过滤
	struct can_filter rfilter;
	rfilter.can_id   = ARMID<<4|m_id;
	rfilter.can_mask = CAN_SFF_MASK;
	setsockopt(m_can, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
//	fcntl(m_can,F_SETFL,O_NONBLOCK);


	m_bFeeback=true;

//#ifdef PRN_DEGINFO
//    cout<<__FUNCTION__<<" m_can:"<<m_can<<" m_id:"<<m_id<<endl;
//#endif

	return true;
}


void CmdCan::Close()
{
	close(m_can);
	printf("CAN Close:%d\n",m_can);
}


int CmdCan::Send(can_cmd *command)
{
    if(m_can<0)
    {
        ErrorInfo::ShowErrinfo((m_id<<16)|(1<<8),true);
        return -1;
    }


	bool bclear=true;
	while(bclear)
	{
        cout<<endl;
		bclear=ClearBuf();
	}
	int len=sizeof(can_cmd);

	//PSOC的字节序不同
	command->dev=m_id;
	command->check=command->getcheck();
	command->value1=htons(command->value1);
	command->value2=htons(command->value2);




	struct can_frame frame;
	frame.can_id = 0x30+m_id;

	unsigned char* buf;
	buf=(unsigned char*)command;

#ifdef PRN_DEGINFO
	cout<<"CAN Send :";
#endif

	for(int i=0;i<len;i++)
	{
		frame.data[i]=*((__u8*)buf+i);
#ifdef PRN_DEGINFO
		char tmp[4];
		sprintf(tmp,"%X ",frame.data[i]);
		cout<<tmp;
#endif
	}
#ifdef PRN_DEGINFO
	cout<<endl;
#endif
	frame.can_dlc = len;

#ifdef DEBUG_EDIT
	  return 7;
#endif

	   int nbytes = sendto(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));

	   //转换成原来的字节序（参数重用时保证值不变)
	   	command->value1=ntohs(command->value1);
	   	command->value2=ntohs(command->value2);

#ifdef HANDSHAKE
	    bool bResend=false;
	    struct timeval tv;
		fd_set readfds;
		tv.tv_sec = 0;
		tv.tv_usec = 50000;
		FD_ZERO(&readfds);
		FD_SET(m_can, &readfds);

		int ret = select(m_can + 1, &readfds, NULL, NULL, &tv);
		if (ret == -1)
		{
			//重发
			bResend=true;
		}
		else if (ret == 0)
		{
			//重发
			bResend=true;
		}
		else if (!FD_ISSET(m_can, &readfds))
		{
			//重发
			bResend=true;
		}

		if(bResend)
		{
			return ReSend(command);
		}
		len=8;
		int rnbytes = recvfrom(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);

		if(rnbytes<0)
		{
			//重发
			return ReSend(command);
		}

		if(frame.can_id!=(unsigned int)(((ARMID<<4)|m_id)))
		{
			//重发
			return ReSend(command);
		}

		if(len>frame.can_dlc)
			len=frame.can_dlc;
#ifdef PRN_DEGINFO
		printf("Recv HandShake: ");
		for(int i=0;i<len;i++)
		{
		   printf("%X ",frame.data[i]);
		}
		printf("\n");
#endif
		if(frame.data[1]!=0xAA)
		{
			//重发
			return ReSend(command);
		}

#endif

	m_bFeeback=false;

	usleep(5000);

	return nbytes;
}


int CmdCan::ReSend(can_cmd *command)
{
    if(m_can<0)
    {
         ErrorInfo::ShowErrinfo((m_id<<16)|(1<<8),true);
        return -1;
    }

	int len=sizeof(can_cmd);

	//PSOC的字节序不同
	command->dev=m_id;
	command->check=command->getcheck();
	command->value1=htons(command->value1);
	command->value2=htons(command->value2);




	struct can_frame frame;
	frame.can_id = 0x30+m_id;

	unsigned char* buf;
	buf=(unsigned char*)command;

#ifdef PRN_DEGINFO
	cout<<"CAN ReSend :";
#endif

	for(int i=0;i<len;i++)
	{
		frame.data[i]=*((__u8*)buf+i);
#ifdef PRN_DEGINFO
		char tmp[4];
		sprintf(tmp,"%X ",frame.data[i]);
		cout<<tmp;
#endif
	}
#ifdef PRN_DEGINFO
	cout<<endl;
#endif
	frame.can_dlc = len;

#ifdef DEBUG_EDIT
	  return 7;
#endif

	int nbytes = sendto(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));

	//转换成原来的字节序（参数重用时保证值不变)
	command->value1=ntohs(command->value1);
	command->value2=ntohs(command->value2);

	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 0;
	tv.tv_usec = 50000;
	FD_ZERO(&readfds);
	FD_SET(m_can, &readfds);

	int ret = select(m_can + 1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	{
        ErrorInfo::ShowErrinfo((m_id<<16)|(2<<8),true);
		return -1;
	}
	else if (ret == 0)
	{
        ErrorInfo::ShowErrinfo((m_id<<16)|(2<<8),true);
		return -1;
	}
	else if (!FD_ISSET(m_can, &readfds))
	{
        ErrorInfo::ShowErrinfo((m_id<<16)|(2<<8),true);
		return -1;
	}

	len=8;
	int rnbytes=recvfrom(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);
	if(rnbytes<0)
    {
        ErrorInfo::ShowErrinfo((m_id<<16)|(3<<8),true);
		return -1;
    }
	if(frame.can_id!=(unsigned int)(((ARMID<<4)|m_id)))
		return 0;
	if(len>frame.can_dlc)
		len=frame.can_dlc;

#ifdef PRN_DEGINFO
		printf("Recv HandShake: ");
		for(int i=0;i<len;i++)
		{
		   printf("%X ",frame.data[i]);
		}
		printf("\n");
#endif
	if(frame.data[1]!=0xAA)
	{
        ErrorInfo::ShowErrinfo((m_id<<16)|(4<<8),true);
		return -1;
	}


	m_bFeeback=false;

	usleep(5000);

	return nbytes;
}

bool CmdCan::ClearBuf()
{
	struct timeval tv;
	fd_set readfds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_SET(m_can, &readfds);

	int ret = select(m_can + 1, &readfds, NULL, NULL, &tv);
	if (ret == -1)
	{
		return false;
	}
	else if (ret == 0)
	{
		return false;
	}
	else if (!FD_ISSET(m_can, &readfds))
	{
		return false;
	}

	int len=8;
	struct can_frame frame;
	recvfrom(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);

#ifdef PRN_DEGINFO
	printf("Clear Can Recv Buf:");
	for(int i=0;i<len;i++)
	{
	   printf("%X ",frame.data[i]);
	}
	printf("\n");
#endif
	return true;

}


int CmdCan::Recv(void * buf,int& len,double timeout)
{

#ifdef DEBUG_EDIT
	  memset(buf,0xFF,7);
	  return 7;
#endif
	if(m_can<0) return -1;

    if(timeout>0)
    {
		struct timeval tv;
		fd_set readfds;
		tv.tv_sec = (int)(timeout);
		tv.tv_usec = (timeout-((int)(timeout)))*1000000;
		FD_ZERO(&readfds);
		FD_SET(m_can, &readfds);

		int ret = select(m_can + 1, &readfds, NULL, NULL, &tv);
		if (ret == -1)
		{
			m_bFeeback=true;
			printf("Socket recv select error.\n");
            ErrorInfo::ShowErrinfo((m_id<<16)|(6<<8),true);
					return -1;
		}
		else if (ret == 0)
		{
			m_bFeeback=true;
			printf("Socket recv select timeout.\n");
            ErrorInfo::ShowErrinfo((m_id<<16)|(7<<8),true);
					return -2;
		}
		else if (!FD_ISSET(m_can, &readfds))
		{
			m_bFeeback=true;
			printf("Socket recv select not from m_can\n");
            ErrorInfo::ShowErrinfo((m_id<<16)|(6<<8),true);
		    return -3;
		}
    }

	struct can_frame frame;
	int nbytes = recvfrom(m_can,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);
#ifdef PRN_DEGINFO
	printf("CAN Recv :");
#endif
	m_bFeeback=true;
	if(nbytes<0)
		return nbytes;

	if(frame.can_id!=(unsigned int)(((ARMID<<4)|m_id)))
		return -1;

	if(len>frame.can_dlc)
		len=frame.can_dlc;
	for(int i=0;i<len;i++)
	{
	   *((__u8*)buf+i)=frame.data[i];
#ifdef PRN_DEGINFO
	   printf("%X ",frame.data[i]);
#endif
	}

	posc_cmd* pRecv=(posc_cmd*)buf;
	pRecv->value=ntohl(pRecv->value);


#ifdef PRN_DEGINFO
	   printf("\n");
#endif
	return len;
}


bool CmdCan::isRecvError(posc_cmd *feeback)
{

#ifdef DEBUG_EDIT
		 return false;
#endif
#ifdef HANDSHAKE
	 if(feeback->check!=feeback->getcheck())
		 return true;
#endif
	 if(feeback->dev!=m_id)
		 return true;


	 return false;
}





