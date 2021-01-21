#pragma once

namespace PLCnext {

	struct PDIResponseStatus
	{
		bool success;
		bool timedOut;

		operator bool() const {
			return success;
		}
	};
}