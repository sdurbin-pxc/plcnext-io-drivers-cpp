
#¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯#
#	Set the directory of your AXC F 2152 SYSROOTS that correspond					#
#	to the firmware version on your controller.										#
#																					#
#	Note, these sysroots can be downloaded from the "Downloads" section of the		#
#	AXL F 2152 product page at https://www.phoenixcontact.com						#
#																					#
	set(AXC2152_SYSROOT "C:/2152sdk2021.9/sysroots")									#
#																					#
# __________________________________________________________________________________#


# The following are paths/flags specific to cross-compiling with the AXC 2152 toolchain:
# DO NOT CHANGE BELOW:

set(LIBARCH "arm" CACHE INTERNAL "" FORCE)

set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_SYSTEM_NAME "Linux" CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE RELEASE CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS "-mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9 -fomit-frame-pointer -pthread" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS "-mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9 -fomit-frame-pointer" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-g++.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_C_COMPILER "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-gcc.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER_RANLIB "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-gcc-ranlib.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER_AR "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-gcc-ar.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_AR "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-ar.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH "${AXC2152_SYSROOT}"  CACHE INTERNAL "" FORCE)
set(CMAKE_LINKER "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-ld.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_MAKE_PROGRAM "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/make.exe"  CACHE INTERNAL "" FORCE)
set(CMAKE_NM "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-nm.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_OBJCOPY "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-objcopy.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_OBJDUMP "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-objdump.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_RANLIB "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-ranlib.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_STRIP "${AXC2152_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/arm-pxc-linux-gnueabi/arm-pxc-linux-gnueabi-strip.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_SYSROOT "${AXC2152_SYSROOT}/cortexa9t2hf-neon-pxc-linux-gnueabi" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE "BOTH" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY "BOTH" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM "BOTH" CACHE INTERNAL "" FORCE)