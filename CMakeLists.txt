cmake_minimum_required(VERSION 3.10)
project(rstools)

set(CMAKE_CXX_STANDARD 17)

include_directories("${CMAKE_SOURCE_DIR}/FPGA-gpiRead")
include_directories("${CMAKE_SOURCE_DIR}/FPGA-readMSEL")      
include_directories("${CMAKE_SOURCE_DIR}/FPGA-gpoWrite")
include_directories("${CMAKE_SOURCE_DIR}/FPGA-readBridge")    
include_directories("${CMAKE_SOURCE_DIR}/FPGA-resetFabric")
include_directories("${CMAKE_SOURCE_DIR}/FPGA-status")    
include_directories("${CMAKE_SOURCE_DIR}/FPGA-writeBridge")
include_directories("${CMAKE_SOURCE_DIR}/FPGA-writeConfig")    
