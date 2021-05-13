cmake_minimum_required(VERSION 3.0.0)

project(AxcSimpleApp)

set(AXL_DRIVER_CLASSES "${CMAKE_CURRENT_SOURCE_DIR}/../../")

#if (LIBARCH STREQUAL "arm")
	include_directories(
#		"${AXC2152_SYSROOT}/cortexa9t2hf-neon-pxc-linux-gnueabi/usr/include/plcnext"
		"${AXL_DRIVER_CLASSES}/include"
	)
#else
 

#endif

link_directories(
	"${AXL_DRIVER_CLASSES}/lib/${LIBARCH}"
)

add_executable(
	axcSimpleApp.o main.cpp
)

target_link_libraries (axcSimpleApp.o Axiobus)

install (TARGETS axcSimpleApp.o DESTINATION bin)