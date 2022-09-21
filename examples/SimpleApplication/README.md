
# Cross-compiling from Windows to target device (AXC F 2152/3152)

## Step 1:  Install the latest Cmake:

Download Cmake for Windows from: https://cmake.org/download/\
\
Verify that Cmake is installed by opening a command line and entering "cmake --version".\

## Step 2:  Download the SDK/Sysroots:

Download the SDK for Windows from the product's Software Downloads page:  Product>Downloads>Software.
The zip file should start with "SDK_for_Windows_".  Open the zip and extrat the .tar.xz file to any directory.
Using a tool similar to 7-zip, extract the contents of the embedded .tar file into a directory.
The extracted contents should contain a folder named "sysroots".
The path to this directory will be referred to as {sysrootsPath} in this walkthrough.

## Step 3: Set path in Cmake files:

Open x64.cmake (for 3152) and/or arm.cmake (for 2152) located in the SimpleApplication project directory.

Change the sysroots path as follows:

	set(AXC_SYSROOT "{sysrootsPath}")

For example, if your syroots path is C:\sysroots, it should show as:  set(AXC_SYSROOT "C:\sysroots").
Be sure to save the file.

## Step 4: Add Windows Environment Variables PATH entry for make.exe:

Add an entry for the following path in your System Environment Variables:

	{sysrootsPath}\x86_64-pokysdk-mingw32\usr\bin

It should look something like the following:  "C:\sysroots\x86_64-pokysdk-mingw32\usr\bin"

Check to see if this is working by opening a new command line and typing "make -v" from any directory.

## Step 5: Generate the Cmake build files:

Open a command line and change directories (cd) to the appropriate build directory pre-created in this project.

	Example:  cd c:\AxioDrivers\examples\SimpleApplication\build
	Note:  c:\AxioDrivers is likely not your path you cloned the project to.

For AXC F 3152, run the command:  cmake ../ -C ../x64.cmake
For AXC F 2152, run the command:  cmake ../ -C ../arm.cmake

Cmake should generate the appropriate makefiles for the project.
A success should end with "Build files have been written to...""

## Step 6: Build the project:

In the same directory, run the "make" command in the console.
After the project builds, you should see: [100%] Built target axcSimpleApp.o
axcSimpleApp.o should now be located in the build directory.

## Step 7:  Move the binary to the device, and execute:

Using WinSCP or another file transfer program, move the axcSimpleApp.o file to the device.
The /tmp folder is preferred for testing, as it is wiped on every reboot.
Change the permission of the axcSimpleApp.o to executable.
Using PuTTy or similar SSH interface, log into the device (using user: "admin", and default password on the front of the device).
Execute the file by changing directories to the /tmp folder, and run the application with ./axcSimpleApp.o

# About the Simple Application:

This is a well commented application example that uses the same bus configuration as the AXC F 2152 StarterKit (DI8/1 DO8/1, AI2 AO2).  

It performs the following actions:

* Initializes I/O driver communication.
* Checks to make sure there is two modules on the bus.
* Checks to make sure the DI8/DO8 module is in the first slot, and the AI2/AO2 is in the second slot.
* Sets the AI2 Channel 1 input mode to 0-10V.
* Sets the AO2 Channel 1 output mode to 4-20mA.
* Enables process outputs

And loops the following actions:

* Reads the current bus diagnostics. Exit if not in run state.
* Reads the AI2 Channel 1 input.
* Checks for error.
* Converts the AI2 Channel 1 input value (0-10V) into 4-20mA signal.
* Puts that calculated value to the AO2 Channel 1 output.
* Reads the DI8 input bits.
* If the AI2 Channel 1 input is over 5V, sets the DO8 to the DI8 input's inverse, otherwise reflect the DI8 onto the DO8 outputs.

The console should be continuously updated with the AI2 Channel 1 value or error, and the current system bus diagnostics.
