#include <math.h>
#include "../../include/Axiobus/Axiobus.h"
#include "../../include/Hardware/SignalLamps.h"

using namespace PLCnext;

int main()
{
	Axiobus axio = Axiobus(Axiobus::DIRECT, Axiobus::EXPLICIT);  // Initialize direct/explicit interface.

	printf("Axio class instantiated.\n");
	// Check to see if the class successfully attached to the driver.
	if (!axio.isInitialized())
	{
		printf("Axiobus class initialization failed. Init Error: %d\n", axio.getInitializationError());
		return 1;
	}

	printf("\nScanning I/O modules...\n");

	// Get a vector of base class (AXLModule) pointers for the current installed I/O:

	vector<AXLModule*> modules = axio.getModules();

	// Check to make sure you have the right number of modules you are expecting.
	// In this example, we are expecting two:

	printf("Number of modules found = %i \n", modules.size());

	if (modules.size() != 1)
	{
		printf("Incorrect number of modules detected: %i\n", modules.size());
		return 2;
	}

	printf("Axioline bus initialized.\n\n");

	// Cast the base AXLModule classes into their derived classes:
	AXLF_DO8* do8 = dynamic_cast<AXLF_DO8*>(modules[0]);

	do8->setSubstituteBehavior(AXLDigitalOutputModule::SubstituteBehavior::ZeroOutputs);

	bool outputValue = false;

	do8->channel[0]->setValue(true);
	do8->channel[1]->setValue(true);
	do8->channel[4]->setValue(true);
	do8->channel[6]->setValue(true);
	do8->channel[7]->setValue(true);

	do8->channel[0]->setFailState();




}