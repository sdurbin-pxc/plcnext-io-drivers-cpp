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
#include "../../AXLOutput.h"

using namespace std;

namespace PLCnext
{

	class AXLAnalogOutputSE : public AXLOutput
	{
	public:
		AXLAnalogOutputSE(AXLModule* module);

		enum SubstituteBehavior
		{
			Minimum = 0,	//Output of zero values(0 V / 0 mA / 4 mA) at output
			Maximum = 1,	//Output of final values(10 V / 5 V / 20 mA) at output
			HoldLast = 2,	//Hold last value
		};

		bool setSubstituteBehavior(SubstituteBehavior);		
		SubstituteBehavior getSubstituteBehavior();
		double getSetpoint();
	protected:
		bool readSubstituteBehavior();
		SubstituteBehavior m_substituteBehavior;
		virtual uint32_t convertValueToRaw(double value, uint16_t&) = 0;
		virtual uint32_t convertRawToValue(uint16_t value, double& ret) = 0;
		AXLEnumParameter* m_subBehaviorEnum;
		char* pdOut;
	};

}