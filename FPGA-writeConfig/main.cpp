/**
 * @file    main.cpp
 * @brief   FPGA-writeConfig
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to write a new configuration to 
 * the FPGA fabric for Intel Arria 10 SX
 */

#include <cstdio>
#include "alt_fpga_manager.h"
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

#pragma region File Accsess 
bool is_file_exist(const char* fileName)
{
	ifstream infile(fileName);
	return infile.good();
}
#pragma endregion


bool writeFPGAconfig(const char* configFileAdress, bool withOutput)
{
	///////////ceck vailed FPGA status  /////////
	//
	//// read the MSEL-switch postion	
	//ALT_FPGA_CFG_MODE_t st = alt_fpga_cfg_mode_get();

	//if ((st != ALT_FPGA_CFG_MODE_PP16_SLOW_NOAES_NODC) && (st != ALT_FPGA_CFG_MODE_PP16_SLOW_AES_NODC))
	//{
	//	if (withOutput)
	//	{
	//		cout << "	EROR: The MSEL Switch is in the wrong postion!" << endl;
	//		cout << "	It is not posible to write the FPGA configuration" << endl;
	//		cout << "	Following MSEL selections are requiered" << endl;
	//		cout << "		MSEL=00100: PP16 with no AES and no Data compression" << endl;
	//		cout << "		MSEL=00101: PP16 with AES and no Data compression" << endl;
	//	}
	//	return false;
	//}

	///// check if the input file exist  
	//if (!is_file_exist(configFileAdress))
	//{
	//	if (withOutput)
	//		cout << "	ERROR: The selected config file does not exsist!" << endl;
	//	return false;
	//}

	///// Load the FPGA configuration file
	//if (withOutput)
	//	cout << "	Start writing the new FPGA configuration" << endl;

	//// Open rbf config and load them to an binary buffer into the Memory
	//FILE* f = fopen(configFileAdress, "rb");
	//fseek(f, 0, SEEK_END);
	//long fsize = ftell(f);
	//fseek(f, 0, SEEK_SET);

	//char* buf = new char[fsize + 1];
	//fread(buf, 1, fsize, f);
	//fclose(f);

	//// Start to write the FPGA Configuration
	//ALT_STATUS_CODE status = alt_fpga_configure(buf, fsize);

	//if (status != ALT_E_SUCCESS)
	//{
	//	if (withOutput)
	//		cout << "	ERROR: Writing the FPGA configuration failed" << endl;
	//	return false;
	//}
	//else
	//{
	//	if (withOutput)
	//	cout << "	Succses: The FPGA runs now with the new configuration" << endl;
	//	return true;
	//}

	return false;
}


int main(int argc, const char* argv[])
{

	cout << "Sory, not implemented...";

	/////////// init the Virtual Memory for I/O access /////////
	//__VIRTUALMEM_SPACE_INIT();

	///////////	 init the FPGA Manager	 /////////
	//alt_fpga_init();

	/////////// Take the right to controll the FPGA /////////
	//alt_fpga_control_enable();

	//ALT_FPGA_STATE_t stat = alt_fpga_state_get();

	//// change to a new selected FPGA configuration
	//if ((argc > 2) && (std::string(argv[1]) == "-f"))
	//{
	//	bool withOutput = !((argc > 3) && (std::string(argv[3]) == "-b"));
	//	bool res = writeFPGAconfig(argv[2], withOutput);

	//	if (!withOutput) cout << res ? 1 : 0;
	//}
	//// restore the the boot up configuration 
	//else if ((argc > 1) && (std::string(argv[1]) == "-r"))
	//{
	//	bool withOutput = !((argc > 2) && (std::string(argv[2]) == "-b"));
	//	bool res = writeFPGAconfig("/usr/rsyocto/running_bootloader_fpgaconfig.rbf", withOutput);
	//	if (!withOutput) cout << res ? 1 : 0;
	//}
	//else 
	//{
	//	cout << "	Command to change the FPGA fabric configuration" << endl;
	//	cout << "	for Cyclone V use following RBF (.rbf) Config File Setings" << endl;
	//	cout << "	MSEL=00100: PP16 with no AES and no Data compression" << endl;
	//	cout << "	MSEL=00101: PP16 with AES and no Data compression" << endl;
	//	cout << "	FPGA-writeConfig -f [config rbf file path] {-b [optinal]}" << endl;
	//	cout << "		change the FPGA config with a selected .rbf file" << endl;
	//	cout << "	FPGA-writeConfig -r {-b [optinal]}" << endl;
	//	cout << "		restore to the boot up FPGA configuration" << endl;
	//	cout << "		this Conf File is located: /usr/rsyocto/running_bootloader_fpgaconfig.rbf" << endl;
	//	cout << "		suffix: -b -> only decimal result output"<<endl;
	//	cout << "						Error:  0" << endl;
	//	cout << "						Succses:1" << endl;
	//}


	//// Give the right to controll the FPGA
	//alt_fpga_control_disable();

	//__VIRTUALMEM_SPACE_DEINIT();

	return 0;
}
