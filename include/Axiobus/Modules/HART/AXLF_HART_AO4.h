/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_HART_AO4.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "../../AXLAnalogOutput.h"
#include "../../AXLChannel.h"

using namespace std;

namespace PLCnext {

	// DataSheet says 0xBOCA2. Needs correction.
	const uint AXLF_MODULE_HART_AO4 = 0xB0CA3;

	class Axiobus;

	class AXLF_HART_AO4 : public AXLModule
	{
	public:

		class Data_Channel : public AXLChannel
		{
		public:
			Data_Channel(char* _pd, AXLF_HART_AO4* AO4, uint channelNum);

			enum class Channel_Select
			{
				Disabled,
				Channel1,
				Channel2,
				Channel3,
				Channel4,
				Unknown = 9
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
			AXLF_HART_AO4* m_AO4;
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

		class AO_Channel : public AXLAnalogOutput
		{
		public:
			AO_Channel(char* _pdIn, char* _pdOut, AXLF_HART_AO4* AO4, uint channelNum);

			uint getValue(double &ret);
			uint setValue(double value);

			enum class OutputRange {
				mA_0_P20	= 4,
				mA_P4_P20 = 6,
				INACTIVE = 0xFF,
				Unknown = 0xFE
			};

			OutputRange getOutputRange();
			bool setOutputRange(OutputRange range);

			enum Error {
				NoError			= 0x0000,
				InactiveChannel = 0x0001,
				UnknownError	= 0x0002,
				InvalidOutput	= 0x0003,
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
			string setValueString(string value);

		protected:

			// AXLAnalogOutput Overrides:

			uint32_t convertValueToRaw(double value, uint16_t& converted);
			uint32_t convertRawToValue(uint16_t value, double& ret);



		private:
			char* pdIn;
			char* pdOut;
			AXLF_HART_AO4* AO4;
			OutputRange outputRange;
			string errorToString(uint);
			void setRangeMinMax();

			// Function enum pointers
			AXLEnumParameter* m_rangeEnum;
		};

		AXLF_HART_AO4(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		AXLF_HART_AO4();
		AO_Channel* aoChannel[4];
		Data_Channel* dataChannel[8];
		virtual const string name();
	};

}


