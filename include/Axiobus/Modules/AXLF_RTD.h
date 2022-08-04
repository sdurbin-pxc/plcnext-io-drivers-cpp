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
#include "../AXLModule.h"
#include "../AXLAnalogInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_RTD4 = 0xA4;
	const uint AXLF_MODULE_RTD8 = 0xA1;

	class Axiobus;

	class AXLF_RTD : public AXLModule
	{
	public:

		class RTD_Channel : public AXLAnalogInput
		{
		public:
			RTD_Channel(char* _pdIn, AXLF_RTD* uth, uint channelNum);

			uint getValue(double &ret);

			bool setConnectionMethod(ushort connectionMethod);
			bool setSensorType(ushort sensorType);
			bool setResolution(ushort resolution);
			bool setFilter(ushort filter);
			bool setR0(ushort r0);

			ushort getConnectionMethod();
			ushort getSensorType();
			ushort getResolution();
			ushort getFilter();
			ushort getR0();

			enum ConnectionMethod {
				Three_Wire = 0,
				Two_Wire = 1,
				Four_Wire = 2
			};

			enum SensorType {
				PtDIN = 0,
				PtSAMA = 1,
				NiDIN = 2,
				NiSAMA = 3,
				Cu10 = 4,
				Cu50 = 5,
				Cu53 = 6,
				Ni1000 = 7,
				Ni500 = 8,
				KTY81_110 = 9,
				KTY84 = 10,
				KTY81_210 = 11,
				LinearR_0_500_Ohm = 13,
				LinearR_0_5000_Ohm = 14,
				INACTIVE = 15
			};

			enum Resolution {
				TenthDegreeCelsius = 0,
				HundredthDegreeCelsius = 1,
				TenthDegreeFarenheit = 2,
				HundredthDegreeFarenheit = 3,
			};

			enum Filter {
				ms_120 = 0,
				ms_100 = 1,
				ms_60 = 2,
				ms_40 = 3
			};

			enum R0 {
				OHMS_100,
				OHMS_10,
				OHMS_20,
				OHMS_30,
				OHMS_50,
				OHMS_120,
				OHMS_150,
				OHMS_200,
				OHMS_240,
				OHMS_300,
				OHMS_400,
				OHMS_500,
				OHMS_1000,
				OHMS_1500,
				OHMS_2000
			};

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


			// AXLInput Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// AXLChannel Overrides

			bool readConfiguration();

		private:
			char* pdIn;
			AXLF_RTD* rtd;
			//uint channelNum;
			char sensorType;
			char r0;
			char resolution;
			char filter;
			char connectionMethod;
			string errorToString(uint);
			ushort getCfgWord(ushort sensorType, ushort resolution, ushort r0, ushort filter, ushort connectionMethod);

			// Function enum pointers
			AXLEnumParameter* m_connectionEnum;
			AXLEnumParameter* m_sensorEnum;
			AXLEnumParameter* m_resolutionEnum;
			AXLEnumParameter* m_filterEnum;
			AXLEnumParameter* m_r0Enum;
		};

		AXLF_RTD(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, int numChannels);
		AXLF_RTD();
		RTD_Channel** channel;
		virtual const string name();
	};

	class AXLF_RTD8 : public AXLF_RTD
	{
	public:
		AXLF_RTD8(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset);
	};

	class AXLF_RTD4 : public AXLF_RTD
	{
	public:
		AXLF_RTD4(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset);
	};
}
