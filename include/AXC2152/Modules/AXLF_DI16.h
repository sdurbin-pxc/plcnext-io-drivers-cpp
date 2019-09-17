/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DI16.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <string>
#include "../AXLModule.h"
#include "../AXLInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DI16 = 0xD6;
	const uint AXLF_MODULE_DI16_4 = 0xD0;
	const uint AXLF_MODULE_DI16_HS = 0xDB;

	class AXLF_DI16 : public AXLModule
	{
	public:
		class DI16_Channel : public AXLInput
		{
		public:
			DI16_Channel(char* _pdIn, uint channel);
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
		DI16_Channel* channel[16];
		AXLF_DI16(AXC2152* axc, ushort _slot, uint pdInOffset);
		ushort getValue();
	private:
		char* pd;
	};

}


