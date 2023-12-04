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
#include "../Hardware/PdiResult.hpp"

using namespace std;

namespace PLCnext {

	class Axiobus;
	class AXLChannel;

	class AXLModule {
	public:

		enum DiagnosticStatus
		{
			OK					= 0x00,
			ERROR				= 0x01,
			WARNING				= 0x02,
			ERROR_REMOVED		= 0x81,
			ERROR_ELIMINATED	= 0x82,
			UNKNOWN				= 0xFE
		};

		struct Diagnostics
		{
			uint16_t id;
			DiagnosticStatus status;
			uint16_t errorCode;
			uint8_t channel;
			uint8_t moreFollows;
			string text;
		};

		AXLModule(Axiobus* axc, ushort slot, uint type);
		AXLModule();
		virtual ~AXLModule();
		virtual const string name()=0;
		const vector<AXLChannel*>& getChannels();
		uint getSerialNumber();
		uint getOrderNumber();
		uint getType();
		uint getSlotNumber();
		Axiobus* getAxioMaster();
		PdiResult pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, std::vector<uint8_t>& data);
		PdiResult pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, const std::vector<uint8_t>& data);
		bool isMissing();
		bool configurationChanged();
		Diagnostics getDiagnostics();
		string getFirmwareVersion();
		string getFirmwareDate();
		string getHardwareVersion();
		string getHardwareDate();

		enum Error
		{
			MODULE_MISSING = 99
		};
	private:
		friend class Axiobus;

		Axiobus* axc=0;
		uint m_serialNumber;
		uint m_orderNumber;
		uint m_slot;
		uint m_lastConfigCnt = 0;
		uint m_currConfigCnt = 0;
		string m_firmwareVersion;
		string m_firmwareDate;
		string m_hardwareVersion;
		string m_hardwareDate;
		virtual void processDiagnostic(Diagnostics&);
		virtual bool readConfiguration();

	protected:
		uint m_type;
		bool m_missing;
		uint inOffset;
		uint outOffset;
		vector<AXLChannel*> _channels;
		void configChangeNotify();
		bool setOutputsToFailState();
	};

}