/**
 * @file    main.cpp
 * @brief	FPGA-readMSEL 
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to read the FPGA MSEL Switch with the
 * FPGA Manager for Intel Arria 10 SX
 */

#include <cstdio>
#include "alt_fpga_manager.h"
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;


// Enable the Diagnostic Mode
#define DEBUG_ALT_FPGA_MANAGER

volatile uint8_t MSELVal; 

#pragma region convert to string 
string std2str(ALT_FPGA_STATUS_e std)
{
	string tmp = "";
	MSELVal = 0;

	if (std & ALT_FPGA_STATUS_F2S_MSEL0)
	{
		tmp += "	Bit 0 : 1\n";
		MSELVal |= (1 << 0);
	}
	else
		tmp += "	Bit 0 : 0\n";

	if (std & ALT_FPGA_STATUS_F2S_MSEL1)
	{
		tmp += "	Bit 1 : 1\n";
		MSELVal |= (1 << 1);
	}
	else
		tmp += "	Bit 1 : 0\n";

	if (std & ALT_FPGA_STATUS_F2S_MSEL2)
	{
		tmp += "	Bit 2 : 1\n";
		MSELVal |= (1 << 2);
	}
	else
		tmp += "	Bit 2 : 0\n";

	return tmp;
}
#pragma endregion

int main(int argc, const char* argv[])
{
	///////// init the Virtual Memory for I/O access /////////
	__VIRTUALMEM_SPACE_INIT();

	/////////	 init the FPGA Manager	 /////////
	alt_fpga_init();

	///////// read the status of the FPGA		/////////
	ALT_FPGA_STATUS_e msel = (ALT_FPGA_STATUS_e)alt_fpga_status_get();

	if ((argc > 1) && (std::string(argv[1]) == "-h"))
	{
		cout << "	Command to read the selected FPGA configuration mode." << endl;
		cout << "	This is set with the MSEL-Switch."<< endl;
		cout << "	FPGA-readMSEL" << endl;
		cout << "		read MSEL with detailed output" << endl;
		cout << "	FPGA-readMSEL -d" << endl;
		cout << "		read MSEL as bit mask value" << endl;
	}
	else if ((argc > 1) && (std::string(argv[1]) == "-d"))
		// Print only the MSEL Value 
		cout << MSELVal;
	else
	{
		// Print the MSEL Value as detailed string 
		cout << "-- Read the MSEL-Switch position with the FPGA Manager of Intel Arria 10 SX  --" << endl;
		cout << "      MSEL-switch postion: " << endl << std2str(msel) << endl;
	}
	
	__VIRTUALMEM_SPACE_DEINIT();
    return 0;
}
