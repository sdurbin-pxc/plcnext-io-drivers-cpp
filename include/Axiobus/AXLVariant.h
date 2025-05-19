/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLVariant.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <string.h>
#include <iostream>

class Variant {
public:
	enum Type {
		UNKOWN = 0,
		BOOL,
		INT,
		DOUBLE,
		STRING
	};
	Variant() {
		data.type = UNKOWN;
		data.intVal = 0;
	}
	Variant(int v) {
		data.type = INT;
		data.intVal = v;
	}
	Variant(double v) {
		data.type = DOUBLE;
		data.realVal = v;
	}
	Variant(std::string v) {
		data.type = STRING;
		data.strVal = new std::string(v);
	}
	Variant(unsigned int v) {
		data.type = INT;
		data.intVal = v;
	}

	Variant(long long v) {
		data.type = INT;
		data.intVal = v;
	}
	//the missing copy constructor
	Variant(Variant const& other)
	{
		*this = other;// redirect to the copy assignment
	}

	~Variant() {
		if (STRING == data.type) {
			delete data.strVal;
		}
	}

	Type getType() const
	{
		return data.type;
	}
	Variant& operator = (const Variant& other) {
		if (this != &other)
		{
			if (STRING == data.type) {
				delete data.strVal;
			}

			switch (other.data.type) {
			case STRING: {
				data.strVal = new std::string(*(other.data.strVal));
				data.type = STRING;
				break;
			}
			default: {
				memcpy(this, &other, sizeof(Variant));
				break;
			}
			}
		}
		return *this;
	}
	Variant& operator = (int newVal) {
		if (STRING == data.type) {
			delete data.strVal;
		}
		data.type = INT;
		data.intVal = newVal;
		return *this;
	}

	Variant& operator = (double newVal) {
		if (STRING == data.type) {
			delete data.strVal;
		}
		data.type = DOUBLE;
		data.realVal = newVal;
		return *this;
	}

	Variant& operator = (std::string& newVal) {
		if (STRING == data.type) {
			delete data.strVal;
		}
		data.type = STRING;
		data.strVal = new std::string(newVal);
		return *this;
	}
	operator int() const {
		if (INT == data.type)
		{
			return data.intVal;
		}
		//do type conversion if you like
		throw std::runtime_error("bad cast");
	}

	operator unsigned int() const {
		if (INT == data.type)
		{
			return data.intVal;
		}
		//do type conversion if you like
		throw std::runtime_error("bad cast");
	}

	operator long long() const {
		if (INT == data.type)
		{
			return data.intVal;
		}
		//do type conversion if you like
		throw std::runtime_error("bad cast");
	}

	operator double() const {
		if (DOUBLE == data.type) {
			return data.realVal;
		}
		else if (STRING == data.type)
		{
			try
			{
				return stod(*data.strVal);
			}
			catch (...)
			{

			}
		}
		//do type conversion if you like
		throw std::runtime_error("bad cast");
	}

	operator std::string() const{
		if (STRING == data.type) {
			return *data.strVal;
		}
		else if (DOUBLE == data.type)
		{
			return std::to_string(data.realVal);
		}
		throw std::runtime_error("bad cast");
	}
	bool operator==(const Variant &other) const
	{
		Type t = getType();
		if (t != other.getType())
			return false;

		if (t == DOUBLE)
			return data.realVal == (double)other;
		else if (t == INT)
			return data.intVal == (int)other;
		else if (t == STRING)
			return strcmp(((std::string)other).c_str(),(*data.strVal).c_str()) == 0;
		return false;
	}
private:

	struct {
		Type type;
		union
		{
			long long intVal;
			double realVal;
			std::string* strVal;
		};
	} data;
};