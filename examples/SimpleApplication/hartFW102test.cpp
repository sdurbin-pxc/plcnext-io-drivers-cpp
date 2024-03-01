#include <math.h>
#include "../../include/Axiobus/Axiobus.h"
#include "../../include/Hardware/SignalLamps.h"

using namespace PLCnext;

int main()
{
	printf("\nInitializing Axioline bus system... \n");

	// Initialize the main Axioline bus class.

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

	if (modules.size() != 1)
	{
		printf("Incorrect number of modules detected: %i\n", modules.size());
		return 2;
	}

	// Check to make sure we have the right modules in the right slots:
	// In this example:  [DI8/DO8, AI2/AO2]

	if (modules[0]->getType() != AXLF_MODULE_HART_AO4)
	{
		printf("Incorrect modules, or module order detected.\n");
		return 3;
	}

	printf("Axioline bus initialized.\n\n");

	// Get the device temperature (not processor temp):
	printf("Device temp: %f C\n\n", axio.deviceTemperature());

	// Cast the base AXLModule classes into their derived classes:

	AXLF_HART_AO4* ao4 = dynamic_cast<AXLF_HART_AO4*>(modules[0]);


	// Configure the AI2/AO2 module's first AI2 channel to measure from 0 to 10 Volts:

	if (!ao4->aoChannel[0]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::mA_P4_P20))
	{
		printf("Configuring AI2/AO2's first input channel's measuring range failed.\n");
		return 4;
	}

	if (!ao4->aoChannel[1]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::INACTIVE))
	{
		printf("Configuring AI2/AO2's first input channel's measuring range failed.\n");
		return 4;
	}

	if (!ao4->aoChannel[2]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::mA_P4_P20))
	{
		printf("Configuring AI2/AO2's first input channel's measuring range failed.\n");
		return 4;
	}

	if (!ao4->aoChannel[3]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::INACTIVE))
	{
		printf("Configuring AI2/AO2's first input channel's measuring range failed.\n");
		return 4;
	}


	ao4->aoChannel[0]->setValue(9.0);
	//ao4->aoChannel[1]->setValue(11.0);
	ao4->aoChannel[2]->setValue(13.0);
	//ao4->aoChannel[3]->setValue(15.0);
	axio.writeOutputs();

	//axio.saveConfiguration("testConfig.json");

	printf("\nEntering program loop. PRESS CTRL+C to end\n\n\n");
	// Loop forever
	for (;;)
	{
		// Get the bus diagnostics information
		Axiobus::DiagnosticsInfo diag = axio.getDiagnosticsInfo();

		// Check if we are in the desired controller state (Bus ready, bus active, and controller in run state)
		// The diag.status, diag.param1 and diag.param2 will give detailed information of the system and I/O state.
		// Refer to the "UM EN AXL F SYS DIAG" document that is provided at the AXC F 2152 product page downloads section
		// for more information

		//printf("Diag: %x, %x, %x\n", diag.status, diag.param1, diag.param2);
		if ((diag.status & 0xE0) != 0xE0)
		{
			printf("Bus not in active/run state. Check diagnostic parameters.\n");
			return 6;
		}

		// Get the value of the first channel of AI2/AO2's input:
		axio.readInputs();

		double ret = -1.0;

		for (int i=0; i < 4; i++)
		{
			uint resp = ao4->aoChannel[i]->getValue(ret);
			cout << i << ": resp code:  " << resp << endl;
			cout << i << ": resp value: " << ret << endl;
		}
		// Wait for 100ms

		getchar();
		//axio.writeOutputs();
		//usleep(100000);

	}

}