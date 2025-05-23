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
#include "AXLModule.h"

using namespace std;

namespace PLCnext
{

	class AXLDigitalOutputModule : public AXLModule
	{
	public:
		AXLDigitalOutputModule(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset, uint _type);

		enum SubstituteBehavior
		{
			ZeroOutputs = 0,	// Set the digital output to 0 (Low)
			HoldLast = 1,		// Hold last value

		};

		bool setSubstituteBehavior(SubstituteBehavior);
		SubstituteBehavior getSubstituteBehavior();
		bool setOutputsToFailState();
		bool readConfiguration();
	private:
		void processDiagnostic(Diagnostics&);
		SubstituteBehavior m_substituteBehavior;
	};

}