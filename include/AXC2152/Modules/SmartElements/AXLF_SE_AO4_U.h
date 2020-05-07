/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXLF_SE_AO4.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include "../../AXLModule.h"
#include "../../AXLOutput.h"

using namespace std;

namespace PLCnext {

	const uint AXLF_MODULE_SE_AO4_U = 0x1a10;

	class AXC2152;

	class AXLF_SE_AO4_U : public AXLModule
	{
	public:

		class AO4_Channel : public AXLOutput
		{
		public:
			AO4_Channel(char* _pdIn, char* _pdOut, AXLF_SE_AO4_U* ao4, uint _channelNum);
			uint setValue(double value);
			uint getValue(double &value);


			enum Error
			{
				NoError			= 0x0000,
				UnknownError	= 0x0002,
				InvalidOutput	= 0x0003,
				ShortCircuit	= 0x8003, // Short - circuit
				InvalidParams	= 0x8010, // Parameter table invalid
				SupplyVoltage	= 0x8020, // Faulty supply voltage
				DeviceFault		= 0x8040  // Device faulty
			};

			// AXLOutput Overrides

			Variant getVariantValue();
			string setValueString(string);
			string getUnitsString();
			bool executeFunction(int id, vector<Variant> params);

		private:
			uint channelNum;
			char* pdIn;
			char* pdOut;
			AXLF_SE_AO4_U* ao4;
			string errorToString(uint);



		};

		AXLF_SE_AO4_U(AXC2152* axc, ushort _slot, uint pdInOffset, uint pdOutOffset);
		AO4_Channel* channel[4];
		virtual const string name();


	private:
		bool _pdiRead(ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool _pdiWrite(ushort subSlot, ushort writeIndex, ushort writeSubIndex, char* data, int length);
	};

}


