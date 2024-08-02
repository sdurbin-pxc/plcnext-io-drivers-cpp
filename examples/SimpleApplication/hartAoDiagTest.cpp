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

	if (modules.size() != 2)
	{
		printf("Incorrect number of modules detected: %i\n", modules.size());
		return 2;
	}

	// Check to make sure we have the right modules in the right slots:
	// In this example:  [DI8/DO8, AI2/AO2]

	if (modules[0]->getType() != AXLF_MODULE_HART_AO4 || modules[1]->getType() != AXLF_MODULE_AI2AO2)
	{
		printf("Incorrect modules, or module order detected.\n");
		return 3;
	}

	printf("Axioline bus initialized.\n\n");

	// Get the device temperature (not processor temp):
	printf("Device temp: %f C\n\n", axio.deviceTemperature());

	// Cast the base AXLModule classes into their derived classes:

	AXLF_HART_AO4* hart = dynamic_cast<AXLF_HART_AO4*>(modules[0]);
	AXLF_AI2AO2* ai2ao2 = dynamic_cast<AXLF_AI2AO2*>(modules[1]);


	// Configure the AI2/AO2 module's first AI2 channel to measure from 0 to 10 Volts:

	if (!hart->aoChannel[0]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::mA_P4_P20))
		printf("error setting output range\n");
	if (!hart->aoChannel[1]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::INACTIVE))
		printf("error setting output range\n");
	if (!hart->aoChannel[2]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::INACTIVE))
		printf("error setting output range\n");
	if (!hart->aoChannel[3]->setOutputRange(AXLF_HART_AO4::AO_Channel::OutputRange::INACTIVE))
		printf("error setting output range\n");


	for (int i = 0; i < 8; i++)
		if (!hart->dataChannel[i]->assignChannel(AXLF_HART_AO4::Data_Channel::Channel_Select::Disabled))
			printf("error setting channel select\n");



	ai2ao2->ai2->channel[0]->setMeasuringRange(AXLF_AI2AO2::AI2_Channel::MeasuringRange::mA_P4_P20);
	ai2ao2->ai2->channel[1]->setMeasuringRange(AXLF_AI2AO2::AI2_Channel::MeasuringRange::INACTIVE);

	ai2ao2->ao2->channel[0]->setOutputRange(AXLF_AI2AO2::AO2_Channel::OutputRange::INACTIVE);
	ai2ao2->ao2->channel[1]->setOutputRange(AXLF_AI2AO2::AO2_Channel::OutputRange::INACTIVE);

	hart->aoChannel[0]->setValue(13.0);
	axio.writeOutputs();
	sleep(1);

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
		printf("Diag Status: %X, Param1: %X, Param2: %X\n", diag.status, diag.param1, diag.param2);
		fflush(stdout);

		// Get the value of the first channel of AI2/AO2's input:
		axio.readInputs();
		double ai2voltage = 0;
		uint err = ai2ao2->ai2->channel[0]->getValue(ai2voltage);

		// Check the return error:
		// Note, these errors are enumerated via AXLF_AI2AO2::AI2_Channel::Error

		if (err == AXLF_AI2AO2::AI2_Channel::NoError)
			printf("AI2 Channel 1: %f mA\n", ai2voltage);
		else
			printf("AI2 Channel 1: Error %u\n", err);


		// Get the value of the second channel of AI2/AO2's input:

		double hartao = 0;
		err = hart->aoChannel[0]->getValue(hartao);

		printf("\nHART: gv Error %u, | ", err);
		printf("\nHART: gv Value: %f, | ", hartao);

		AXLModule::Diagnostics diagz = hart->getDiagnostics();

		printf("\nHART DIAG:\n");
		printf("Channel: %u\n", diagz.channel);
		printf("ErrorCode: %u\n", diagz.errorCode);
		printf("Status: %u\n", diagz.status);
		printf("ErrorCode: %s\n", diagz.text.c_str());

		diagz = ai2ao2->getDiagnostics();

		printf("\nAI2AO2 DIAG:\n");
		printf("Channel: %u\n", diagz.channel);
		printf("ErrorCode: %u\n", diagz.errorCode);
		printf("Status: %u\n", diagz.status);
		printf("ErrorCode: %s\n", diagz.text.c_str());

		// Append the diagnostics information to console output:



		// Linear conversion of 0-10V to 4-20mA where:  0V => 4mA, 10V => 20mA.

		double ao2mA = 4.0 + (16.0 * (ai2voltage / 10.0));

		// Set the AO2 channel 1 output to the calculated value:

		err = ai2ao2->ao2->channel[0]->setValue(ao2mA);



		//axio.writeOutputs();
		getchar();

	}

}