/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLModule.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/


/* Smart Element Types:

slot: 1: type: 1a0d - ai4/u
slot: 2: type: 1d19 - do16/1
slot: 3: type: 1d18 - di16/1
slot: 4: type: 1a10 - ao4/u
slot: 5: type: 1a0c - ai4/i
slot: 6: type: 1a0f - ao4/i

*/
#pragma once

#include <sys/types.h>
#include <vector>
#include <string>
#include "PDIResponseStatus.h"

using namespace std;

namespace PLCnext {

	class Axiobus;
	class AXLChannel;

	class AXLModule {
	public:
		AXLModule(Axiobus* axc, ushort slot, uint type);
		AXLModule();
		virtual const string name()=0;
		const vector<AXLChannel*>& getChannels();
		uint getSerialNumber();
		uint getOrderNumber();
		uint getType();
		uint getSlotNumber();
		PDIResponseStatus pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		PDIResponseStatus pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
		bool isMissing();

		enum Error
		{
			MODULE_MISSING = 99
		};
	private:
		Axiobus* axc=0;
		uint m_serialNumber;
		uint m_orderNumber;
		uint m_slot;
	protected:
		uint m_type;
		bool m_missing;
		uint inOffset;
		uint outOffset;

		vector<AXLChannel*> _channels;
	};

}