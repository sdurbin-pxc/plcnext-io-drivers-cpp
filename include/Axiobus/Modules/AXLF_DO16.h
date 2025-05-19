/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DO16.h
*
*  Created on: November 18, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <string>
#include "../AXLDigitalOutputModule.h"
#include "../AXLDigitalOutput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DO16_FLK = 0x0DC;
	const uint AXLF_MODULE_DO16 = 0x0D7;
	const uint AXLF_MODULE_DO16_2H = 0xD07;
	const uint AXLF_MODULE_DO16_2F = 0x0D1;

	class AXLF_DO16 : public AXLDigitalOutputModule
	{
	public:
		class DO16_Channel : public AXLDigitalOutput
		{
		public:
			DO16_Channel(char* _pdOut, AXLModule* module, uint channel);
			void setValue(bool value);
			bool getValue();

			// AXLOutput Overrides

			Variant getVariantValue() override;
			ValueWithError getValueWithError() override;
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params) { return false; }
		private:
			uint channel;
			char* pdOut;
		};

		const string name() override;
		DO16_Channel* channel[16];
		AXLF_DO16(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		void setValue(ushort value);
		ushort getValue();
	};

}


