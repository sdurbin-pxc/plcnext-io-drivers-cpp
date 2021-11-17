/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DO32.h
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

	const uint AXLF_MODULE_DO32 = 0x0D3;
	const uint AXLF_MODULE_DO32_2H = 0xD06;

	class AXLF_DO32 : public AXLDigitalOutputModule
	{
	public:
		class DO32_Channel : public AXLDigitalOutput
		{
		public:
			DO32_Channel(char* _pdOut, uint channel);
			void setValue(bool value);
			bool getValue();

			// AXLOutput Overrides

			Variant getVariantValue();
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params) { return false; }
		private:
			uint channel;
			char* pdOut;
		};

		virtual const string name();
		DO32_Channel* channel[32];
		AXLF_DO32(Axiobus* axc, ushort _slot, uintptr_t pdOutOffset);
		void setValue(uint value);
		uint getValue();
	private:
		char* pd;
	};

}


