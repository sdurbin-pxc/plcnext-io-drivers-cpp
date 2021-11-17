/************************************************************************
**                                                                     **
**                PHOENIX CONTACT GmbH & Co., D-32819 Blomberg         **
**                                                                     **
*************************************************************************
**                                                                     **
** Project      : AXC3051 C++ lib for Ulstein                          **
**                                                                     **
*************************************************************************
**
** File         : AXL_RSUNI.cpp
** Component(s) : CAXL_RSUNI
** Definition   : Reference to related Specification.
** Author       : Steven Durbin
** Date         : October 2015
**              :
** Version      : V1.00 beta
** Date         : --
** State        : in work (in work, tested, reviewed, released)
**              :
** Description  : class source, access to AXL RSUNI module functionality
**              :
*************************************************************************/

#pragma once

#define RSUNI_BUS_ERROR				-1
#define RSUNI_NO_ERROR 				0
#define RSUNI_INVALID_WRITE_LEN		1
#include <sys/types.h>
#include "../../AXLModule.h"

//#include "SystemManager.hpp"


/*
** Class:         CAXL_RSUNI
**
** Description:   For read/write operations via the RSUNI module
**
** Methods:       nRead:                Read characters from the Rx buffer.
**                nWrite:               Write characters.
**                nGetNumBytesToRead:   Retrieve the number of bytes in the
**                                      Rx buffer.
**                
*/

namespace PLCnext {

	const uint AXLF_MODULE_RSUNI = 0x123456;  // CHANGE

	class AXLF_RSUNI : public AXLModule
	{
	public:
		AXLF_RSUNI(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		bool bRead(char* pcBuffer, uint uMaxCharsToRead, uint& uNumCharsRead, uint& uError);
		bool bWrite(char* pcBuffer, uint uWriteLength, uint& uError);
		unsigned int uGetNumBytesToRead(uint& uError);
		bool bIsTransmitBufferEmpty(uint& uError);
		bool bIsReadBufferEmpty(uint& uError);
		virtual ~AXLF_RSUNI();
	private:
		bool		 m_bToggleBit;
		unsigned int m_uNumRdBuf;
		char m_arr_cRdBuf[17];
		char m_arr_cQbuf[20];
		char m_arr_cIbuf[20];
		char* pdOut;
		char* pdIn;
		unsigned short* m_pControlWord;
		unsigned int uStatusWord();
		bool bReadInputBuffer(uint& uError);
		bool bSetOutputBuffer(uint& uError);

	};
}
