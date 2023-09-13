#include <stdint.h>

namespace PLCnext {

	class SignalLamps {

	public:

		enum Mode
		{
			BLINK = 1,
			ON = 2,
			OFF = 3
		};

		enum Color
		{
			GREEN = 1,
			YELLOW = 2,
			RED = 3
		};

		static bool SetSignalLampState(uint32_t lampNumber, Mode mode);
		static bool SetSignalLampState(uint32_t lampNumber, Mode mode, Color color);
		static bool SetSignalLampState(uint32_t lampNumber, Mode mode, Color color, uint16_t period);

	private:

		static bool writeToDriver(const char* data, const char* file);
	};
}