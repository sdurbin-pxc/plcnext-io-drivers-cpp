/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DI32.h
*
*  Created on: November 14, 2019
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

	const uint AXLF_MODULE_DI32 = 0xD2;
	const uint AXLF_MODULE_DI32_2H = 0xD03;


	class AXLF_DI32 : public AXLModule
	{
	public:
		class DI32_Channel : public AXLDigitalInput
		{
		public:
			DI32_Channel(char* _pdIn, uint channel);
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
		DI32_Channel* channel[32];
		AXLF_DI32(Axiobus* axc, ushort _slot, uintptr_t pdInOffset);
		uint getValue();
	private:
		char* pd;
	};

}


