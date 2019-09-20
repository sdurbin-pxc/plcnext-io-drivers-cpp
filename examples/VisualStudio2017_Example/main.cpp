#include <iostream>
#include <AXC2152/AXC2152.h>
#include <vector>

using namespace std;
using namespace PLCnext;

int main()
{
	printf("\nInitializing Axioline bus system... ");

	// Initialize the main Axioline 2152 class.
	AXC2152 axio = AXC2152();

	// Check to see if the class successfully attached to the driver.
	if (!axio.isInitialized())
	{
		printf("AXC2152 class initialization failed.\n");
		return 1;
	}

	printf("\nScanning I/O modules...\n");

	// Get a vector of base class (AXLModule) pointers for the current installed I/O:

	vector<AXLModule*> modules = axio.getModules();

	printf("\nDetected: %d modules\n\n\n", modules.size());

	uint cnt = 0;
	for (;;)
	{
		printf("\b\rCounting up for Visual Studio debug demo: %u\n", cnt++);
		sleep(1);
	}
	return 0;
}