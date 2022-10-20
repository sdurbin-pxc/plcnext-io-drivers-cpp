cmake_minimum_required(VERSION 3.0.0)

project(AxcSimpleApp)

set(CMAKE_BUILD_TYPE "Debug")

set(AXL_DRIVER_CLASSES "${CMAKE_CURRENT_SOURCE_DIR}/../../")

include_directories(
	"${AXL_DRIVER_CLASSES}/include"
)

link_directories(
	"${AXL_DRIVER_CLASSES}/lib/${LIBARCH}"
)

add_executable(
	${OUTPUT_NAME} main.cpp
)

target_link_libraries (${OUTPUT_NAME} Axiobus)

install (TARGETS ${OUTPUT_NAME} DESTINATION bin)