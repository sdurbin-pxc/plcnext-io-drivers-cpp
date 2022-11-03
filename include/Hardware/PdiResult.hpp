#pragma once

#include <stdint.h>

namespace PLCnext
{
	struct PdiResult
	{
		bool ServiceDone = false;
		uint16_t  ErrorCode = 0;
		uint16_t  AddInfo = 0;

		operator bool() const {
			return (ErrorCode == 0);
		}
	};
}