/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_SE_AO4.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "AXLAnalogOutputSE.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_SE_AO4_I = 0x1a0f;

	class AXLF_SE_AO4_I : public AXLModule
	{
	public:

		class AO4_Channel : public AXLAnalogOutputSE
		{
		public:
			AO4_Channel(char* _pdIn, char* _pdOut, AXLModule* module, uint _channelNum);
			uint setValue(double value);
			uint getValue(double &value);


			enum Error
			{
				NoError			= 0x0000,
				UnknownError	= 0x0002,
				InvalidOutput	= 0x0003,
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

			// AXLChannel Overrides

			bool readConfiguration();

		private:
			//uint channelNum;
			char* pdIn;
			//char* pdOut;
			string errorToString(uint);

		protected:

			uint32_t convertValueToRaw(double value, uint16_t& converted);
			uint32_t convertRawToValue(uint16_t value, double& ret);

		};

		AXLF_SE_AO4_I(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		AO4_Channel* channel[4];
		const string name() override;
	};

}


