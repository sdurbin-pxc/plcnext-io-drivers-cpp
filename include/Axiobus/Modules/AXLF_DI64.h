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
#include "../AXLDigitalInput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DI64 = 0xD8;

	class AXLF_DI64 : public AXLModule
	{
	public:
		class DI64_Channel : public AXLDigitalInput
		{
		public:
			DI64_Channel(char* _pdIn, AXLModule* module, uint channel);
			bool getValue();

			// AXLInput Overrides

			Variant getVariantValue() override;
			ValueWithError getValueWithError() override;
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params) { return false; }
		private:
			uint channel;
			char* pdIn;
		};

		const string name() override;
		DI64_Channel* channel[64];
		AXLF_DI64(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		unsigned long long getValue();
	};

}


