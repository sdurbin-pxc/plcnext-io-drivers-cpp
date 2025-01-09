/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DO8.h
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

	const uint AXLF_MODULE_DO8 = 0xD5;

	class AXLF_DO8 : public AXLDigitalOutputModule
	{
	public:
		class DO8_Channel : public AXLDigitalOutput
		{
		public:
			DO8_Channel(char* _pdOut, uint channel);
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

		const string name() override;
		DO8_Channel* channel[8];
		AXLF_DO8(Axiobus* axc, ushort _slot, uintptr_t pdOutOffset);
		void setValue(char value);
		char getValue();
	private:
		char* pd;
	};

}


