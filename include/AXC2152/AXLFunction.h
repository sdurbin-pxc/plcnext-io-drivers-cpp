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


using namespace std;


namespace PLCnext
{
	class AXLChannel;

	class AXLParameter
	{
	public:
		enum Type
		{
			NUMBER,
			ENUM
		};
		virtual Type getType() = 0;
		string name;
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
		const vector<string>& getStrings();
	private:
		unordered_map<string, int> values;
		vector<string> strings;

	};

	/*
	class AXLIntegerParameter : public AXLParameter
	{
	public:
		int min;
		int max;
	};
	

	class AXLDoubleParameter : public AXLParameter
	{
		double min;
		double max;
	};
	*/

	class AXLFunction
	{
	public:
		AXLChannel* owner;
		string name;
		string description;
		vector<AXLParameter*> params;
		AXLFunction(int _id, string _name, string _description, vector<AXLParameter*> params, AXLChannel* _owner);
		int getId() { return id; };
	protected:
		int id;
	private:

	};
}