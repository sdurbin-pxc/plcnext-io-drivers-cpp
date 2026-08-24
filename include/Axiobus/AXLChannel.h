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
#include "AXLFunctional.h"
#include "AXLModule.h"

using namespace std;

namespace PLCnext
{
	class AXLChannel : public AXLFunctional
	{
	public:

		AXLChannel(AXLModule* module);

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
			AnalogSE,
			Unknown
		};

		struct ValueWithError
		{
			AXLVariant value;
			uint32_t error;
			uint32_t genericError;
		};

		enum GenericError
		{
			NONE,
			INACTIVE,
			INVALID_CONFIG,
			POWER_SUPPLY,
			HARDWARE_FAULT,
			UNDER_RANGE,
			OVER_RANGE,
			OUT_OF_RANGE,
			OPEN_CIRCUIT,
			SHORT_CIRCUIT,
			SENSOR_FAIL,
			MISSING,
			UNKNOWN
		};

		const ChannelDirection getChannelDirection();
		const ChannelType getChannelType();
		virtual AXLVariant getVariantValue() = 0;
		virtual ValueWithError getValueWithError() = 0;
		virtual string getUnitsString() = 0;
		//bool executeFunction(int id, vector<AXLVariant> params) override;
		virtual bool readConfiguration() = 0;
		virtual GenericError errorToGeneric(uint error) = 0;
		virtual ~AXLChannel();
		bool configurationChanged();
		virtual bool setFailState();

		Axiobus* getAxioMaster();
		uint getChannelNumber();
		double getRangeMinimum();
		double getRangeMaximum();
		AXLModule* getModule();

	private:
		uint m_lastConfigCnt;
		uint m_currConfigCnt;
		friend class Axiobus;
	protected:
		void configChangeNotify();
		ChannelDirection channelDirection;
		ChannelType m_channelType;
		AXLModule* m_module;
		uint channelNum;
		double m_rangeMinimum;
		double m_rangeMaximum;
	};

}