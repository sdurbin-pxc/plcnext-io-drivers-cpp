/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DI64.h
*
*  Created on: November 14, 2019
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

	const uint AXLF_MODULE_DI64 = 0xD8;

	class AXLF_DI64 : public AXLModule
	{
	public:
		class DI64_Channel : public AXLInput
		{
		public:
			DI64_Channel(char* _pdIn, uint channel);
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
		DI64_Channel* channel[64];
		AXLF_DI64(AXC2152* axc, ushort _slot, uint pdInOffset);
		unsigned long long getValue();
	private:
		char* pd;
	};

}


