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

	if (modules[0]->getType() != AXLF_MODULE_DI8DO8 || modules[1]->getType() != AXLF_MODULE_AI2AO2)
	{
		printf("Incorrect modules, or module order detected.\n");
		return 3;
	}

	printf("Axioline bus initialized.\n\n");

	// Get the device temperature (not processor temp):
	printf("Device temp: %f C\n\n", axio.deviceTemperature());

	// Cast the base AXLModule classes into their derived classes:

	AXLF_DI8DO8* di8do8 = dynamic_cast<AXLF_DI8DO8*>(modules[0]);
	AXLF_AI2AO2* ai2ao2 = dynamic_cast<AXLF_AI2AO2*>(modules[1]);


	// Configure the AI2/AO2 module's first AI2 channel to measure from 0 to 10 Volts:

	if (!ai2ao2->ai2->channel[0]->setMeasuringRange(AXLF_AI2AO2::AI2_Channel::MeasuringRange::V_0_P10))
	{
		printf("Configuring AI2/AO2's first input channel's measuring range failed.\n");
		return 4;
	}

	// Configure the AI2/AO2 module's first output channel to output from 4 to 20 mA:

	if (!ai2ao2->ao2->channel[0]->setOutputRange(AXLF_AI2AO2::AO2_Channel::OutputRange::mA_P4_P20))
	{
		printf("Configuring AI2/AO2's first output channel's output range failed.\n");
		return 5;
	}

	if (!ai2ao2->ao2->channel[1]->setOutputRange(AXLF_AI2AO2::AO2_Channel::OutputRange::V_N10_P10))
	{
		printf("Configuring AI2/AO2's first output channel's output range failed.\n");
		return 5;
	}

	// Configure the AI2/AO2 module's second AI2 channel to measure from 4 to 20 mA:

	if (!ai2ao2->ai2->channel[1]->setMeasuringRange(AXLF_AI2AO2::AI2_Channel::MeasuringRange::mA_P4_P20))
	{
		printf("Configuring AI2/AO2's second input channel's measuring range failed.\n");
		return 6;
	}

	// Set digital output bus fail output behavior:
	if (!di8do8->setSubstituteBehavior(AXLDigitalOutputModule::SubstituteBehavior::HoldLast))
		printf("Trouble setting DO sub behavior.\n");


	//axio.saveConfiguration("testConfig.json");

	printf("\nEntering program loop. PRESS CTRL+C to end\n\n\n");
	// Loop forever
	// Loop forever
	for (;;)
	{
		// Get the bus diagnostics information

		// Check if we are in the desired controller state (Bus ready, bus active, and controller in run state)
		// The diag.status, diag.param1 and diag.param2 will give detailed information of the system and I/O state.
		// Refer to the "UM EN AXL F SYS DIAG" document that is provided at the AXC F 2152 product page downloads section
		// for more information

		//printf("Diag: %x, %x, %x\n", diag.status, diag.param1, diag.param2);
		//if ((diag.status & 0xE0) != 0xE0)
		//{
		//	printf("Bus not in active/run state. Check diagnostic parameters.\n");
		//	printf("Diag Status: %X, Param1: %X, Param2: %X\n", diag.status, diag.param1, diag.param2);
		//	fflush(stdout);
		//	return 6;
		//}
		//axio.readInputs();

		// Get the value of the first channel of AI2/AO2's input:


		//////
		/*
		uint32_t _pv, _sv, _tv, _qv;
		float pv, sv, tv, qv;

		_pv = hart->dataChannel[0]->getValue();
		_sv = hart->dataChannel[1]->getValue();
		_tv = hart->dataChannel[2]->getValue();
		_qv = hart->dataChannel[3]->getValue();

		pv = *(float*)&_pv;
		sv = *(float*)&_sv;
		tv = *(float*)&_tv;
		qv = *(float*)&_qv;


		printf("pv: %f, sv: %f, tv: %f, qv: %f\n", pv, sv, tv, qv);
		*/
		printf("set output: ");

		double setpoint = -1.0;
		cin >> setpoint;

		if (setpoint >= 4.0 && setpoint <= 20)
			ai2ao2->ao2->channel[0]->setValue(setpoint);

		axio.writeOutputs();
		sleep(2);
		axio.readInputs();

		//double ai2voltage = 0;
		//uint err = ai2ao2->ai2->channel[0]->getValue(ai2voltage);

		// Check the return error:
		// Note, these errors are enumerated via AXLF_AI2AO2::AI2_Channel::Error

		//cout << "\b\r";
		//if (err == AXLF_AI2AO2::AI2_Channel::NoError)
			//printf("Data: %f F, | ", val);
		//else
		//	printf("AI2 Channel 1: Error %u, | ", err);


		// Get the value of the second channel of AI2/AO2's input:

		/*
		double ai2mA = 0;
		err = ai2ao2->ai2->channel[1]->getValue(ai2mA);
		*/
		// Check the return error:
		// Note, these errors are enumerated via AXLF_AI2AO2::AI2_Channel::Error

		/*
		if (err == AXLF_AI2AO2::AI2_Channel::NoError)
			printf("AI2 Channel 2: %f mA, | ", ai2mA);
		else
			printf("AI2 Channel 2: Error %u, | ", err);
		*/
		// Append the diagnostics information to console output:
		Axiobus::DiagnosticsInfo diag = axio.getDiagnosticsInfo();

		printf("Diag Status: %X, Param1: %X, Param2: %X\n", diag.status, diag.param1, diag.param2);
		fflush(stdout);

		// Linear conversion of 0-10V to 4-20mA where:  0V => 4mA, 10V => 20mA.



		//usleep(100000);

	}

}