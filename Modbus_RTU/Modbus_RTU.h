/*
  Modbus_RTU.h - Modbus_RTU Client/Server library 
  Copyright (c) 2012 Gilles De Vos.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

///Function return values
enum t_status
{
  NOK = (1==0), ///< False
  OK = (1==1)   ///< True
};

// Supported communication baudrates
enum t_baud
{
  MDB_BAUD_1200 = 1200,   ///< Define baudrate to 1200 bauds
  MDB_BAUD_2400 = 2400,   ///< Define baudrate to 2400 bauds
  MDB_BAUD_4800 = 4800,   ///< Define baudrate to 4800 bauds
  MDB_BAUD_9600 = 9600,   ///< Define baudrate to 9600 bauds
  MDB_BAUD_19200 = 19200, ///< Define baudrate to 19200 bauds
  MDB_BAUD_38400 = 38400, ///< Define baudrate to 38400 bauds
};

///Communication parity
enum t_parity
{
  MDB_PARITY_EVEN,   ///< Define character parity bit to even
  MDB_PARITY_ODD,    ///< Define character parity bit to Odd
  MDB_PARITY_NONE,   ///< Define character parity bit to No parity
};

/// Modbus RTU device types
enum t_devicetype
{
  MDB_SERVER,    ///< Define a server device (often wrongly named slave)
  MDB_CLIENT,    ///< Define a client device (often wrongly named master)
};

/// Modbus data type
enum t_datatype
{
  MDB_BIT, 
  MDB_BYTE,
  MDB_WORD,
  MDB_LONG
};

// Modbus exception definitions
#define MDB_EXCEPTION_MASK 0x80
#define MDB_EXCEPTION_ILLEGAL_FUNCTION 1
#define MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS 2
#define MDB_EXCEPTION_ILLEGAL_DATA_VALUE 3
#define MDB_EXCEPTION_SERVER_DEVICE_FAILURE 4

// Modbus Server node address definitions
#define MDB_ADDRESS_MIN 1         ///< Lower bound of the server node address range
#define MDB_ADDRESS_MAX 247       ///< Upper bound of the server node address range
#define MDB_ADDRESS_BROADCAST 0   ///< All Modbus servers must accept this address but should not send any response
#define MDB_ADDRESS_MONODROP 248  ///< Specific point-to-point server node address (Schneider Electric specific)
#define MDB_ADDRESS_INVALID 255   ///< Default value out of bounds to avoid conflicts

// Modbus Message limits
#define MDB_MSG_LENGTH_MIN  4     ///< Min size of a Modbus frame (in bytes)
#define MDB_MSG_LENGTH_MAX  256   ///< Max size of a Modbus frame (in bytes)
#define MDB_INP_NUMBER_MAX  2000  ///< Max number of inputs in a frame
#define MDB_REG_NUMBER_MAX  125   ///< Max number of registers in a frame
#define MDB_REG_NUMBER_MAX_FC23  120   ///< Max number of written registers in a frame FC23

// Definition of Modbus Function Code availabilities for the application
// This allows code volume reduction
#define MDB_FUNCTIONCODE_01	///< Function code 01 availability
#define MDB_FUNCTIONCODE_02	///< Function code 02 availability
#define MDB_FUNCTIONCODE_03	///< Function code 03 availability
#define MDB_FUNCTIONCODE_04	///< Function code 04 availability
#define MDB_FUNCTIONCODE_05	///< Function code 05 availability
#define MDB_FUNCTIONCODE_06	///< Function code 06 availability
#define MDB_FUNCTIONCODE_07	///< Function code 07 availability
#define MDB_FUNCTIONCODE_08	///< Function code 08 availability
#define MDB_FUNCTIONCODE_16	///< Function code 16 availability
#define MDB_FUNCTIONCODE_23	///< Function code 23 availability

// Modbus Function codes
enum t_functioncode{
  MDB_FC01 = 1,     ///< Read coil status
  MDB_FC02 = 2,     ///< Read input status
  MDB_FC03 = 3,     ///< Read Holding register
  MDB_FC04 = 4,     ///< Read input registers
  MDB_FC05 = 5,     ///< Force single coil
  MDB_FC06 = 6,     ///< Preset single register
  MDB_FC07 = 7,     ///< Read Exception status
  MDB_FC08 = 8,     ///< Diagnostics
  MDB_FC16 = 16,    ///< Preset multiple registers
  MDB_FC23 = 23,    ///< Read/Write multiple registers
};

enum t_diagtype
{
  MDB_DIAG_0 = 0,   ///< Return query data
  MDB_DIAG_1 = 1,   ///< Restart Communication option
  MDB_DIAG_2 = 2,   ///< Return Diagnostic register
  MDB_DIAG_3 = 3,   ///< Change ASCII delimiter
  MDB_DIAG_4 = 4,   ///< Force Listen mode only
  MDB_DIAG_10 = 10, ///< Clear counters and Diagnostic register
  MDB_DIAG_11 = 11, ///< Return Bus message count
  MDB_DIAG_12 = 12, ///< Return Bus communication error count
  MDB_DIAG_13 = 13, ///< Return Bus Exception error count
  MDB_DIAG_14 = 14, ///< Return server message count
  MDB_DIAG_15 = 15, ///< Return server no response count
  MDB_DIAG_16 = 16, ///< Return server NAK count
  MDB_DIAG_17 = 17, ///< Return server busy count
  MDB_DIAG_18 = 18, ///< Return Bus charactere overrun count
  MDB_DIAG_20 = 20, ///< Clear Overrun counter and flag
};
#define MDB_MEI_READID 14  ///<  Subfunction used by MEI (Modbus Encapsulated Interface) request (FC 43)


// Modbus frame structure
typedef struct
{
  char length;
  char data[MDB_MSG_LENGTH_MAX];
} Modbus_Frame;

// Modbus Data structure
typedef struct
{
  char length;
  t_datatype type;
  unsigned int data[MDB_REG_NUMBER_MAX];
} Modbus_Data;

// CRC tables
static const unsigned char Modbus_CRC_hi[] = 
{
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

static const unsigned char Modbus_CRC_lo[] = 
{
  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2,
  0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
  0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
  0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
  0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
  0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
  0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
  0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
  0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
  0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
  0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE,
  0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
  0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA,
  0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
  0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
  0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62,
  0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
  0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE,
  0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
  0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
  0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
  0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76,
  0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
  0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
  0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
  0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
  0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
  0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A,
  0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86,
  0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

// Class Definition /////////////////////////////////////////////////////////    
class Modbus_RTU
{
  private:
    t_devicetype Mdb_Type;
    t_baud Mdb_Baudrate;
    t_parity Mdb_Parity;
    int Mdb_Address;
    int Mdb_FrameReceived;
    int Mdb_FrameNotResponded;
    int Mdb_FrameServerReceived;
    int Mdb_FrameExceptionSent;
    int Mdb_FrameServerSent;
    bool Mdb_ListenOnly;
  public:
    Modbus_RTU(int Param);
    // Device generic interface
    t_status SetType(t_devicetype Param);
    t_status GetType(t_devicetype* Param);
    t_status SetBaudrate(t_baud Param);
    t_status GetBaudrate(t_baud* Param);
    t_status SetParity(t_parity Param);
    t_status GetParity(t_parity* Param);
    t_status GetFrameTimeout(unsigned long* Value);
    t_status GetCRC16(Modbus_Frame* msg, unsigned short* Value);
    // Server specific interface
    t_status Server_SetAddress(int Param);
    t_status Server_GetAddress(int* Param);
    t_status Server_Update(Modbus_Frame* msg);
    // Client specific interface
    t_status Client_ReadCoils(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg); 
    t_status Client_ReadDiscreteInputs(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg); 
    t_status Client_ReadHoldingRegisters(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg); 
    t_status Client_ReadInputRegisters(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg); 
    t_status Client_WriteSingleCoil(int ServerAddr, unsigned short Addr, int Data, Modbus_Frame* msg); 
    t_status Client_PresetSingleRegister(int ServerAddr, unsigned short Addr, int Data, Modbus_Frame* msg); 
    t_status Client_ReadException(int ServerAddr, Modbus_Frame* msg);
    t_status Client_ReadDiagnostic(int ServerAddr, t_diagtype DiagType, int Data, Modbus_Frame* msg);
    t_status Client_PresetMultipleRegisters(int ServerAddr, unsigned short Addr, Modbus_Data* Data, Modbus_Frame* msg);
    t_status Client_ReadWriteMultipleRegisters(int ServerAddr, unsigned short rAddr, int rNb,unsigned short wAddr, Modbus_Data* Data, Modbus_Frame* msg);
    t_status Client_Update(Modbus_Frame* msg, Modbus_Data* Data);
};

// Private functions ////////////////////////////////////////////////////////
t_status Modbus_ReadCoils(Modbus_Frame* msg);
t_status Modbus_ReadDiscreteInputs(Modbus_Frame* msg);
t_status Modbus_ReadHoldingRegisters(Modbus_Frame* msg);
t_status Modbus_ReadInputRegisters(Modbus_Frame* msg);
t_status Modbus_WriteSingleCoil(Modbus_Frame* msg);
t_status Modbus_PresetSingleRegister(Modbus_Frame* msg);
t_status Modbus_ReadExceptionStatus(Modbus_Frame* msg);
t_status Modbus_ReadDiagnostic (Modbus_Frame* msg);
t_status Modbus_PresetMultipleRegisters(Modbus_Frame* msg);
t_status Modbus_ReadWriteMultipleRegisters(Modbus_Frame* msg);
t_status Modbus_ReadCoil(unsigned short Addr, int* Value);
t_status Modbus_WriteCoil(unsigned short Addr, int* Value);
t_status Modbus_ReadInput(unsigned short Addr, int* Value);
t_status Modbus_ReadRegister(unsigned short Addr, int* Value);
t_status Modbus_ReadInputRegister(unsigned short Addr, int* Value);
t_status Modbus_WriteRegister(unsigned short Addr, int* Value);
t_status Modbus_ReadException(int* Param1);
t_status Modbus_CRC16(Modbus_Frame* msg, unsigned short* Value);
t_status Modbus_Exception(int Param, Modbus_Frame* msg);




 