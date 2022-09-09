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
#include "AXLModule.h"

using namespace std;

namespace PLCnext
{
	class AXLChannel
	{
	public:

		AXLChannel();

		enum ChannelDirection
		{
			Input,
			Output,
			InputOutput
		};

		enum ChannelType
		{
			Digital,
			Analog,
			Unknown
		};

		const ChannelDirection getChannelDirection();
		const ChannelType getChannelType();
		const vector<AXLFunction*>& getFunctions();
		virtual Variant getVariantValue() = 0;
		virtual string getUnitsString() = 0;
		virtual bool executeFunction(int id, vector<Variant> params) = 0;
		virtual bool readConfiguration() = 0;
		virtual ~AXLChannel();
		bool configurationChanged();

		Axiobus* getAxioMaster();
		uint getChannelNumber();
		double getRangeMinimum();
		double getRangeMaximum();

	private:
		uint m_lastConfigCnt;
		uint m_currConfigCnt;
		friend class Axiobus;
	protected:
		void configChangeNotify();
		ChannelDirection channelDirection;
		ChannelType m_channelType;
		vector<AXLFunction*> functions;
		AXLModule* m_module;
		uint channelNum;
		double m_rangeMinimum;
		double m_rangeMaximum;
		uint m_functionCount;
	};

}