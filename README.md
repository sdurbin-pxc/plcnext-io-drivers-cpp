<p align="right"><a href="https://github.com/sdurbin-pxc/plcnext-io-drivers-cpp/wiki">Go to Wiki for code documentation</a></p>  

# Overview

This repository contains C++ driver classes to read and write I/O data from PLCnext Axioline modules. This library currently only supports the Axioline 2152 controller ([AXC F 2152, Part Number 2404267](https://www.phoenixcontact.com/online/portal/us/?uri=pxc-oc-itemdetail:pid=2404267)), and is currently offered as a static library (.a) with associated header files.

This method of accessing the I/O is not intended to be used in conjunction with PLCnext Engineer IEC 61131 development environment, but rather a means to utilize the I/O from a Linux/C++ application. Please visit the PLCnext Community tutorials at the following link if you are looking to integrate C++ code into an IEC 61131 application:  https://www.plcnext-community.net

This method of utilizing the controller and I/O requires experience in C++ and the Linux OS.

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

**1e.** Using SSH, *cd* to the path you copied the driver component package to and run the following commands. Note: change *{fwVersion}* to the firmware version of the driver you downloaded from this repository.

------> **tar xvzf plcnext-iodriver-*{fwVersion}*.tar.gz --overwrite -C /** (Extract the driver component package)  
------> **/etc/init.d/plcnext restart** (Restart the PLCnext runtime)  

## 2. Download the SDK/SYSROOTS for cross-compiling from Windows:

**2a.** Visit the www.phoenixcontact.com webpage and search for the AXC F 2152 device. On the products page, click the "Downloads" tab and scroll down to find your corresponding Windows SDK.  If there is not an SDK that corresponds to your firmware version, you will need to update the firmware on your device before continuing.

**2b.** Extract the SDK to any directory on the local drive. Note that the *sysroots* folder in this directory is your "AXC 2152 SYSROOT" folder.

## 3. Compiling an example program from the repository:

With the SDK, you are not limited to one development environment. You may choose to integrate the needed compilation flags and sysroots path into many different environments (Visual Studio, VSCode, Eclipse, etc).  In this README, we will go over a simple Cmake compilation. In the future, examples will be created to show how to compile directly from Visual Studio and other IDEs.

## 3a. CMAKE

The following steps are to show how to compile the example project "SimpleApplication" located in the examples directory of this repository.  The CMakeLists.txt is the main configuration file for building the project via CMake and has already been created for you. You can use this file as a base to further develop your custom application using CMake.

**3a-1.** Download and install the latest version of CMake from https://cmake.org/download  

**3a-2.** In your local copy of the repository, navigate to and open the *examples/SimpleApplication/PreLoad.cmake* file. This file contains all of the compiler paths and flags that CMake needs to generate a Makefile for the application.  Note that the actual paths and flags can be referenced to create a development environment in any IDE.

**3a-3.** Change line 4 to *set(AXC2152_SYSROOT "**{SYSROOT_FOLDER**")*, where *{SYSROOT_FOLDER}* is the location of the sysroots folder that was noted in *2b*.  For example:  set(AXC2152_SYSROOT "c:\Path\To\SDK\sysroots").

**3a-4.** For a simple compilation without an IDE, you can open the command line editor in Windows, change directory (cd) to your *examples/SimpleApplication/build* folder, and run Cmake as follows:

-----> cd c:\Path\To\examples\SimpleApplication\build  
-----> cmake ../  

Note that the *cmake ../* command tells cmake to generate build files (Makefile in this case) in the current directory (build), and to use one directory up (../) as the source directory that also contains the CMakeLists.txt  

**3a-5.** Compile the program based on the Cmake-generated Makefile by running the following command:  

-----> make  

The program should compile, and in the case of the SimpleApplication example, the axcSimpleApp binary will be located in the build folder.  

**3a-6.**  Move the executable to the device, set it to executable (chmod +x), and execute the binary.  

# Visual Studio - Open Folder

Check the [Visual Studio 2017 Example](https://github.com/sdurbin-pxc/plcnext-io-drivers-cpp/blob/master/examples/VisualStudio2017_Example). It has the configuration (json) files needed to compile, deploy, and debug in an "Open Folder" project. It has its own README that explains the files.  

# C++ Class Driver Documentation

Reading through the sample application code and comments may be enough to get you going using the drivers. All of the I/O module classes follow a similar use pattern.  To supplement this, more robust documentation will be available at the wiki page associated with this repository: 

### [Class Driver Documentation Wiki](https://github.com/sdurbin-pxc/plcnext-io-drivers-cpp/wiki)
