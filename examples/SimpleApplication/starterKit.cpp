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
	// In this example, we are expecting six. Note: The SmartElement modules empty slots
	// count as a module.

	if (modules.size() != 6)
	{
		printf("Incorrect number of modules detected: %i\n", modules.size());
		return 2;
	}

	// Check to make sure we have the right modules in the right slots:
	// In this example:  [DI8/DO8, AI2/AO2]

	if (modules[0]->getType() != AXLF_MODULE_SE_DO16 ||
		modules[1]->getType() != AXLF_MODULE_SE_DI16 ||
		modules[3]->getType() != AXLF_MODULE_SE_AI4_U)
		
	{
		printf("Incorrect modules, or module order detected.\n");
		return 3;
	}

	printf("Axioline bus initialized.\n\n");

	// Get the device temperature (not processor temp):
	printf("Device temp: %f C\n\n", axio.deviceTemperature());

	// Cast the base AXLModule classes into their derived classes:

	AXLF_SE_DO16* do16 = dynamic_cast<AXLF_SE_DO16*>(modules[0]);
	AXLF_SE_DI16* di16 = dynamic_cast<AXLF_SE_DI16*>(modules[1]);
	AXLF_SE_AI4_U* ai4u = dynamic_cast<AXLF_SE_AI4_U*>(modules[3]);


	// Set digital output bus fail output behavior:
	if (!do16->setSubstituteBehavior(AXLDigitalOutputModule::SubstituteBehavior::HoldLast))
		printf("Trouble setting DO sub behavior.\n");

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

		// Trigger the reading of the Axioline bus. This must be done before reading values.
		axio.readInputs();

		// Get the value of the first channel of AI2/AO2's input:

		double aiVoltage = 0;
		uint err = ai4u->channel[0]->getValue(aiVoltage);

		// Check the return error:
		// Note, these errors are enumerated via AXLF_AI2AO2::AI2_Channel::Error

		if (err == AXLF_SE_AI4_U::AI4_Channel::NoError)
			printf("\b\rAI4 Channel 1: %f V\n", aiVoltage);
		else
			printf("\b\rAI4 Channel 1: Error %u\n", err);


		// Read the input channel 1 of the di16 module. If this is high,
		// it will stop the "alarm" light (do16 channel 1) from going high if
		// the ai4 voltage is over 5

		bool quietAlarm = di16->channel[0]->getValue();

		// If the AI4's channel 1 voltage input is over 5 Volts,
		// Make the do16 channel 1 output go high (alarm), unless alarm quieted (di16 ch1)

		if (aiVoltage > 5.0 && !quietAlarm)
			do16->channel[0]->setValue(true);
		else
			do16->channel[0]->setValue(false);

		// Note: You can set an indivual channel of the output via:
		// di8do8->do8->channel[x]->setValue(true/false);

		// Write set outputs to the actual bus:
		axio.writeOutputs();

		// Wait for 100ms
		usleep(100000);

	}

}