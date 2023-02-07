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
		
		SubstituteBehavior getSubstituteBehavior();
		double getSubstituteValue();
		bool setFailState();
		double getSetpoint();
	protected:
		virtual uint setValue(double value) = 0;
		virtual uint getValue(double &value) = 0;
		bool readSubstituteBehavior();
		SubstituteBehavior m_substituteBehavior;
		double m_substituteValue;
		virtual uint32_t convertValueToRaw(double value, uint16_t&) = 0;
		virtual uint32_t convertRawToValue(uint16_t value, double& ret) = 0;
		AXLEnumParameter* m_subBehaviorEnum;
		AXLRealParameter* m_subValueParam;
		AXLEnumParameter* m_filterEnum;
		double m_nominalMax;
		double m_nominalMin;
		char* pdOut;
		virtual bool executeFunction(int id, vector<Variant> params);
	};

}