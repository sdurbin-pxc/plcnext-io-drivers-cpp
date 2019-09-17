
This is a well commented application example that uses the same bus configuration as the AXC F 2152 StarterKit (DI8/1 DO8/1, AI2 AO2).  

It performs the following actions:

* Initializes I/O driver communication.
* Checks to make sure there is two modules on the bus.
* Checks to make sure the DI8/DO8 module is in the first slot, and the AI2/AO2 is in the second slot.
* Sets the AI2 Channel 1 input mode to 0-10V.
* Sets the AO2 Channel 1 output mode to 4-20mA.

And loops the following actions:

* Reads the AI2 Channel 1 input.
* Checks for error.
* Converts the AI2 Channel 1 input value (0-10V) into 4-20mA signal.
* Puts that calculated value to the AO2 Channel 1 output.
* Reads the DI8 input bits.
* If the AI2 Channel 1 input is over 5V, sets the DO8 to the DI8 input's inverse, otherwise reflect the DI8 onto the DO8 outputs.
