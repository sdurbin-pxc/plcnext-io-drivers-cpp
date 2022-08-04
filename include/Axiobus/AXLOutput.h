/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLOutput.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <string>
#include "AXLChannel.h"

using namespace std;

namespace PLCnext
{

	class AXLOutput : public AXLChannel
	{
	public:
		AXLOutput();
		virtual string setValueString(string) = 0;
	};

}