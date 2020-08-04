/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  AXC2152.h
*
*  Created on: July 11, 2019
*      Author: Steven Durbin
*
*  To obtain the latest release or post an issue, please visit the official GitHub repository:
*
*	https://github.com/sdurbin-pxc/plcnext-io-drivers-cpp
*
******************************************************************************/

#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include "../AXC2152/AXLModule.h"
#include "../AXC2152/Modules/AXLF_AI4_I.h"
#include "../AXC2152/Modules/AXLF_AI4_U.h"
#include "../AXC2152/Modules/AXLF_AI8.h"
#include "../AXC2152/Modules/AXLF_AO4.h"
#include "../AXC2152/Modules/AXLF_DO8.h"
#include "../AXC2152/Modules/AXLF_DO16.h"
#include "../AXC2152/Modules/AXLF_DO32.h"
#include "../AXC2152/Modules/AXLF_DO64.h"
#include "../AXC2152/Modules/AXLF_DI8.h"
#include "../AXC2152/Modules/AXLF_DI16.h"
#include "../AXC2152/Modules/AXLF_DI32.h"
#include "../AXC2152/Modules/AXLF_DI64.h"
#include "../AXC2152/Modules/AXLF_DI8DO8.h"
#include "../AXC2152/Modules/AXLF_AI2AO2.h"
#include "../AXC2152/Modules/AXLF_UTH.h"
#include "../AXC2152/Modules/AXLF_RTD.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_AI4_I.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_AI4_U.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_AO4_I.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_AO4_U.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_DI16.h"
#include "../AXC2152/Modules/SmartElements/AXLF_SE_DO16.h"
#include "../AXC2152/Modules/Function/AXLF_CNT.h"

#define PROCESS_DATA_SIZE 512

using namespace std;

namespace PLCnext {


	class AXC2152 {
		friend class AXLModule;
	public:

		struct DiagnosticsInfo
		{
			ushort status;  // Bus status flags
			ushort param1;  // Error code
			ushort param2;  // Error Location (slot number, 1 based index);
		};

		AXC2152();
		bool initialize();
		const vector<AXLModule*>& getModules() const;
		void scanModules();
		DiagnosticsInfo getDiagnosticsInfo();
		int saveConfiguration(string filePath);
		bool loadConfiguration(string filePath, string &error);
		uint getBaseModuleType(uint type);
		string getBaseModuleName(uint baseType);
		uint moduleTypeFromName(string name);
		uint getInitializationError();
		bool isInitialized();
		~AXC2152();

		// Functions to interpret diagnostic flags:
		bool ioWarning();
		bool ioError();
		bool busError();
		bool controllerError();
		bool busOperational();

		// Device functions

		void setAxioSampleRate(uint);
		void setPdiRequestRate(uint);

		double deviceTemperature();
		
	private:

		struct PDIPipe {
			uint16_t slot;
			uint16_t subSlot;
			uint16_t index;
			uint16_t subIndex;
			uint16_t requestCnt;
			uint16_t finishedCnt;
			uint16_t dataCount;
			uint16_t error;
			uint16_t addInfo[2];
			uint8_t data[128];
		};

		bool m_initialized;
		int fd;
		int pdiMutexFd;
		pthread_mutex_t* pdiWriteMutex;
		pthread_mutex_t* pdiReadMutex;
		char* map;
		size_t mapSize;
		AXLModule* moduleFromType(ushort slot, uint type, uint &pdInOffset, uint &pdOutOffset, bool missing);
		double timeSpecToSeconds(struct timespec* ts);
		vector<AXLModule*> modules;
		uint m_initError;
	protected:
		bool pdiRead(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		bool pdiWrite(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, char* data, int length);
	private:
		pair<uint, uint> getProcessDataSize(ushort type, char data[]);
	};

}