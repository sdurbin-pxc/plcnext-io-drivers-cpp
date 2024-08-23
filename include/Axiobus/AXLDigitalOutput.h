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
		AXLDigitalOutput();

		virtual void setValue(bool value) = 0;
		virtual bool getValue() = 0;
		virtual bool setFailState() override;

		// AXLChannel Override

		bool readConfiguration() override;

	};

}