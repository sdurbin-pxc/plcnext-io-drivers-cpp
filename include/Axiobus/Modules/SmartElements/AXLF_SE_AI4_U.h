/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_SE_AI4_U.h
*
*  Created on: April 22, 2020
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "../../AXLAnalogInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_SE_AI4_U = 0x1A0D;

	class Axiobus;

	class AXLF_SE_AI4_U : public AXLModule
	{
	public:

		class AI4_Channel : public AXLAnalogInput
		{
		public:
			AI4_Channel(char* _pd, AXLModule* module, uint channelNum);
			uint getValue(double &ret);

			enum Error {
				NoError = 0x0000,
				InactiveChannel = 0x0001,
				UnknownError = 0x0002,
				OverRange = 0x8001, // Measuring range exceeded(overrange)
				ParamError = 0x8010, // Parameter Error
				SupplyVoltage = 0x8020, // Faulty supply voltage
				DeviceFault = 0x8040, // Device faulty
				UnderRange = 0x8080  // Below measuring range(underrange)
			};

			// AXLInput Overrides

			Variant getVariantValue() override;
			ValueWithError getValueWithError() override;

			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// AXLChannel Overrides

			bool readConfiguration() { return true; }

		private:
			char* pd;
			//uint channelNum;
			string errorToString(uint);
		};

		AXLF_SE_AI4_U(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		AXLF_SE_AI4_U();
		AI4_Channel* channel[4];
		const string name() override;
	};

}


