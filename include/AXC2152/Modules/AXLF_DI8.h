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
#include "../AXLInput.h"

using namespace std;

namespace PLCnext {

	const ushort AXLF_MODULE_DI8 = 0xD03;

	class AXLF_DI8 : public AXLModule
	{
	public:
		class DI8_Channel : public AXLInput
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
		AXLF_DI8(AXC2152* axc, ushort _slot, uint pdInOffset);
		char getValue();
	private:
		char* pd;
	};
}


