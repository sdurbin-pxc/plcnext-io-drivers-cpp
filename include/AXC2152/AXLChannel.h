/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLChannel.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <string>
#include "AXLVariant.h"
#include "AXLFunction.h"

using namespace std;

namespace PLCnext
{
	class AXLChannel
	{
	public:
		enum ChannelType
		{
			Input,
			Output
		};
		const ChannelType getChannelType() { return channelType;  }
		const vector<AXLFunction*>& getFunctions() { return functions;  }
		virtual Variant getVariantValue() = 0;
		virtual string getUnitsString() = 0;
		virtual bool executeFunction(int id, vector<Variant> params) = 0;
	protected:
		ChannelType channelType;
		vector<AXLFunction*> functions;
	};

}