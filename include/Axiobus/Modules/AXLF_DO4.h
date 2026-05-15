/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DO4.h
*
*  Created on: July 11, 2019
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

	const uint AXLF_MODULE_DO4 = 0xB0D02;
	const uint AXLF_MODULE_DO4_21_60 = 0xB0D03;

	class AXLF_DO4 : public AXLDigitalOutputModule
	{
	public:
		class DO4_Channel : public AXLDigitalOutput
		{
		public:
			DO4_Channel(char* _pdOut, AXLModule* module, uint channel);
			void setValue(bool value);
			bool getValue();

			// AXLOutput Overrides

			AXLVariant getVariantValue() override;
			ValueWithError getValueWithError() override;
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<AXLVariant> params) { return false; }
		private:
			uint channel;
			char* pdOut;
		};

		const string name() override;
		DO4_Channel* channel[8];
		AXLF_DO4(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		void setValue(char value);
		char getValue();
	};

}


