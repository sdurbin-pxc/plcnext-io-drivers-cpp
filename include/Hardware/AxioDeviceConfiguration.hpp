#pragma once

#include <stdint.h>

namespace PLCnext
{
	struct AxioDeviceConfiguration
	{

		uint32_t Type = 0;
		uint32_t Id = 0;
		uint16_t Length = 0;

	};
}