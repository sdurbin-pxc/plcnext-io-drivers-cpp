/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_HART_AI8.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "../../AXLAnalogInput.h"
#include "../../AXLChannel.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_HART_AI8 = 0xB0CA1;

	class Axiobus;

	class AXLF_HART_AI8 : public AXLModule
	{
	public:

		class Data_Channel : AXLChannel
		{
		public:
			Data_Channel(char* _pd, AXLF_HART_AI8* ai8, uint channelNum);

			enum class Channel_Select
			{
				Disabled,
				Channel1,
				Channel2,
				Channel3,
				Channel4,
				Channel5,
				Channel6,
				Channel7,
				Channel8,
				Unknown
			};

			bool assignChannel(Channel_Select channel);
			Channel_Select getChannel();

			enum class Data_Variable
			{
				Loop_Current,
				PV,
				SV,
				TV,
				QV,
				Unknown
			};

			bool assignVariable(Data_Variable variable);
			Data_Variable getAssignVariable();

			uint32_t getValue();

			enum class Channel_Enable
			{
				Disabled,
				Enabled,
				Enabled_NoAlarms,
				Unknown
			};



			Channel_Enable getChannelEnabled();
			bool setChannelEnabled(Channel_Enable);


			enum class Priority_Polling
			{
				Disabled,
				Enabled,
				Unknown
			};

			Priority_Polling getHighPriorityPolling();
			bool setHighPriorityPolling(Priority_Polling);

			// AXLChannel Overrides:

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);
			bool readConfiguration();

		private:
			int m_channelNum;
			AXLF_HART_AI8* m_ai8;
			bool m_enabled;
			char* m_pd;
			AXLEnumParameter* m_assignVariableEnum;
			AXLEnumParameter* m_assignChannelEnum;
			AXLEnumParameter* m_channelEnableEnum;
			AXLEnumParameter* m_highPrioPolling;

			Channel_Enable m_channelEnabled;
			Data_Variable m_assignedVariable;
			Channel_Select m_assignedChannel;
			Priority_Polling m_priorityPolling;
		};

		class AI_Channel : public AXLAnalogInput
		{
		public:
			AI_Channel(char* _pd, AXLF_HART_AI8* ai8, uint channelNum);
			uint getValue(double &ret);

			enum class NE43_Alarm {

				Disabled = 0x00,
				Enabled = 0x01,
				Unknown = 0xFF
			};

			bool setNE43alarmEnabled(NE43_Alarm ne43enabled);
			NE43_Alarm getNE43alarmEnabled();

			enum class MeanValue {
				NoMean = 0,
				Sample4 = 0x04,
				Sample8 = 0x08,
				Sample16 = 0x10,
				Sample32 = 0x20,
				Unknown = 0xFF
			};

			MeanValue getMeanValue();
			bool setMeanValue(MeanValue meanValue);

			enum class MeasuringRange {
				mA_P4_P20 = 6,
				INACTIVE = 0xFF,
				Unknown = 0xFE
			};

			MeasuringRange getMeasuringRange();
			bool setMeasuringRange(MeasuringRange range);

			enum Error {
				NoError			= 0x0000,
				InactiveChannel = 0x0001,
				UnknownError	= 0x0002,
				OverRange		= 0x8001, // Measuring range exceeded(overrange)
				OpenCircuit		= 0x8002, // Open circuit
				Invalid			= 0x8004, // Measured value invalid / no valid measured value available
				DeviceFault		= 0x8040, // Device faulty
				UnderRange		= 0x8080  // Below measuring range(underrange)
			};

			// AXLInput Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// AXLChannel Overrides

			bool readConfiguration();

		private:
			char* pd;
			AXLF_HART_AI8* ai8;
			//uint channelNum;
			MeanValue meanValue;
			MeasuringRange measuringRange;
			NE43_Alarm ne43alarm;
			string errorToString(uint);
			ushort getCfgWord(ushort measuringRange, ushort filter, ushort meanValue);
			void setRangeMinMax();

			// Function enum pointers
			AXLEnumParameter* m_rangeEnum;
			AXLEnumParameter* m_meanEnum;
			AXLEnumParameter* m_ne43enum;
		};

		AXLF_HART_AI8(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset);
		AXLF_HART_AI8();
		AI_Channel* aiChannel[8];
		Data_Channel* dataChannel[8];
		virtual const string name();
	};

}


