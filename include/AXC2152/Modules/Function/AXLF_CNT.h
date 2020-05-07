/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_CNT.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <unistd.h>
#include "../../AXLModule.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_CNT = 0xF1;

	class AXC2152;

	class AXLF_CNT : public AXLModule
	{
	public:

		class CNT_Channel
		{
		public:

			struct CounterConfiguration {
				ushort countType;
				ushort gateMode;
				ushort directionStopMode;
				ushort outputMode;
				ushort outputReact;
				ushort outputPulseTimeMs;
				uint	initialCountValue;
				uint	lowerCountLimit;
				uint	upperCountLimit;
			};

			CNT_Channel(char* _pdIn, char* _pdOut, AXLF_CNT* cnt, uint channelNum);
			bool start();
			bool isRunning();
			uint getCount();
			bool stop();
			bool resetCount();
			bool setCountDirection(ushort direction);
			bool setCountLimits(uint low, uint high);
			ushort getCountDirection();
			bool setConfiguration(CounterConfiguration cfg);
			CounterConfiguration getConfiguration();

			enum CountDirection {
				Down = 0,
				Up = 1
			};

			enum CountConfig_CountType {
				OneTime = 0,
				Periodic = 1
			};

			enum CountConfig_GateMode {
				GateOff					= 0,
				CountAtHighLevel		= 1 << 4,
				CountAtLowLevel			= 2 << 4,
				StartOnRisingEdge		= 3 << 4,
				StartOnFallingEdge		= 4 << 4,
				CountHighResetRisin		= 5 << 4,
				CountLowResetFalling	= 6 << 4
			};

			enum CountConfig_DirectionStop {
				NoFunction						= 0,
				ChangeDirectionOnRiseStartUp	= 1 << 8,
				ChangeDirectionOnRiseStartDown	= 2 << 8,
				ChangeDirectionOnFallStartUp	= 3 << 8,
				ChangeDirectionOnFallStartDown	= 4 << 8,
				CountUpAtHighLevel				= 5 << 8,
				CountUpAtLowLevel				= 6 << 8,
				StopOnRisingEdge				= 7 << 8,
				StopOnFallingEdge				= 8 << 8
			};

			enum CountConfig_OutputMode {
				Deactivated		= 0,
				High			= 1,
				Low				= 2,
				ToggleStartLow	= 3,
				ToggleStartHigh = 4,
				HighPulse		= 5,
				LowPulse		= 6,
				Manual			= 7
			};

			enum CountConfig_OutputReact {
				NotUsed			= 0,
				LowerCountLimit = 1 << 4,
				UpperCountLimit = 2 << 4,
				BothLimits		= 3 << 4
			};
			bool executeFunction(int id, vector<Variant> params) { return false; }
		private:
			char* pdIn;
			char* pdOut;
			CounterConfiguration counterConfiguration;
			AXLF_CNT* cnt;
			uint channelNum;
			void bitClear(int wordNum, int bit);
			void bitSet(int wordNum, int bit);
			bool getBit(int wordNum, int bit);
			bool initConfiguration();
			double timeSpecToSeconds(struct timespec* ts);

#pragma pack(push, 1)

			struct CounterPdiParams
			{
				ushort	BasicConfig;
				ushort	Reserved;
				ushort	OutputConfig;
				ushort	OutputPulseTime;
				uint	StartValue;
				uint	LowerLimit;
				uint	UpperLimit;
				uint	Reserved2[6];
			};

#pragma pack(pop)

		};

		AXLF_CNT(AXC2152* _axc, ushort _slot, uint pdInOffset, uint pdOutOffset);
		AXLF_CNT();
		CNT_Channel* channel[2];
		virtual const string name();
	private:
		bool _pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool _pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
	};

}


