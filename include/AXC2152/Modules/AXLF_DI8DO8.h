/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_DI8DO8.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <string>
#include "../AXLModule.h"
#include "AXLF_DI8.h"
#include "AXLF_DO8.h"

using namespace std;

namespace PLCnext {

	const ushort AXLF_MODULE_DI8DO8 = 0xDD;

	class AXLF_DI8DO8 : public AXLModule
	{
	public:
		virtual const string name();
		AXLF_DO8* do8;
		AXLF_DI8* di8;
		AXLF_DI8DO8(AXC2152* axc, ushort _slot, uint pdInOffset, uint pdOutOffset);
		AXLF_DI8DO8() {}
	};

}


