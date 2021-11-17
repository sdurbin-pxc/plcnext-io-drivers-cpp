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

	class AXLDigitalInput : public AXLInput
	{
	public:
		AXLDigitalInput() : AXLInput()
		{
			m_channelType = ChannelType::Digital;
			m_rangeMaximum = 1.0;
			m_rangeMinimum = 0.0;
		}

	};

}