/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DI8.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <string>
#include "../AXLModule.h"
#include "../AXLDigitalInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DI8 = 0xD0D03;
	const uint AXLF_MODULE_DI8_110_220 = 0xD01;
	const uint AXLF_MODULE_DI8_48_60 = 0xD0D02;

	class AXLF_DI8 : public AXLModule
	{
	public:
		class DI8_Channel : public AXLDigitalInput
		{
		public:
			DI8_Channel(char* _pdIn, uint channel);
			bool getValue();

			// AXLInput Overrides

			Variant getVariantValue();
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params) { return false; }

		private:
			uint channel;
			char* pdIn;
		};

		virtual const string name();
		DI8_Channel* channel[8];
		AXLF_DI8(Axiobus* axc, ushort _slot, uintptr_t pdInOffset);
		char getValue();
	private:
		char* pd;
	};
}


