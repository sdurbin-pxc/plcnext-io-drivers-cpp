# Overview

C++ driver classes to read and write I/O data from PLCnext Axioline modules. This library is currently only supports the Axioline 2152 controller (AXC F 2152, Part Number 2404267), and is currently offered as a static library (.a) with associated header files.

This method of accessing the I/O is not intended to be used in conjunction with PLCnext Engineer IEC 61131 development environment, but rather a means to utilize the I/O from a Linux/C++ application. Please visit the PLCnext Community tutorials at the following link if you are looking to integrate C++ code into an IEC 61131 application:  https://www.plcnext-community.net

This method of utilizing the controller and I/O requires experience in C++ and the Linux O/S.

# Getting Started

Follow these steps to get your development environment set up:

## 1. Deploy the PLCnext I/O Driver Component to the device:

