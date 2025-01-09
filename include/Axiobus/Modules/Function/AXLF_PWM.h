/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_PWM.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <unistd.h>
#include "../../AXLModule.h"
#include "../../AXLOutput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_PWM = 0xF8;

	class Axiobus;

	class AXLF_PWM : public AXLModule
	{
	public:

		class PWM_Channel : public AXLOutput
		{
		public:

			PWM_Channel(char* _pdOut, AXLF_PWM* pwm, uint channelNum);
			
			// Pdi Config Functions
			bool setMode(ushort mode);
			ushort getMode();
			bool setDivider(ushort divider);
			ushort getDivider();
			bool setPulseWidth(ushort pulseWidth);
			ushort getPulseWidth();

			// Process Data Functions
			uint setPwmOutput(double dutyFactorPercent, ushort frequency);
			uint sendPulses(double dutyFactorPercent, ushort numberOfPulses);
			uint setPushPullOut(bool value);

			enum Mode {
				PWM = 1,
				PulseGenerator = 2,
				PushPullOutput = 3
			};

			enum Divider {
				DIV_BY_1 = 0,
				DIV_BY_10 = 1,
				DIV_BY_100 = 2
			};

			Variant getVariantValue();
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

			// AXLChannel Overrides

			bool readConfiguration();

			enum Error
			{
				NoError = 0x0000,
				OutOfRange = 0x0001,
				InvalidMode = 0x0002,
			};

		private:
			char* pdOut;
			//uint channelNum;
			uint m_mode;
			ushort m_divider;
			ushort m_pulseWidth;
			string errorToString(uint);
			AXLEnumParameter* m_modeEnum;
			AXLEnumParameter* m_dividerEnum;
			AXLIntegerParameter* m_pulseWidthParam;
		};

		AXLF_PWM(Axiobus* _axc, ushort _slot, uintptr_t pdOutOffset);
		AXLF_PWM();
		PWM_Channel* channel[2];
		const string name() override;
	};

}


