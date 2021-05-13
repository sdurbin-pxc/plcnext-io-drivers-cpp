#pragma once

namespace PLCnext {

	struct PDIResponseStatus
	{
		bool success;
		bool timedOut;
		uint32_t count = 0;
		operator bool() const {
			return success;
		}
	};
}