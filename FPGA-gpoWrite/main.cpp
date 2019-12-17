/**
 * @file    main.cpp
 * @brief	FPGA-gpoWrite
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to write the general purpose outline
 * to the FPGA fabric for Intel Arria 10 SX
 */

#include <cstdio>
#include "alt_fpga_manager.h"
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <sstream>

using namespace std;

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


// Enable the Diagnostic Mode
#define DEBUG_ALT_FPGA_MANAGER

bool checkIfInputIsVailed(string input, bool DecHex)
{
	if ((input.length() < 1) || (input.length() > 8)) return false;
	uint16_t i = 0;
	for (i = 0; i < input.length(); i++)
	{
		if (i != input.find_first_of(DecHex ? "0123456789" :"0123456789abcdef", i)) break;
	}

	if (i == input.length()) return true;

	return false;
}


int main(int argc, const char* argv[])
{

	cout << "Sory, not implemented...";

	/////////// init the Virtual Memory for I/O access /////////
	//__VIRTUALMEM_SPACE_INIT();

	///////////	 init the FPGA Manager	 /////////
	//alt_fpga_init();

	//// Check if the FPGA is in the USER Mode ///
	//bool isFPGAuserMode = alt_fpga_status_get() & (ALT_FPGA_STATUS_F2S_USERMODE);


	//if (((argc > 2) && (std::string(argv[1]) == "-h")) || ((argc > 2) && (std::string(argv[1]) == "-d")))
	//{
	//	if (isFPGAuserMode)
	//	{
	//		bool DecHex = (std::string(argv[1]) == "-d");

	//		string hexString = argv[2];
	//		// check if the input is vailed 
	//		if(checkIfInputIsVailed(hexString, DecHex))
	//		{
	//			istringstream buffer(hexString);
	//			uint32_t Inputvalue;

	//			if (DecHex)
	//				buffer >> Inputvalue;
	//			else
	//				buffer >> hex >> Inputvalue;

	//			cout << "	Writing " << Inputvalue << " [0x" << hex << Inputvalue << dec;
	//			cout << "] as 32 Bit value via gpo register to the FPGA" << endl;
	//			alt_fpga_gpo_write(0xFFFFFFFF,Inputvalue);
	//		}
	//		else
	//		{
	//			cout << "ERROR: Input is not valid!" << endl;
	//			if(DecHex)
	//				cout << "Only numbers characters allowed!" << endl;
	//			else
	//				cout << "Only 8 HEX characters allowed!" << endl;
	//		}
	//	}
	//	else
	//	{
	//		cout << "ERROR: The FPGA Core is not in the User Mode!" << endl;
	//		cout << "		Writing to the FPGA fabric is not possible!" << endl;
	//	}
	//}
	//else if ((argc > 3) && (std::string(argv[1]) == "-b"))
	//{
	//	if (isFPGAuserMode)
	//	{
	//		/// readin the user input value

	//		string BitPosString		= argv[2];
	//		string BitValueString   = argv[3];

	//		bool BitPosvalid = false;
	//		bool BitValueValid = false;

	//		uint32_t Bitpos, Value2set;
	//		
	//		/// check if the inputs are vailed 
	//		
	//		if (checkIfInputIsVailed(BitPosString, true))
	//		{
	//			istringstream buffer(BitPosString);
	//			buffer >> Bitpos;
	//			cout << Bitpos<<endl;

	//			if (Bitpos < 32)
	//				BitPosvalid = true;
	//		}
	//		if (checkIfInputIsVailed(BitValueString, true))
	//		{
	//			istringstream buffer(BitValueString);
	//			buffer >> Value2set;
	//			cout << Value2set << endl;

	//			if (Value2set < 2)
	//				BitValueValid = true;
	//		}

	//		if (!BitPosvalid)
	//		{
	//			cout << "ERROR: The first Bit position value is not valid" << endl;
	//			cout << "		The value must be a number between 0 and 31" << endl;
	//		}

	//		if (!BitValueValid)
	//		{
	//			cout << "ERROR: The secound Bit value is not valid" << endl;
	//			cout << "		The value must be \"0\" or \"1\" "<< endl;
	//		}

	//		// Set or Reset the Bit 
	//		if (BitPosvalid && BitValueValid)
	//		{
	//			if      (Value2set == 0) cout << "Reset";
	//			else if (Value2set == 1) cout << "Set";
	//			
	//			cout << " the gpo Register Bit at position " << BitPosString << endl;
	//			alt_fpga_gpo_write( (1<< Bitpos), Value2set ? (1 << Bitpos): ~(1<< Bitpos));
	//		}
	//	}
	//	else
	//	{
	//		cout << "ERROR: The FPGA Core is not in the User Mode!" << endl;
	//		cout << "		Writing to the FPGA fabric is not possible!" << endl;
	//	}

	//}
	//else 
	//{
	//	cout << "	Command to write the general-purpose output signals (gpo) to " << endl;
	//	cout << "	the FPGA fabric " << endl;
	//	cout << "	The HPS get write a 32 Bit register to the FPGA" << endl;
	//	cout << "	FPGA-gpoWrite -h [uint]" << endl;
	//	cout << "		writing the whole 32 Bit gpo as HEX" << endl;
	//	cout << "		e.g.: FPGA-gpoWrite -h ffffffff" << endl;
	//	cout << "	FPGA-gpoWrite -d [uint]" << endl;
	//	cout << "		writing the whole 32 Bit gpo as DEC" << endl;
	//	cout << "		e.g.: FPGA-gpoWrite -d 12345" << endl;
	//	cout << "	FPGA-gpoWrite -b [bit pos] [value]" << endl;
	//	cout << "		writing a specific Bit position" << endl;
	//	cout << "		e.g.: FPGA-gpoWrite -b 16 1" << endl;
	//	cout << "			  (to set the Bit 16 of the gpo Regiser)" << endl;
	//}


	//__VIRTUALMEM_SPACE_DEINIT();
	return 0;
}
