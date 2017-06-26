/*
 * CanObject.h
 *
 *  Created on: 2015-2-4
 *      Author: kaishui
 */

#ifndef CANOBJECT_H_
#define CANOBJECT_H_

#include <stdio.h>
#include "CmdCan.h"

#define TIMEOUT 20

class CanObject
{
public:

	CanObject(unsigned char uCanID);
	~CanObject();
	CmdCan *m_pCmdCan;

	unsigned char m_uCANID;
	int param_read(unsigned short iPos,unsigned int& iValue);
	int param_adjust(unsigned short iPos,short iParam);
	int param_save(unsigned short iPos, short iParam);
	int read_psoc_temp(unsigned int& iValue);
	int read_psoc_edition(unsigned int& iValue);
	int led_star();


protected:
	can_cmd command;
};

#endif /* CANOBJECT_H_ */
