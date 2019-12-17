/**
 * @file    main.cpp
 * @brief   FPGA-status
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to read the Status of the FPGA Fabric
 * with FPGA Manager for Intel Arria 10 SX
 */

#include <cstdio>
#include "alt_fpga_manager.h"
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

string std2str(ALT_FPGA_STATUS_e std)
{
	string tmp = "";
	if (std & ALT_FPGA_STATUS_F2S_CRC_ERROR)
		tmp+= "			FPGA POWER CRC  ERROR STATE\n"\
			  " 		CRC Error detected while in User mode \n";

	if (std & ALT_FPGA_STATUS_F2S_EARLY_USERMODE)
		tmp += "	FPGA EARLY USERMODE\n"\
			"		Early usermode signal from CSS. This can be used by software to\n"\
			"		determine status when HPS is configured the shared IOs via sending the\n"\
			"		POF to the CSS.\n";

	if (std & ALT_FPGA_STATUS_F2S_USERMODE)
		tmp += "	FPGA USER MODE STATE\n"\
			"		Usermode status. Asserted only when the FPGA has finally entered usermode.";

	if (std & ALT_FPGA_STATUS_F2S_INITDONE_OE)
		tmp += "	FPGA INITIALIZATION DONE STATE\n"\
			"		Driven enable of \b initdone signal.\n";

	if(std &  ALT_FPGA_STATUS_F2S_NSTATUS_PIN)
		tmp += "	FPGA NETSTATUS PIN\n"\
			"		Sampled pin value of \b nstatus signal. This can be overridden by an \n" \
			"		external device.\n";

	if (std & ALT_FPGA_STATUS_F2S_NSTATUS_OE)
		tmp += "	FPGA NETSTATUS SIGNAL\n"\
			"		Driven enable of \b nstatus signal.\n"; 

	if (std & ALT_FPGA_STATUS_F2S_CONDONE_PIN)
		tmp += "	FPGA CONDONE PIN\n"\
			"		Sampled pin value of \b condone signal. This can be overridden by an \n" \
			"		external devices.\n";

	if (std & ALT_FPGA_STATUS_F2S_CONDONE_OE)
		tmp += "FPGA CONDONE SIGNAL\n"\
			"	Driven enable of \b condone signal from CSS. \n";

	if (std & ALT_FPGA_STATUS_F2S_CVP_CONF_DONE)
		tmp += "	FPGA PCIe CONFIG DONE\n"\
			"		Configuration via PCIe (CVP) done indicator. \n";

	if(std & ALT_FPGA_STATUS_F2S_PR_READY)
		tmp += "	FPGA PARTIAL RECONF READY\n"\
			"		Partial Reconfiguration (PR) ready. \n";

	if (std & ALT_FPGA_STATUS_F2S_PR_DONE) 
		tmp += "	FPGA PARTIAL RECONF DONE\n"\
			"		Partial Reconfiguration (PR) done. \n";

	if (std & ALT_FPGA_STATUS_F2S_PR_ERROR)
		tmp += "	FPGA PARTIAL RECONF ERROR\n"\
			"		Partial Reconfiguration (PR) error. \n";
	
	if (std & ALT_FPGA_STATUS_F2S_NCONFIG_PIN)
		tmp += "	FPGA NCONFIG SIGNAL\n"\
			"		Sampled pin value of \b nconfig signal.\n";
	
	if (std & ALT_FPGA_STATUS_F2S_NCEO_OE)
		tmp += "	FPGA CSS BLOCK\n"\
			"		Chip select output driven from CSS block.\n";

	if (std & ALT_FPGA_STATUS_IMGCFG_FIFOEMPTY)
		tmp += "	FPGA FIFO EMPTY\n"\
			"		FIFO Empty status of the FPGA image configuration FIFO..\n";

	if (std & ALT_FPGA_STATUS_IMGCFG_FIFOFULL)
		tmp += "	FPGA FIFO FULL\n"\
			"		FIFO Empty full of the FPGA image configuration FIFO..\n";

	if (std & ALT_FPGA_STATUS_JTAGM)
		tmp += "	JTAG STATUS\n" \
			"		JTAG Master Session Status..\n";

	if (std & ALT_FPGA_STATUS_EMR)
		tmp += "	EMR STATUS\n" \
		    "		EMR valid bit.\n";

	return tmp;
}

int main(int argc, const char* argv[])
{
	///////// init the Virtual Memory for I/O access /////////
	__VIRTUALMEM_SPACE_INIT();

	///////// read the status of the FPGA		/////////
	ALT_FPGA_STATUS_e stat =(ALT_FPGA_STATUS_e) alt_fpga_status_get();

	if ((argc > 1) && (std::string(argv[1]) == "-h"))
	{
		cout << "	Command to read current Status mode of the FPGA fabric" << endl;
		cout << "	FPGA-status" << endl;
		cout << "		read the status with detailed output" << endl;
		cout << "	FPGA-status -d" << endl;
		cout << "    Output as 32-Bit Register value" << endl;
	}
	else if ((argc > 1) && (std::string(argv[1]) == "-d"))
		// Print only the Status Code 
		cout << stat;
	else
	{
		// Print the MSEL Value as detailed string 
		cout << "-- Read the current Status of the FPGA fabric  --" << endl;
		cout << "   Status of the FPGA: "  << std2str(stat) << endl;
	}

	__VIRTUALMEM_SPACE_DEINIT();
	return 0;
}
