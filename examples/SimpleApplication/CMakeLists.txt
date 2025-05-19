cmake_minimum_required(VERSION 3.0.0)

project(AxcSimpleApp)

set(AXL_DRIVER_CLASSES "${CMAKE_CURRENT_SOURCE_DIR}/../../")

include_directories(
	"${AXL_DRIVER_CLASSES}/include"
)


link_directories(
	"${AXL_DRIVER_CLASSES}/lib/shared/${LIBARCH}"
) 

add_executable(
	axcSimpleApp.o main.cpp
)

add_library(axiobus SHARED IMPORTED)
set_property(TARGET axiobus PROPERTY IMPORTED_LOCATION ${AXL_DRIVER_CLASSES}/lib/shared/${LIBARCH}/libAxiobus.so.7)

target_link_libraries (axcSimpleApp.o axiobus)

install (TARGETS axcSimpleApp.o DESTINATION bin)