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
#include <features.h>
#include <signal.h>
#include "AXLModule.h"
#include "Modules/AXLF_AI4_I.h"
#include "Modules/AXLF_AI4_U.h"
#include "Modules/AXLF_AI8.h"
#include "Modules/AXLF_AO4.h"
#include "Modules/AXLF_AO8.h"
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
#include "Modules/SmartElements/AXLF_SE_RTD.h"
#include "Modules/Function/AXLF_CNT.h"
#include "Modules/HART/AXLF_HART_AI8.h"
#include "Modules/HART/AXLF_HART_AO4.h"
#include "../Hardware/AxioServiceExecuter.hpp"
#include "../Hardware/PdiResult.hpp"
#include <thread>

#define PROCESS_DATA_SIZE 512

using namespace std;

namespace PLCnext {


	class Axiobus {
		friend class AXLModule;
	public:


		// Select the process data interface. Deprecated, PLCNEXT interface removed.
		// To work in conjunction with PLCnext Engineer, PLCNEXT must be chosen.
		enum DataInterface
		{
			DIRECT		// Access I/O hardware directly
		};

		// Determine how the process data is read/write.
		enum BusMode
		{
			EXPLICIT,	// Reads bus and writes process data on command only.
			DETACHED	// Explicit mode that does not keep driver open, for PDI calls only
		};

		// Structure that holds diagnostic information about the bus
		struct DiagnosticsInfo	
		{
			ushort status;		// Bus status flags
			ushort param1;		// Error code
			ushort param2;		// Error Location (slot number, 1 based index);
			bool driverError;	// Driver error
		};

		enum class DiagStatusFlags : std::uint16_t
		{
			IO_WARNING			= 0x0001,
			IO_ERROR			= 0x0002,
			BUS_ERROR			= 0x0004,
			CONTROLLER_ERROR	= 0x0008,
			RUNNING				= 0x0020,
			ACTIVE				= 0x0040,
			BUS_READY			= 0x0080,
			BUS_DIFFERENT		= 0x0100,
			SYS_FAIL			= 0x0200,
			FORCE_MODE			= 0x0400,
			SYNC_FAILED			= 0x0800,
			PARAM_REQUIRED		= 0x1000
		};

		Axiobus();
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
		bool setOutputsToFailState();

		// (Re)configure the bus I/O
		void configureBus();

		// Clear the sysfail register and start input/output
		void clearSysfail();


		// Explicit Mode functions:
		bool readInputs();
		bool writeOutputs();

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
		
		PdiResult pdiRead(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, std::vector<uint8_t>& data);
		PdiResult pdiWrite(ushort slot, ushort subSlot, ushort readIndex, ushort readSubIndex, const std::vector<uint8_t>& data);


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

		bool m_emptyBus;
		static Axiobus* m_instance;

		pthread_mutex_t* pdiMutex;
		uint8_t* userId;
		char* map;
		size_t mapSize;
		AXLModule* moduleFromType(ushort slot, uint type, uintptr_t &pdInOffset, uintptr_t &pdOutOffset, bool missing);
		double timeSpecToSeconds(struct timespec* ts);
		static vector<AXLModule*> modules;
		uint m_initError;
		uint* m_pOutputEnabled;
		pair<uint, uint> getProcessDataSize(ushort type, uint8_t data[]);
		AxioServiceExecuter* m_axioServiceExecuter;
		uint m_inDataSize;
		uint m_outDataSize;
		thread* m_cyclicThread;
		uintptr_t m_OutputPtr;
		bool CreatePdiMutexes();
		BusMode m_busMode;
		DataInterface m_dataInterface;

		static void configNotifyHandler(int sig, siginfo_t *si, void *ucontext);



	};

}