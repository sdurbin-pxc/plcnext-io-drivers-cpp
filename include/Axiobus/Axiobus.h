/******************************************************************************
*
*  Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
*	Licensed under the MIT. See LICENSE file in the project root for full license information.
*
*  Axiobus.h
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
#include "AXLModule.h"
#include "Modules/AXLF_AI4_I.h"
#include "Modules/AXLF_AI4_U.h"
#include "Modules/AXLF_AI8.h"
#include "Modules/AXLF_AO4.h"
#include "Modules/AXLF_DO8.h"
#include "Modules/AXLF_DO16.h"
#include "Modules/AXLF_DO32.h"
#include "Modules/AXLF_DO64.h"
#include "Modules/AXLF_DI8.h"
#include "Modules/AXLF_DI16.h"
#include "Modules/AXLF_DI32.h"
#include "Modules/AXLF_DI64.h"
#include "Modules/AXLF_DI8DO8.h"
#include "Modules/AXLF_AI2AO2.h"
#include "Modules/AXLF_UTH.h"
#include "Modules/AXLF_RTD.h"
#include "Modules/SmartElements/AXLF_SE_AI4_I.h"
#include "Modules/SmartElements/AXLF_SE_AI4_U.h"
#include "Modules/SmartElements/AXLF_SE_AO4_I.h"
#include "Modules/SmartElements/AXLF_SE_AO4_U.h"
#include "Modules/SmartElements/AXLF_SE_DI16.h"
#include "Modules/SmartElements/AXLF_SE_DO16.h"
#include "Modules/Function/AXLF_CNT.h"
#include "PDIResponseStatus.h"
#include "../Hardware/AxioServiceExecuter.hpp"
#include <thread>

#define PROCESS_DATA_SIZE 512

using namespace std;

namespace PLCnext {


	class Axiobus {
		friend class AXLModule;
	public:

		// Select the process data interface.
		// To work in conjunction with PLCnext Engineer, PLCNEXT must be chosen.
		enum DataInterface
		{
			DIRECT,		// Access I/O hardware directly
			PLCNEXT		// Access I/O process data via PLCnext Runtime
		};

		// Determine how the process data is read/write.
		enum BusMode
		{
			CYCLIC,		// Creates thread that writes/reads process data on a cycle.
			EXPLICIT	// Reads bus and writes process data on command only.
		};

		// Structure that holds diagnostic information about the bus
		struct DiagnosticsInfo	
		{
			ushort status;		// Bus status flags
			ushort param1;		// Error code
			ushort param2;		// Error Location (slot number, 1 based index);
		};

		// Default constructor defaults to "PLCnext Mode - CYCLIC"
		Axiobus();	

		// DataInterface:
		//	PLCNEXT -> If using PLCNext Runtime
		//	DIRECT  -> If PLCnext Runtime is not running.

		// BusMode:
		//	CYCLIC -> Data reads/writes update on a cycle.
		//	EXPLICIT -> Data immediately reads/writes on command.
		//				Use if process data must not change mid-code execution.

		Axiobus(DataInterface, BusMode);
		bool initialize();
		const vector<AXLModule*>& getModules() const;
		bool scanModules();
		DiagnosticsInfo getDiagnosticsInfo();
		int saveConfiguration(string filePath);
		bool loadConfiguration(string filePath, string &error);
		uint getBaseModuleType(uint type);
		string getBaseModuleName(uint baseType);
		uint moduleTypeFromName(string name);
		uint getInitializationError();
		bool isInitialized();

		// Explicit Mode functions:
		bool readInputs();
		bool writeOutputs();


		// PLCnext Interface Functionality
		void enablePLCnextOutputs();
		void disablePLCnextOutputs();

		bool isOutputEnabled();
		~Axiobus();


		// Functions to interpret diagnostic flags:
		bool ioWarning();
		bool ioError();
		bool busError();
		bool controllerError();
		bool busOperational();

		// PLCnext Runtime Interop Parameters

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
		AXLModule* moduleFromType(ushort slot, uint type, uintptr_t &pdInOffset, uintptr_t &pdOutOffset, bool missing);
		double timeSpecToSeconds(struct timespec* ts);
		vector<AXLModule*> modules;
		uint m_initError;
		uint* m_pOutputEnabled;
		pair<uint, uint> getProcessDataSize(ushort type, char data[]);
		bool CreatePdiMutexes();
		AxioServiceExecuter* m_axioServiceExecuter;
		uint m_inDataSize;
		uint m_outDataSize;
		thread* m_cyclicThread;
		void cyclicExecution();
		bool m_doCyclicExecution;
		uintptr_t m_OutputPtr;
		T_AXM_DIAG_EX m_directDiag;

		BusMode m_busMode;
		DataInterface m_dataInterface;
	protected:
		PDIResponseStatus pdiRead(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, char* data);
		PDIResponseStatus pdiWrite(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, char* data, int length);

	};

}