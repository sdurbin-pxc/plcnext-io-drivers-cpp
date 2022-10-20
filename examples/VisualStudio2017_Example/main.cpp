#include <iostream>
#include <Axiobus/Axiobus.h>
#include <vector>

using namespace std;
using namespace PLCnext;

int main()
{
	printf("\nInitializing Axioline bus system... ");

	// Initialize the main Axioline 2152 class.
	Axiobus axio = Axiobus(Axiobus::DIRECT, Axiobus::EXPLICIT);

	// Check to see if the class successfully attached to the driver.
	if (!axio.isInitialized())
	{
		printf("Axiobus class initialization failed.\n");
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