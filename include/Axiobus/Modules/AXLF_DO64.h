/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DO64.h
*
*  Created on: November 18, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <string>
#include "../AXLDigitalOutputModule.h"
#include "../AXLOutput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DO64 = 0x0DF;

	class AXLF_DO64 : public AXLDigitalOutputModule
	{
	public:
		class DO64_Channel : public AXLOutput
		{
		public:
			DO64_Channel(char* _pdOut, uint channel);
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
		DO64_Channel* channel[64];
		AXLF_DO64(Axiobus* axc, ushort _slot, uintptr_t pdOutOffset);
		void setValue(unsigned long long value);
		unsigned long long getValue();
	private:
		char* pd;
	};

}


