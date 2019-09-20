/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_AI2AO2.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../AXLModule.h"
#include "../AXLOutput.h"
#include "../AXLInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_AI2AO2 = 0xA9;

	class AXC2152;

	class AXLF_AI2AO2 : public AXLModule
	{
	public:

		class AO2_Channel : public AXLOutput
		{
		public:
			AO2_Channel(char* _pdOut, AXLF_AI2AO2* ai2ao2, uint _channelNum);
			bool setOutputRange(ushort range);
			ushort getOutputRange();
			uint setValue(double value);
			uint getValue(double &value);

			enum OutputRange : ushort
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

			Variant getVariantValue();
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

		private:
			uint channelNum;
			char* pdOut;
			char outputRange;
			AXLF_AI2AO2* ai2ao2;
			string errorToString(uint);

		};

		class AI2_Channel : public AXLInput
		{
		public:
			AI2_Channel(char* _pd, AXLF_AI2AO2* AI2AO2, uint channelNum);
			uint getValue(double &ret);
			bool setMeasuringRange(ushort measuringRange);
			bool setFilter(ushort filter);
			bool setMeanValue(ushort meanValue);

			ushort getMeasuringRange();
			ushort getFilter();
			ushort getMeanValue();

			enum MeasuringRange
			{
				V_0_P10 = 0,    // 0 to +10 Volts
				V_N10_P10 = 1,  // -10 to +10 Volts
				V_0_P5 = 2,     // 0 to +5 Volts
				V_N5_P5 = 3,    // -5 to +5 Volts
				mA_0_P20 = 4,   // 0 to +24 milliamps
				mA_N20_P20 = 5, // -20 to +20 milliamps
				mA_P4_P20 = 6,  // +4 to +20 milliamps
				INACTIVE = 15   // Deactivate channel
			};

			enum MeanValue
			{
				Sample16 = 0, // 16 samples averaged
				NoMean = 1,   // Instantaneous value returned
				Sample4 = 2,  // 4 samples averaged
				Sample32 = 3  // 32 samples averaged
			};

			enum Filter
			{
				Hz_30 = 0,   // 30 Hz Filter
				kHz_12 = 1   // 12 kHz Filter
			};

			enum Error {
				NoError = 0x0000,
				InactiveChannel = 0x0001,
				UnknownError = 0x0002,
				OverRange = 0x8001, // Measuring range exceeded(overrange)
				OpenCircuit = 0x8002, // Open circuit
				Invalid = 0x8004, // Measured value invalid / no valid measured value available
				SupplyVoltage = 0x8020, // Faulty supply voltage
				DeviceFault = 0x8040, // Device faulty
				UnderRange = 0x8080  // Below measuring range(underrange)
			};

			// AXLInput Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

		private:
			char* pd;
			AXLF_AI2AO2* ai2ao2;
			uint channelNum;
			char measuringRange;
			char meanValue;
			bool filter;
			string errorToString(uint);
			ushort getCfgWord(ushort measuringRange, ushort filter, ushort meanValue);
		};

		struct AXLF_AO2
		{
			AO2_Channel* channel[2];
		};
		AXLF_AO2* ao2;

		struct AXLF_AI2
		{
			AI2_Channel* channel[2];
		};
		AXLF_AI2* ai2;

		AXLF_AI2AO2(AXC2152* axc, ushort _slot, uint pdInOffset, uint pdOutOffset);

		virtual const string name();

	private:
		bool _pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool _pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
	};
}


