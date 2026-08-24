/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLFunction.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdarg>
#include "AXLVariant.h"
#include <functional>

#define AXL_FUNCTION(NAME, DESCRIPTION, PARAMS, BODY, ISCONFIG) \
    addFunction(NAME, DESCRIPTION, PARAMS, [this](vector<AXLVariant>& args) -> AXLFunction::ReturnCode BODY, ISCONFIG)

using namespace std;


namespace PLCnext
{
	class AXLChannel;
	class AXLFunctional;

	class AXLParameter
	{
	public:
		enum Type
		{
			INT,
			REAL,
			ENUM
		};
		virtual Type getType() = 0;
		virtual AXLVariant getCurrentValue() = 0;
		string name;
		virtual ~AXLParameter() = default;
	};

	struct AXLEnumPair
	{
		string text;
		int value;
	};

	class AXLEnumParameter : public AXLParameter
	{
	public:
		AXLEnumParameter(string);
		Type getType() { return ENUM;  }
		void addItem(string text, int value);
		int getValue(string);
		void setCurrentValue(AXLVariant);
		AXLVariant getCurrentValue();
		string getString(int);
		const vector<string>& getStrings();
		virtual ~AXLEnumParameter() = default;
	private:
		unordered_map<string, int> values;
		vector<string> strings;
		int m_currentValue;

	};

	class AXLIntegerParameter : public AXLParameter
	{
	public:
		Type getType() { return INT; }
		AXLIntegerParameter(string _name, long long val, long long min, long long max);
		long long getMax();
		long long getMin();
		void setCurrentValue(AXLVariant);
		AXLVariant getCurrentValue();
		virtual ~AXLIntegerParameter() = default;
	private:
		long long m_currentValue;
		long long m_min;
		long long m_max;
	};

	class AXLRealParameter : public AXLParameter
	{
	public:
		Type getType() { return REAL; }
		AXLRealParameter(string _name, double val, double min, double max);
		double getMax();
		double getMin();
		void setCurrentValue(AXLVariant);
		AXLVariant getCurrentValue();
		virtual ~AXLRealParameter() = default;
	private:
		double m_currentValue;
		double m_min;
		double m_max;
	};

	class AXLFunction
	{
	public:

		enum ReturnCode
		{
			SUCCESS,
			INVALID_PARAMS,
			FAIL
		};

		AXLFunction(int _id, string _name, string _description, vector<AXLParameter*> params, AXLFunctional* _owner, function<ReturnCode(vector<AXLVariant>& params)> execute, bool isConfiguration);

		int getId();
		string getName();
		bool isConfiguration();
		const vector<AXLParameter*>& getParams();
		string getCamelCaseName();
		ReturnCode execute(vector<AXLVariant>& arguments);

		~AXLFunction();
	protected:
		int m_id;
		bool m_isConfig;
		std::function<ReturnCode(vector<AXLVariant>&)> m_functionCall;
		AXLFunctional* m_owner;
		string m_name;
		string m_description;
		vector<AXLParameter*> m_params;
	};
}