/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_AO8.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../AXLModule.h"
#include "../AXLAnalogOutput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_AO8 = 0xA3;

	class AXLF_AO8 : public AXLModule
	{
	public:

		class AO8_Channel : public AXLAnalogOutput
		{
		public:
			AO8_Channel(char* _pdIn, char* _pdOut, AXLModule* module, uint _channelNum);
			bool setOutputRange(ushort range);
			ushort getOutputRange();
			uint setValue(double value);
			uint getValue(double &value);

			enum OutputRange
			{
				V_0_P10		 = 0,
				V_N10_P10	 = 1,
				V_0_P5		 = 2,
				V_N5_P5		 = 3,
				mA_0_P20	 = 4,
				mA_N20_P20	 = 5,
				mA_P4_P20	 = 6,
				INACTIVE	 = 15
			};

			enum Error
			{
				NoError			= 0x0000,
				InactiveChannel = 0x0001,
				UnknownError	= 0x0002,
				InvalidOutput	= 0x0003,
				OpenCircuit		= 0x8002, // Open circuit
				ShortCircuit	= 0x8003, // Short - circuit
				InvalidParams	= 0x8010, // Parameter table invalid
				SupplyVoltage	= 0x8020, // Faulty supply voltage
				DeviceFault		= 0x8040  // Device faulty
			};

			// AXLOutput Overrides

			Variant getVariantValue() override;
			ValueWithError getValueWithError() override;

			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// Function enum pointers

			AXLEnumParameter* m_rangeEnum;

			// AXLChannel Overrides

			bool readConfiguration();

		private:

			char* pdIn;
			//char* pdOut;
			char outputRange;
			AXLF_AO8* AO8;
			string errorToString(uint);
			void setRangeMinMax();

		protected:

			// AXLAnalogOutput Overrides:

			uint32_t convertValueToRaw(double value, uint16_t& converted);
			uint32_t convertRawToValue(uint16_t value, double& ret);


		};

		AXLF_AO8(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		AO8_Channel* channel[8];
		const string name() override;
	};

}


