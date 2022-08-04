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

#include "AXLOutput.h"

using namespace std;

namespace PLCnext
{

	class AXLDigitalOutput : public AXLOutput
	{
	public:
		AXLDigitalOutput() : AXLOutput()
		{
			m_channelType = ChannelType::Digital;
			m_rangeMaximum = 1.0;
			m_rangeMinimum = 0.0;
		}

		// AXLChannel Override

		bool readConfiguration() { return true; }

	};

}