#include <mutex>
#include <string>
#include "axio_xfer.h"

using namespace std;

class AxioDrvAcc
{
public:
	AxioDrvAcc();
	~AxioDrvAcc();
	uint16_t GetNextUserId();
	int Open(const bool reset = true);
	int Close();
	int Send(uint16_t  userId, const uint8_t *buffer);
	int Receive(uint16_t userId, uint8_t *buffer, uint16_t bufSize);
	int32_t CheckMxiConfirmation(const uint8_t *sndBuf,const uint8_t *rcvBuf,const bool isBreakAtNegCnf,const bool isBreakAtNegDevCnf);
	int GetDiagRegs(T_AXM_DIAG_EX *poDiag);
	void SetDriverName(const string& name);
	int SetSysfailReg();
	int ClearSysfailReg();
	int ReadPD(uint8_t *pData, uint32_t len);
	int WritePD(uint8_t *pData, uint32_t len);

	enum ERR_CODES
	{
		NO_ERROR = 0,
		ERR_NEGATIV_CNF = 1,
		ERR_UNEXPECTED_IND = 2,
		ERR_UNEXPECTED_EVENT = 3
	};
private:

	static std::mutex idMutex;
	static uint16_t  lastUserId;
	static std::string drvPath;

	int drvFp;

};