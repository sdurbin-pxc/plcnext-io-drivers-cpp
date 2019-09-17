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

#pragma once

#include <sys/types.h>
#include <vector>
#include <string>
#include "AXLChannel.h"

using namespace std;

namespace PLCnext {

	class AXC2152;

	class AXLModule {
	public:
		AXLModule(AXC2152* axc, ushort slot, uint type);
		AXLModule();
		virtual const string name()=0;
		const vector<AXLChannel*>& getChannels();
		uint getSerialNumber();
		uint getOrderNumber();
		uint getType();
		uint getSlotNumber();
	private:
		AXC2152* axc=0;
		uint m_serialNumber;
		uint m_orderNumber;
		uint m_slot;
	protected:
		uint m_type;
		uint inOffset;
		uint outOffset;
		bool pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
		vector<AXLChannel*> _channels;
	};

}