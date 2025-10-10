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
#include "../AXLDigitalOutputModule.h"
#include "AXLF_DI8.h"
#include "AXLF_DO8.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_DI8DO8 = 0xDD;
	const uint AXLF_MODULE_DI8DO8_3 = 0xD02;

	class AXLF_DI8DO8 : public AXLDigitalOutputModule
	{
	public:
		const string name() override;
		AXLF_DO8* do8;
		AXLF_DI8* di8;
		AXLF_DI8DO8(Axiobus* axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
	private:
		void processDiagnostic(Diagnostics&);
	};

}


