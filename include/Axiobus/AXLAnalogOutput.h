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
#include "AXLOutput.h"

using namespace std;

namespace PLCnext
{

	class AXLAnalogOutput : public AXLOutput
	{
	public:
		AXLAnalogOutput();

		enum SubstituteBehavior
		{
			Minimum = 0,	//Output of zero values(0 V / 0 mA / 4 mA) at output
			Maximum = 1,	//Output of final values(10 V / 5 V / 20 mA) at output
			HoldLast = 2,	//Hold last value
			Substitute = 3	// Transfer the substitute value
		};

		bool setSubstituteBehavior(SubstituteBehavior);
		bool setSubstituteValue(double);

	protected:
		//SubstituteBehavior m_substituteBehavior;
		//uint16_t m_substituteValue;
		virtual uint32_t convertValueToRaw(double value, uint16_t&) = 0;
	};

}