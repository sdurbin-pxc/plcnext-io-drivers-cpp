/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_SE_Empty.h
*
*  Created on: January 8, 2025
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <string>
#include "../../AXLModule.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_SE_SCA = 0x531005;

	class AXLF_SE_SCA : public AXLModule
	{
	public:
		AXLF_SE_SCA(Axiobus* _axc, ushort _slot, uintptr_t pdInOffset, uintptr_t pdOutOffset);
		const string name() override;
	};
}
