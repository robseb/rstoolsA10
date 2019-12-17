/**
 * @file    main.cpp
 * @brief	FPGA-writeBridge
 * @author  Robin Sebastian (https://github.com/robseb)
 * @mainpage
 * rstools application to write to any HPS-FPGA Bridge 
 * address
 */

#include <cstdio>
#include "hps.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sstream>
using namespace std;

#define DEC_INPUT 1
#define HEX_INPUT 0
#define BIN_INPUT 2

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
	// Read to the Light Wightweight or AXI HPS to FPGA Interface
	if (((argc > 3) && (std::string(argv[1]) == "-lw")) || ((argc > 3) && (std::string(argv[1]) == "-hf")))
	{
		// read the selected Bridge Interface 
		bool lwBdrige  (std::string(argv[1]) == "-lw");

		/// check the value input type (Dec or Hex) ///
		// 1: DEC Value input | 0: HEX Dec Input | 2: Binary Bit Set/Reset 
		int DecHexBin = DEC_INPUT;
		bool ConsloeOutput = true;

		// check the Value input type (dec,hex,bin)
		if ((argc >= 4) && (std::string(argv[3]) == "-h"))
			DecHexBin = HEX_INPUT;

		if ((argc > 4) && (std::string(argv[3]) == "-b"))
			DecHexBin = BIN_INPUT;

		string ValueString;

		switch (DecHexBin)
		{
		case DEC_INPUT:
			if ((argc > 4)&& (std::string(argv[4]) == "-b"))
				ConsloeOutput = false;

			ValueString = argv[3];
			break;
		case HEX_INPUT:
			if ((argc > 5) && (std::string(argv[5]) == "-b"))
				ConsloeOutput = false;
			ValueString = argv[4];
			break;
		case BIN_INPUT:
			if ((argc > 6) && (std::string(argv[6]) == "-b"))
				ConsloeOutput = false;
			break;
		default:
			break;
		}

		/// Check the user inputs ///

		string AddresshexString = argv[2];
		uint32_t addressOffset = 0;
		

		uint32_t ValueInput = 0;
		uint64_t ValueInputTemp = ValueInput;

		uint32_t BitPosValue = 0;
		uint32_t SetResetBit = 0;

		// check if the address hex input is vailed
		bool InputVailed = true;
		if (checkIfInputIsVailed(AddresshexString, false))
		{
			istringstream buffer(AddresshexString);
			buffer >> hex >> addressOffset;

			// address inside range?
			if(lwBdrige)
			{
				// check the range of the lightwight Bridge Interface 
				if (addressOffset > 2097150)
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
				if (addressOffset > 8143)
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

		// only for binary mode: check if the Set or Reset input is vailed //
		if (DecHexBin == BIN_INPUT)
		{
			// read and check the Pos input value
			string SetInputString = argv[5];
			string BitPosString = argv[4];

			// check if the Bit pos value input is okay
			if (checkIfInputIsVailed(BitPosString, true))
			{
				istringstream buffer(BitPosString);
				buffer >> BitPosValue;

				if (BitPosValue < 32)
					InputVailed = true;
			}

			// read and check the Set or Reset input
			if (checkIfInputIsVailed(SetInputString, true))
			{
				istringstream buffer(SetInputString);
				buffer >> SetResetBit;

				if (SetResetBit < 2)
					InputVailed = true;
			}
		}
		else
		{
			// fort DEC and HEX
			// check if the address hex input is vailed

			if (checkIfInputIsVailed(ValueString,!(DecHexBin == HEX_INPUT)))
			{
				istringstream buffer(ValueString);

				if (DecHexBin==DEC_INPUT)
					buffer >> dec >> ValueInputTemp;
				else
					buffer >> hex >> ValueInputTemp;

				// value a 32 Bit value 
				if (ValueInputTemp > UINT32_MAX)
				{
					if (ConsloeOutput)
						cout << "	ERROR: selected Value greater the 32 bit" << endl;
					InputVailed = false;
				}

				ValueInput = ValueInputTemp;
			}
			else
			{
				// value input is not vailed
				if (ConsloeOutput)
					cout << "	ERROR: selected value is input is not vailed!" << endl;
				InputVailed = false;
			}
		}

		// only in case the input is vailed write the request to the light wight bus
		if (InputVailed)
		{
			if (ConsloeOutput)
			{
				cout << "		-- Write following through a Bridge--" << endl;
				cout << "	Bridge:      " << (lwBdrige ? "Lightwight HPS to FPGA" : "HPS to FPGA AXI") << endl;
				cout << "	Brige Base:  0x" <<hex << (lwBdrige ? ALT_LWFPGASLVS_OFST : ALT_H2F_OFST) <<dec<< endl;
				cout << "	your Offset: 0x" << hex << addressOffset << dec << endl;
				cout << "	Address:     0x" << hex << ((lwBdrige ? ALT_LWFPGASLVS_OFST : ALT_H2F_OFST)+ addressOffset) << dec << endl;
		
				if (DecHexBin == BIN_INPUT)
					cout << "	Value:	 Bit Pos:" << BitPosValue <<" Output:"<< SetResetBit << endl;
				else
					cout << "new Value:	     " << ValueInput << " [0x" << hex << ValueInput << "]" << dec << endl;
			
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
				bridgeMap = mmap(NULL, sysconf(_SC_PAGE_SIZE), PROT_WRITE| PROT_READ, MAP_SHARED, fd, \
					(lwBdrige ? ALT_LWFPGASLVS_OFST : ALT_H2F_OFST));
				
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
				// write the value to the address 
				volatile  uint32_t* write_bridge = (volatile  uint32_t*) \
							(bridgeMap + addressOffset);

				// print also the old value of the selected register
				if (ConsloeOutput)
				{
					uint32_t oldValue = *write_bridge;
					cout << "	old Value:	     " << oldValue << " [0x" << hex << oldValue << "]" << dec << endl;
				}
					
				// write the new value to the selected register
				if (DecHexBin == BIN_INPUT)
				{
					if (SetResetBit) *write_bridge |= (1 << BitPosValue);
					else			 *write_bridge &= ~(1 << BitPosValue);
				}
				else
					*write_bridge = ValueInput;
				
				// Close the MAP 
				int res = munmap(bridgeMap, sysconf(_SC_PAGE_SIZE));

				if (res < 0)
				{
					if (ConsloeOutput)
						cout << "ERROR: Closing of shared memory failed!" << endl;
				}

				// close the driver port 
				close(fd);

				if (ConsloeOutput)
					cout << "Writing was successful" << endl;
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
		cout << "	Command write to address of a HPS-FPGA Bridge" << endl;
		cout << "	address" << endl;
		cout << "	FPGA-readBridge -lw [offset module address hex]" << endl;
		cout << "		read the register on the Lightweight HPS-FPGA Brige" << endl;
		cout << "		e.g.: FPGA-writeBridge -lw 0a" << endl;
		cout << endl;
		cout << "	FPGA-writeBridge -hf [offset module address hex] [value dec]" << endl;
		cout << "		write to the HPS to FPGA AXI Bridge Interface with a dec values" << endl;
		cout << "		e.g.: FPGA-writeBridge -hf 0a 255" << endl;
		cout << "	FPGA-writeBridge -hf [offset module address hex] -h [value hex]" << endl;
		cout << "		write to the HPS to FPGA AXI Bridge Interface with a hex values" << endl;
		cout << "		e.g.: FPGA-writeBridge -hf 0a -h ff" << endl;
		cout << "	FPGA-writeBridge -hf [offset module address hex] -b [Bit pos] [value]" << endl;
		cout << "		Set or Reset a Bit on HPS to FPGA AXI Bridge register" << endl;
		cout << "		e.g.: FPGA-writeBridge -hf 0a -b 8 0" << endl;
		cout << endl;
		cout << "		suffix: -b -> only decimal result output" << endl;
		cout << "						Error:  0" << endl;
		cout << "						Succses:1" << endl;
	}


	return 0;
}
