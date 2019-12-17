cmake_minimum_required(VERSION 2.4)
project(FPGA-resetFabric)
add_executable(FPGA-resetFabric
main.cpp
alt_fpga_manager.c
alt_fpga_manager.h
hps.h
hwlib.h
socal.h
alt_fpgamgr.h
alt_printf.h
alt_fpgamgrdata.h
)
