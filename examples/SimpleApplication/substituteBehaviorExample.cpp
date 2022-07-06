#include <math.h>
#include <Axiobus/Axiobus.h>

using namespace PLCnext;

int main()
{
	printf("\nInitializing Axioline bus system... ");

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

	if (modules.size() != 2)
	{
		printf("Incorrect number of modules detected: %i\n", modules.size());
		return 2;
	}

	// Check to make sure we have the right modules in the right slots:

	if (modules[1]->getType() != AXLF_MODULE_AI2AO2)
	{
		printf("Incorrect modules, or module order detected.\n");
		return 3;
	}

	printf("Axioline bus initialized.\n\n");

	// Cast the base AXLModule classes into their derived classes:

	AXLF_DI8DO8* di8do8 = dynamic_cast<AXLF_DI8DO8*>(modules[0]);
	AXLF_AI2AO2* ai2ao2 = dynamic_cast<AXLF_AI2AO2*>(modules[1]);

	ai2ao2->ao2->channel[0]->setOutputRange(AXLF_AI2AO2::AO2_Channel::OutputRange::V_0_P10);
	ai2ao2->ao2->channel[0]->setValue(5.5);
	ai2ao2->ao2->channel[0]->setSubstituteBehavior(PLCnext::AXLAnalogOutput::SubstituteBehavior::Substitute);
	ai2ao2->ao2->channel[0]->setSubstituteValue(8.8);

	axio.writeOutputs();

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

		// Read the loop current value
		axio.readInputs();

		//double aiLoopCurrent = 0;
		//uint err = ai8hart->aiChannel[0]->getValue(aiLoopCurrent);

		//uint32_t data = ai8hart->dataChannel[0]->getValue();

		// In this instance (temp sensor), the data object is a float.  So convert the UINT32 to float.
		//float val = *(float*)&data;

		//printf("\b\rCh.1 Loop Current: %f mA, HART Data Channel 1: %f V | ", aiLoopCurrent, val);

		//printf("Diag Status: %X, Param1: %X, Param2: %X\n", diag.status, diag.param1, diag.param2);
		//fflush(stdout);

		usleep(100000);

	}

}