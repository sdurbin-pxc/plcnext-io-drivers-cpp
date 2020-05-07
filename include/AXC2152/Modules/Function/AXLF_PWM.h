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

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_PWM = 0xF8;

	class AXC2152;

	class AXLF_PWM : public AXLModule
	{
	public:

		class PWM_Channel
		{
		public:

			PWM_Channel(char* _pdOut, AXLF_PWM* pwm, uint channelNum);
			
			bool setMode(uint mode);
			uint getMode();

			bool executeFunction(int id, vector<Variant> params) { return false; }
		private:
			char* pdOut;
			AXLF_PWM* pwm;
			uint channelNum;


		};

		AXLF_PWM(AXC2152* _axc, ushort _slot, uint pdOutOffset);
		AXLF_PWM();
		PWM_Channel* channel[2];
		virtual const string name();
	private:
		bool _pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool _pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
	};

}


