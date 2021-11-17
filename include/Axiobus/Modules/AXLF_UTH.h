/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_UTH.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../AXLModule.h"
#include "../AXLAnalogInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_UTH8 = 0xA2;
	const uint AXLF_MODULE_UTH4 = 0xA8;

	class Axiobus;

	class AXLF_UTH : public AXLModule
	{
	public:

		class UTH_Channel : public AXLAnalogInput
		{
		public:
			UTH_Channel(char* _pdIn, char* _pdOut, AXLF_UTH* uth, uint channelNum);

			uint getValue(double &ret);

			bool setSensorType(ushort sensorType);
			bool setResolution(ushort resolution);
			bool setFilter(ushort filter);
			bool setColdJunctionType(ushort coldJunctionType);

			ushort getSensorType();
			ushort getResolution();
			ushort getFilter();
			ushort getColdJunctionType();

			enum SensorType {
				K = 0,
				J = 1,
				E = 2,
				R = 3,
				S = 4,
				T = 5,
				B = 6,
				N = 7,
				U = 8,
				L = 9,
				C = 10,
				W = 11,
				HK = 12,
				ColdJunction = 15,
				LinearVoltage_PN100mV = 16,
				INACTIVE = 0x1F
			};

			enum Resolution {
				OneTenthDegreeCelsius_1uV = 0,
				DegreeCelsius_10uV = 1,
				OneTenthDegreeFarenheit = 2,
				DegreeFarenheit = 3,
			};

			enum Filter {
				ms_120 = 0,
				ms_100 = 1,
				ms_60 = 2,
				ms_40 = 3
			};

			enum ColdJunctionType {
				Internal = 0,
				SwitchedOff = 1,
				Connector1 = 2,
				Connector2 = 3,
				Connector3 = 4,
				Connector4 = 5,
				ProcessData = 6
			};

			enum MountingPosition {
				Horizontal = 0,
				ProcessorAboveIO = 1,
				ProcessorBelowIO = 2,
				LyingFlat = 3
			};

			enum Error {
				NoError = 0x0000,
				InactiveChannel = 0x0001,
				UnknownError = 0x0002,
				OverRange = 0x8001, // Measuring range exceeded(overrange)
				OpenCircuit = 0x8002, // Open circuit
				Invalid = 0x8004, // Measured value invalid / no valid measured value available
				ColdJunctionDefective = 0x8008,
				BadParameter = 0x8010,
				SupplyVoltage = 0x8020, // Faulty supply voltage
				DeviceFault = 0x8040, // Device faulty
				UnderRange = 0x8080  // Below measuring range(underrange)
			};


			// AXLInput Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

		private:
			char* pdIn;
			char* pdOut;
			AXLF_UTH* uth;
			//uint channelNum;
			char sensorType;
			char coldJunctionType;
			char resolution;
			char filter;
			string errorToString(uint);
			ushort getCfgWord(ushort sensorType, ushort resolution, ushort coldJunction, ushort filter);

			// Function enum pointers
			AXLEnumParameter* m_filterEnum;
			AXLEnumParameter* m_sensorEnum;
			AXLEnumParameter* m_coldJunctionEnum;
			AXLEnumParameter* m_resolutionEnum;
		};

		AXLF_UTH(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset, int numChannels);
		AXLF_UTH();
		UTH_Channel** channel;
		virtual const string name();
	};

	class AXLF_UTH8 : public AXLF_UTH
	{
	public:
		AXLF_UTH8(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
	};

	class AXLF_UTH4 : public AXLF_UTH
	{
	public:
		AXLF_UTH4(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
	};
}
