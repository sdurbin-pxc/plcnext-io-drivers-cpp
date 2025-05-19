/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLAnalogInput.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include "AXLInput.h"

using namespace std;

namespace PLCnext
{

	class AXLAnalogInput : public AXLInput
	{
	public:
		AXLAnalogInput(AXLModule* module);
	};

}