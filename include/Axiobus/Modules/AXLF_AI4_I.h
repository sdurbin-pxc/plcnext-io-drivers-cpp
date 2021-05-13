/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_AI4_I.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../AXLModule.h"
#include "../AXLInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_AI4_I = 0xA6;

	class Axiobus;

	class AXLF_AI4_I : public AXLModule
	{
	public:

		class AI4_I_Channel : public AXLInput
		{
		public:
			AI4_I_Channel(char* _pd, AXLF_AI4_I* ai4i, uint channelNum);
			uint getValue(double &ret);
			bool setMeasuringRange(ushort measuringRange);
			bool setFilter(ushort filter);
			bool setMeanValue(ushort meanValue);

			ushort getMeasuringRange();
			ushort getFilter();
			ushort getMeanValue();

			enum MeasuringRange {
				mA_0_P20 = 4,
				mA_N20_P20 = 5,
				mA_P4_P20 = 6,
				INACTIVE = 15
			};

			enum MeanValue {
				Sample16 = 0,
				NoMean = 1,
				Sample4 = 2,
				Sample32 = 3
			};

			enum Filter {
				Hz_30 = 0,
				kHz_16 = 1
			};

			enum Error {
				NoError			= 0x0000,
				InactiveChannel = 0x0001,
				UnknownError	= 0x0002,
				OverRange		= 0x8001, // Measuring range exceeded(overrange)
				OpenCircuit		= 0x8002, // Open circuit
				Invalid			= 0x8004, // Measured value invalid / no valid measured value available
				SupplyVoltage	= 0x8020, // Faulty supply voltage
				DeviceFault		= 0x8040, // Device faulty
				UnderRange		= 0x8080  // Below measuring range(underrange)
			};

			// AXLChannel Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

		private:
			char* pd;
			//uint channelNum;
			char measuringRange;
			char meanValue;
			bool filter;
			string errorToString(uint);
			ushort getCfgWord(ushort measuringRange, ushort filter, ushort meanValue);

			// Function enum pointers
			AXLEnumParameter* m_rangeEnum;
			AXLEnumParameter* m_meanEnum;
			AXLEnumParameter* m_filterEnum;
		};

		AXLF_AI4_I(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset);
		AXLF_AI4_I();
		AI4_I_Channel* channel[4];

		// AXLModule Overrides
		const string name();
	};

}


