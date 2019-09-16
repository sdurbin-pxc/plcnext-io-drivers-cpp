# Overview

C++ driver classes to read and write I/O data from PLCnext Axioline modules. This library is currently only supports the Axioline 2152 controller (AXC F 2152, Part Number 2404267), and is currently offered as a static library (.a) with associated header files.

This method of accessing the I/O is not intended to be used in conjunction with PLCnext Engineer IEC 61131 development environment, but rather a means to utilize the I/O from a Linux/C++ application. Please visit the PLCnext Community tutorials at the following link if you are looking to integrate C++ code into an IEC 61131 application:  https://www.plcnext-community.net

This method of utilizing the controller and I/O requires experience in C++ and the Linux O/S.

# Repository Overview

**/examples** -> Contains examples of programs that utilize the library.  
**/include**  -> Contains the header files (.h) you will need to add to your project.  
**/lib**      -> Contains the static library file that will need to be referenced by your project.  
**/plcnext-io-driver-component**  -> Contains tar files that will need to be deployed to the controller before using the library.  

# Getting Started

Follow these steps to get your development environment set up:

## 1. Deploy the PLCnext I/O Driver Component to the device:

**1a.** Download your favorite SSH client (PuTTy, for example), and file transfer client (WinSCP, for example).

**1b.** Connect to the device using user: "admin", and the default password is on the front of the device.

**1c.** Check the device firmware version by running *cat /etc/plcnext/arpversion*.  Add a *20* in front of the response and this will be your firmware version. For instance, if the response is 19.3.0, your firmware version is 2019.3.0.

**1d.** Copy the corresponding package from the */plcnext-io-driver-component* folder to your device. For example, if your device has 2019.6, the latest available package would be *plcnext-iodriver-2019.3.tar.gz*.

**1e.** Using SSH, *cd* to the path you copied the driver component package to and run the following commands:  

**tar xvzf iodriver_v3.tar.gz --overwrite -C /** (Extract the driver component package)  
**/etc/init.d/plcnext restart** (Restart the PLCnext runtime)  
