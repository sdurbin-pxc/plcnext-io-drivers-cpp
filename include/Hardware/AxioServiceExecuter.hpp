#pragma once

//#include "Arp/System/Core/Arp.h"
//#include "Arp/System/Commons/Logging.h"

#include "AxioService.hpp"
#include "AxioDrvAcc.h"
#include "AxioResult.hpp"
#include "AxioDeviceConfiguration.hpp"
#include "PdiResult.hpp"
#include "PdiParam.hpp"

//#include "Arp/Io/Axioline/Services/IAcyclicCommunicationService.hpp"
//#include "Arp/Io/Axioline/Services/IAxioMasterService.hpp"

#include <vector>
#include <map>


//using namespace Arp::Io::Axioline::Services;

class AxioServiceExecuter
{
public:
    AxioServiceExecuter();
    ~AxioServiceExecuter();

public:
    AxioResult ProcessAxioService(AxioService& service, bool getConfirmationResult = true);
public:
    uint16_t AxioControl(const std::vector<uint16_t>& inData, std::vector<uint16_t>& outData);
    AxioResult CreateConfiguration(uint16_t frameReference);
    AxioResult ReadConfiguration(uint16_t frameReference, std::vector<AxioDeviceConfiguration>& configuration);
    AxioResult WriteConfiguration(uint16_t frameReference, const std::vector<AxioDeviceConfiguration>& configuration);
    AxioResult ActivateConfiguration(uint16_t frameReference);
    AxioResult DeactivateConfiguration(uint16_t frameReference);
    AxioResult ResetMaster();
    PdiResult PdiRead(const PdiParam& pdiParam, std::vector<uint8_t>& data);
    PdiResult PdiWrite(const PdiParam& pdiParam, const std::vector<uint8_t>& data);
	int ReadPD(uint8_t *pData, uint32_t len);
	int WritePD(uint8_t *pData, uint32_t len);
	int GetDiagRegs(T_AXM_DIAG_EX *poDiag);
	int ClearSysfailReg();
    /* auxiliary methods */
private:
    uint16_t Builduint16Value(uint8_t lowByte, uint8_t highByte);
    bool IsPdiRequest(AxioService service);

protected:
    AxioDrvAcc axioMxi;
};
