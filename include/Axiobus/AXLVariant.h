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

namespace PLCnext
{
	class AXLVariant {
	public:
		enum Type {
			UNKOWN = 0,
			BOOL,
			INT,
			UINT,
			FLOAT,
			STRING
		};

		AXLVariant() {
			data.type = UNKOWN;
			data.intVal = 0;
		}
		AXLVariant(int v) {
			data.type = INT;
			data.intVal = v;
		}
		AXLVariant(bool v) {
			data.type = BOOL;
			data.boolVal = v;
		}
		AXLVariant(double v) {
			data.type = FLOAT;
			data.floatVal = (float)v;
		}
		AXLVariant(float v)
		{
			data.type = FLOAT;
			data.floatVal = v;
		}
		AXLVariant(std::string v) {
			data.type = STRING;
			data.strVal = new std::string(v);
		}
		AXLVariant(unsigned int v) {
			data.type = UINT;
			data.uintVal = v;
		}

		AXLVariant(long long v) {
			data.type = INT;
			data.intVal = (int)v;
		}

		AXLVariant(unsigned long v)
		{
			data.type = UINT;
			data.uintVal = (unsigned int)v;
		}
		
		AXLVariant(AXLVariant const& other)
		{
			*this = other;
		}

		~AXLVariant() {
			stringDeleteCheck();
		}

		Type getType() const
		{
			return data.type;
		}

		AXLVariant& operator = (const AXLVariant& other) {
			if (this != &other)
			{
				stringDeleteCheck();

				switch (other.data.type) {
				case STRING: {
					data.strVal = new std::string(*(other.data.strVal));
					data.type = STRING;
					break;
				}
				default: {
					memcpy(this, &other, sizeof(AXLVariant));
					break;
				}
				}
			}
			return *this;
		}

		AXLVariant& operator = (AXLVariant&& other) {
			if (this != &other)
			{
				memcpy(this, &other, sizeof(AXLVariant));			
				other.data.strVal = nullptr;
			}
			return *this;
		}

		AXLVariant& operator = (int newVal) {
			stringDeleteCheck();
			data.type = INT;
			data.intVal = newVal;
			return *this;
		}

		AXLVariant& operator = (unsigned int newVal) {
			stringDeleteCheck();
			data.type = UINT;
			data.uintVal = newVal;
			return *this;
		}

		AXLVariant& operator = (double newVal) {
			stringDeleteCheck();
			data.type = FLOAT;
			data.floatVal = (float)newVal;
			return *this;
		}

		AXLVariant& operator = (float newVal) {
			stringDeleteCheck();
			data.type = FLOAT;
			data.floatVal = newVal;
			return *this;
		}

		AXLVariant& operator = (std::string& newVal) {
			stringDeleteCheck();
			data.type = STRING;
			data.strVal = new std::string(newVal);
			return *this;
		}

		operator int() const {
			if (data.type == INT)
			{
				return data.intVal;
			}
			else if (data.type == UINT)
			{
				return (int)data.uintVal;
			}
			else if (data.type == FLOAT)
			{
				return (int)data.floatVal;
			}
			else if (BOOL == data.type)
			{
				return (int)data.boolVal;
			}
			else if (STRING == data.type)
			{
				try
				{
					return stoi(*data.strVal);
				}
				catch(...)
				{
				}
			}
			return 0;
		}

		operator long long() const {
			return data.intVal;
		}

		operator bool() const {
			if (data.type == INT)
			{
				return (bool)data.intVal;
			}
			else if (data.type == UINT)
			{
				return (bool)data.uintVal;
			}
			else if (data.type == FLOAT)
			{
				return (bool)data.floatVal;
			}
			else if (BOOL == data.type)
			{
				return data.boolVal;
			}
			else if (STRING == data.type)
			{
				if (data.strVal->length() == 4 &&
					(((*data.strVal)[0] == 't' || (*data.strVal)[0] == 'T') &&
					((*data.strVal)[1] == 'r' || (*data.strVal)[1] == 'R') &&
						((*data.strVal)[2] == 'u' || (*data.strVal)[2] == 'U') &&
						((*data.strVal)[3] == 'e' || (*data.strVal)[3] == 'E')))
					return true;
				else if (data.strVal->length() == 1 && (*data.strVal)[0] == '1')
					return true;
				return false;
			}
			throw std::runtime_error("bad cast");
		}

		operator unsigned int() const {
			if (UINT == data.type)
			{
				return data.uintVal;
			}
			else if (INT == data.type)
			{
				return (unsigned int)data.intVal;
			}
			else if (FLOAT == data.type)
			{
				return (unsigned int)data.floatVal;
			}
			else if (STRING == data.type)
			{
				try
				{
					return stoul(*data.strVal);
				}
				catch (...)
				{
					return 0;
				}
			}
			throw std::runtime_error("bad cast");
		}

		operator float() const {
			if (UINT == data.type)
			{
				return (float)data.uintVal;
			}
			else if (INT == data.type)
			{
				return (float)data.intVal;
			}
			else if (FLOAT == data.type)
			{
				return (float)data.floatVal;
			}
			else if (BOOL == data.type)
			{
				return (float)data.boolVal;
			}
			else if (STRING == data.type)
			{
				try
				{
					return stof(*data.strVal);
				}
				catch (...)
				{
					return 0;
				}
			}
			throw std::runtime_error("bad cast");
		}

		operator std::string() const {
			if (STRING == data.type) {
				return *data.strVal;
			}
			else if (FLOAT == data.type)
			{
				return std::to_string(data.floatVal);
			}
			else if (INT == data.type)
			{
				return std::to_string(data.intVal);
			}
			else if (UINT == data.type)
			{
				return std::to_string(data.uintVal);
			}
			else if (BOOL == data.type)
			{
				if (data.boolVal)
				{
					return "true";
				}
				return "false";
			}
			throw std::runtime_error("bad cast");
		}
		bool operator==(const AXLVariant &other) const
		{
			//if (data.type != other.data.type)
			//	return false;
			if (data.type == BOOL)
				return data.boolVal == (bool)other;
			else if (data.type == INT)
				return data.intVal == (int)other;
			if (data.type == FLOAT)
				return data.floatVal == (float)other;
			else if (data.type == UINT)
				return data.uintVal == (unsigned int)other;
			else if (data.type == STRING)
			{
				
				return strcmp(((std::string)other).c_str(), (*data.strVal).c_str()) == 0;
			}
			return false;
		}
	private:

		struct {
			Type type;
			union
			{
				int intVal;
				uint uintVal;
				float floatVal;
				bool boolVal;
				std::string* strVal;
			};
		} data;

		void stringDeleteCheck()
		{
			if (data.type == STRING && data.strVal != nullptr) {
				delete data.strVal;
			}
		}
	};
}