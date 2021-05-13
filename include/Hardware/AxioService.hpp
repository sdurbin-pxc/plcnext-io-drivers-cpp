#pragma once

#include "ddi_macr.h"
#include "fibo_msg_codes.h"
#include <vector>
#include <stdint.h>
#include "AxioDeviceConfiguration.hpp"
#include "PdiResult.hpp"

#define PDI_REQ_HEADER_SIZE  12
#define PDI_CONF_HEADER_SIZE PDI_REQ_HEADER_SIZE+2

#define AXIO_SERVICE_BUFFER_SIZE 1024

//using namespace Arp::Io::Axioline::Services;
using namespace std;

class AxioService
{

public:
    AxioService(uint16_t cmdCode);
    AxioService(uint16_t cmdCode, uint16_t parameter1);
    AxioService(uint16_t cmdCode, uint16_t parameter1, uint16_t parameter2);
    AxioService(uint16_t cmdCode, uint16_t parameter1, uint16_t parameter2, uint16_t parameter3);
    AxioService(uint16_t cmdCode, uint16_t parameter1, uint16_t parameter2, uint16_t parameter3, uint16_t parameter4);
    virtual ~AxioService();

public:
    void InitService(uint16_t cmdCode);
    void SetCommandCode(uint16_t cmdCode);

	uint16_t GetReqMsgCode();
	uint16_t GetRespMsgCode();
	uint16_t GetParameterCount();
	uint16_t GetResult();
	uint16_t GetAddInfo();

    uint8_t* GetTxBuffer(void);
    uint8_t* GetRxBuffer(void);

public:
    void WriteTxBuffer(std::vector<uint16_t> inData);
    void ReadRxBuffer(std::vector<uint16_t>& outData);

    // Pdi-Service methods
public:
    PdiResult GetPdiReadResult(std::vector<uint8_t>& data);
    PdiResult GetPdiWriteResult();

    uint32_t SetData(const std::vector<uint8_t>& data);

    uint16_t GetIndex();
    uint8_t GetDataLen();
    std::vector<uint8_t> GetData();

    // Configuration service
public:
    std::vector<AxioDeviceConfiguration> GetDeviceConfiguration();
    void SetDeviceConfiguration(const std::vector<AxioDeviceConfiguration>& configuration);

protected:
    uint8_t txBuffer[AXIO_SERVICE_BUFFER_SIZE];
    uint8_t rxBuffer[AXIO_SERVICE_BUFFER_SIZE];

private:
    uint8_t resultPosition;
};

inline void AxioService::SetCommandCode(uint16_t cmdCode)
{
    IB_SetCmdCode(txBuffer, cmdCode);
}

inline uint16_t AxioService::GetReqMsgCode()
{
    return (uint16_t)IB_GetMsgCode(txBuffer);
}

inline uint16_t AxioService::GetRespMsgCode()
{
    return (uint16_t)IB_GetMsgCode(rxBuffer);
}

inline uint16_t AxioService::GetParameterCount()
{
    return (uint16_t)IB_GetParaCnt(rxBuffer);
}

inline uint16_t AxioService::GetResult()
{
    return (uint16_t)IB_GetParaN(rxBuffer, resultPosition);
}

inline uint16_t AxioService::GetAddInfo()
{
    return (uint16_t)IB_GetParaN(rxBuffer, resultPosition + 1);
}

inline uint8_t* AxioService::GetTxBuffer(void)
{
    return txBuffer;
}

inline uint8_t* AxioService::GetRxBuffer(void)
{
    return rxBuffer;
}
