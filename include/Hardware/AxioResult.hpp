#pragma once

#include <stdint.h>

namespace PLCnext
{
	struct AxioResult
	{
		bool ServiceDone = false;
		uint16_t  ErrorCode = 0;
		uint16_t  AddInfo = 0;
	};
}