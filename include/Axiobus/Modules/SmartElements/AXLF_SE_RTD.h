/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_RTD.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "../../AXLAnalogInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_SE_RTD4 = 0x1a0e;
	const uint AXLF_MODULE_SE_RTD4_PT1000 = 0x1a11;

	class Axiobus;

	class AXLF_SE_RTD : public AXLModule
	{
	public:

		class RTD_Channel : public AXLAnalogInput
		{
		public:
			RTD_Channel(char* _pdIn, AXLModule* module, uint channelNum);

			uint getValue(double &ret);

			enum Error {
				NoError = 0x0000,
				InactiveChannel = 0x0001,
				UnknownError = 0x0002,
				OverRange = 0x8001, // Measuring range exceeded(overrange)
				OpenCircuit = 0x8002, // Open circuit
				Invalid = 0x8004, // Measured value invalid / no valid measured value available
				BadParameter = 0x8010,
				SupplyVoltage = 0x8020, // Faulty supply voltage
				DeviceFault = 0x8040, // Device faulty
				UnderRange = 0x8080  // Below measuring range(underrange)
			};

			bool setWireBreakDetection(bool);
			bool getWireBreakDetection();

			// AXLInput Overrides

			Variant getVariantValue() override;
			ValueWithError getValueWithError() override;
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// AXLChannel Overrides

			bool readConfiguration();

		private:
			AXLEnumParameter* m_wireBreakEnum;
			uint8_t wireBreak;
			char* pdIn;
			AXLF_SE_RTD* rtd;
			//uint channelNum;
			string errorToString(uint);
		};

		AXLF_SE_RTD(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		~AXLF_SE_RTD();
		AXLF_SE_RTD();
		RTD_Channel* channel[4];
		const string name() override;

	};

}
