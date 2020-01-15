/**
 * @file    main.cpp
 * @brief	FPGA-readBridge
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to read any bridge to FPGA
 * address for Intel Arria 10 SX
 */

#include <cstdio>
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>
using namespace std;


#pragma region Check user input 
bool checkIfInputIsVailed(string input, bool DecHex)
{
	if (input.length() < 1) return false;
	uint16_t i = 0;
	for (i = 0; i < input.length(); i++)
	{
		if (i != input.find_first_of(DecHex ? "0123456789" : "0123456789abcdef", i)) break;
	}

	if (i == input.length()) return true;

	return false;
}
#pragma endregion

int main(int argc, const char* argv[])
{
	// Read a Register ofthe light Wightweight or AXI HPS to FPGA Interface
	if (((argc >2) && (std::string(argv[1]) == "-lw")) || ((argc > 2) && (std::string(argv[1]) == "-hf")))
	{
		// read the selected Bridge Interface 
		bool lwBdrige(std::string(argv[1]) == "-lw");

		bool ConsloeOutput = true;

		string ValueString;

		// check if only decimal output is enabeled 
		if ((argc > 3) && (std::string(argv[3]) == "-b"))
			ConsloeOutput = false;

		/// Check the user inputs ///
		string AddresshexString = argv[2];
		uint32_t addressOffset = 0;

		// check if the address hex input is vailed
		bool InputVailed = true;
		if (checkIfInputIsVailed(AddresshexString, false))
		{
			istringstream buffer(AddresshexString);
			buffer >> hex >> addressOffset;

			// address inside range?
			if (lwBdrige)
			{
				// check the range of the lightwight Bridge Interface 
				if (addressOffset > 0x200000)
				{
					if (ConsloeOutput)
						cout << "	ERROR: selected address is outside of"\
						"the Lightwight Bridge range!" << endl;
					InputVailed = false;
				}
			}
			else
			{
				// check the range of the AXI HPS to FPGA Bridge Interface 
				if (addressOffset > 0x3c000000)
				{
					if (ConsloeOutput)
						cout << "	ERROR: selected address is outside of the HPS to "\
						"FPGA AXI Bridge range!" << endl;
					InputVailed = false;
				}
			}
		}
		else
		{
			// address input is not vailed
			if (ConsloeOutput)
				cout << "	ERROR: selected address input is no hex address!" << endl;
			InputVailed = false;
		}

		
		// only in case the input is vailed read the bridge
		if (InputVailed)
		{
			if (ConsloeOutput)
			{
				cout << "		-- Read registers on the FPGA part " << endl;
				cout << "	Bridge:      " << (lwBdrige ? "Lightwight HPS to FPGA" : "HPS to FPGA AXI") << endl;
				cout << "	Brige Base:  0x" << hex << (lwBdrige ? ALT_FPGA_BRIDGE_LWH2F_OFST : ALT_FPGA_BRIDGE_H2F128_OFST) << dec << endl;
				cout << "	your Offset: 0x" << hex << addressOffset << dec << endl;
				cout << "	Address:     0x" << hex << ((lwBdrige ? ALT_FPGA_BRIDGE_LWH2F_OFST : ALT_FPGA_BRIDGE_H2F128_OFST) + addressOffset) << dec << endl;
			}

			do
			{
				void* bridgeMap;
				int fd;

				// open memory driver 
				fd = open("/dev/mem", (O_RDWR | O_SYNC));

				// was opening okay
				if (fd < 0)
				{
					if (ConsloeOutput)
						cout << "ERROR: Failed to open memory driver!" << endl;
					else
						cout << 0;
					break;
				}

				// configure a virtual memory interface to the bridge
				bridgeMap = mmap(NULL, lwBdrige ? 0x200000 : 0x3c000000, PROT_READ, MAP_SHARED, fd, \
					(lwBdrige ? ALT_FPGA_BRIDGE_LWH2F_OFST : ALT_FPGA_BRIDGE_H2F128_OFST));

				// check if opening was sucsessful
				if (bridgeMap == MAP_FAILED)
				{
					if (ConsloeOutput)
						cout << "ERROR: Accesing the virtual memory failed!" << endl;
					else
						cout << 0;
					close(fd);
					break;
				}
				
				// access to Bridge is okay 
				// read the value to the address 
				volatile  uint32_t* readMap = (volatile  uint32_t*) \
					(bridgeMap + addressOffset);

				// readin the data 
				uint32_t value = *readMap;

				if (ConsloeOutput)
				{
					// print also the old value of the selected register
					cout << "	Value:	     " << value << " [0x" << hex << value << "]" << dec << endl;
					for (uint32_t i = 0; i < 32; i++)
					{
						cout << "	val[" << (i < 10 ? " " : "") <<i<<"] ="<< (value &(1 << i) ? 1 : 0) << endl;
					}
				}
				else
				{
					// output only the value as decimal 
					cout << value;
				}

				// Close the MAP 
				int res = munmap(bridgeMap, lwBdrige ? 0x200000 : 0x3c000000);

				if (res < 0)
				{
					if (ConsloeOutput)
						cout << "ERROR: Closing of shared memory failed!" << endl;
				}

				// close the driver port 
				close(fd);

				if (ConsloeOutput)
					cout << "Reading was successful" << endl;
				else
					cout << 1;

			} while (0);
		}
		else
		{
			// the user input is not okay 
			if (!ConsloeOutput)
				cout << 0;
		}

	}
	else
	{
		// help output 
		cout << "	Command to read a register on a HPS-FPGA Bridge" << endl;
		cout << "	FPGA-readBridge -lw [offset module address hex]" << endl;
		cout << "		read a register on the Lightweight HPS-FPGA Brige" << endl;
		cout << "		e.g.: FPGA-readBridge -lw 0a" << endl;
		cout << endl;
		cout << "	FPGA-readBridge -hf [offset module address hex]" << endl;
		cout << "		read a register on the HPS to FPGA AXI Bridge" << endl;
		cout << "		e.g.: FPGA-readBridge -lw 0a" << endl;
		cout << endl;
		cout << "		suffix: -b -> only decimal result output" << endl;
	}


	return 0;
}
