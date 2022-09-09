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


using namespace std;


namespace PLCnext
{
	class AXLChannel;

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
		virtual Variant getCurrentValue() = 0;
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
		void setCurrentValue(Variant);
		Variant getCurrentValue();
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
		void setCurrentValue(Variant);
		Variant getCurrentValue();
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
		void setCurrentValue(Variant);
		Variant getCurrentValue();
		virtual ~AXLRealParameter() = default;
	private:
		double m_currentValue;
		double m_min;
		double m_max;
	};

	class AXLFunction
	{
	public:
		AXLChannel* owner;
		string name;
		string description;
		vector<AXLParameter*> params;
		AXLFunction(int _id, string _name, string _description, vector<AXLParameter*> params, AXLChannel* _owner, bool isConfiguration);
		int getId();
		bool isConfiguration();
		string getCamelCaseName();
		~AXLFunction();
	protected:
		int id;
		bool m_isConfig;

	};
}