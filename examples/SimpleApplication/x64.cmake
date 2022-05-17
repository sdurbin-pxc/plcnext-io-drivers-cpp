
#¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯#
#	Set the directory of your AXC F 3152 SYSROOTS that correspond					#
#	to the firmware version on your controller.										#
#																					#
#	Note, these sysroots can be downloaded from the "Downloads" section of the		#
#	AXL F 3152 product page at https://www.phoenixcontact.com						#
#																					#
	set(AXC_SYSROOT "C:/3152sdk2022/sysroots")								#
#																					#
# __________________________________________________________________________________#


# The following are paths/flags specific to cross-compiling with the AXC 3152 toolchain:
# DO NOT CHANGE BELOW:

set(LIBARCH "x64" CACHE INTERNAL "" FORCE)

set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_SYSTEM_NAME "Linux" CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE RELEASE CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS "-std=c++11 -m64 -march=nehalem -mtune=generic -mfpmath=sse -msse4.2 -fomit-frame-pointer -pthread" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS "-m64 -march=nehalem -mtune=generic -mfpmath=sse -msse4.2 -fomit-frame-pointer" CACHE INTERNAL "" FORCE)

set(CMAKE_CXX_COMPILER "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-g++.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_C_COMPILER "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-gcc.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER_RANLIB "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-x86_64-linux/x86_64-pxc-linux-gcc-ranlib.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER_AR "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-gcc-ar.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_AR "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-ar.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH "${AXC_SYSROOT}"  CACHE INTERNAL "" FORCE)
set(CMAKE_LINKER "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-ld.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_MAKE_PROGRAM "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/make64.exe"  CACHE INTERNAL "" FORCE)
set(CMAKE_NM "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-nm.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_OBJCOPY "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-objcopy.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_OBJDUMP "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-objdump.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_RANLIB "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-ranlib.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_STRIP "${AXC_SYSROOT}/x86_64-pokysdk-mingw32/usr/bin/x86_64-pxc-linux/x86_64-pxc-linux-strip.exe" CACHE INTERNAL "" FORCE)
set(CMAKE_SYSROOT "${AXC_SYSROOT}/corei7-64-pxc-linux" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE "BOTH" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY "BOTH" CACHE INTERNAL "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM "BOTH" CACHE INTERNAL "" FORCE)