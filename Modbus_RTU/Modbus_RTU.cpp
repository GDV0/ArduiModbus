/*
  Modbus_RTU.cpp - Modbus_RTU client/server library 
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

/***********************************************************************//**
* \defgroup Device Modbus Device functions
* These functions are related to the Modbus device (both Client and Server)
* \defgroup Server Modbus Server functions
* These functions are specific to the Modbus Server device implementation
* \defgroup Client Modbus client functions
* These functions are specific to the Modbus client device implementation
* \defgroup Callbacks Callback functions
* These functions shall be implemented in the server application to define access to used device objects.
* It is the responsibility of the user application to manage the returned value according to the result of the request.
* If the function is not implemented in the user code, the returned value will be NOK 
***************************************************************************/

// Include files //////////////////////////////////////////////////////////////
#include "Modbus_RTU.h"
#include"Arduino.h"

// Macros /////////////////////////////////////////////////////////////////////
#define GET_WORD(p)     ((((unsigned short)(*(p))& 0x0ff) << 8) | (*((p)+1)& 0x0ff))
#define PUT_WORD(p, x)  {*(p) = ((x) >> 8) & 0x0ff; *((p)+1) = (x) & 0x0ff;}
 
//=============================================================================
// Public functions
//=============================================================================

///\class Modbus_RTU
// Class Constructor //////////////////////////////////////////////////////////
Modbus_RTU::Modbus_RTU(int Param)
{
  // Initialize device as server to avoid transmissions when connected to the network
  Mdb_Type = MDB_SERVER;

  // Initialize address to 255 which is not a correct Modbus address (1-247)
  Mdb_Address = MDB_ADDRESS_INVALID;

  // Initialize baudrate to 19200 Bauds and parity to Even
  Mdb_Baudrate = MDB_BAUD_19200;
  Mdb_Parity = MDB_PARITY_EVEN;
}

// Callback functions /////////////////////////////////////////////////////// 
t_status Modbus_CB_SetCoil(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function sets the state of a single coil 
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the coil to be set
*   \param[in]  Param2 Pointer to a variable which contains the state of the coil
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_SetCoil(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_GetCoil(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function provides the state of a single coil
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the coil to be read
*   \param[out]  Param2 Pointer to a variable which will receive the state of the coil
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_GetCoil(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_GetInput(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function provides the state of a single input
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the input to be read
*   \param[out]  Param2 Pointer to a variable which will receive the state of the input
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_GetInput(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_SetRegister(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function writes a value in a Single register
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the register to write
*   \param[out]  Param2 Pointer to a variable which contains the value to write
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_SetRegister(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_GetRegister(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function provides the value of a single register
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the register to be read
*   \param[out]  Param2 Pointer to a variable which will receive the value of the register
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_GetRegister(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_GetInputRegister(unsigned short Param1, int* Param2) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function provides the state of a single input register
*   \ingroup    Callbacks
*   \param[in]  Param1 Address of the input register to be read
*   \param[out]  Param2 Pointer to a variable which will receive the state of the input register
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_GetInputRegister(unsigned short Param1, int* Param2)
{
  t_status Status = NOK;
  return(Status);
}

t_status Modbus_CB_GetException(int* Param1) __attribute__((weak));
/**************************************************************************//**
*   \brief      This function provides the value of the Modbus exception register
*   \ingroup    Callbacks
*   \param[out]  Param1 Pointer to a variable which will receive the state of the exception register
*   \return     Shall be OK if operation is accepted
*   \return     Shall be NOK if operation is not accepted
******************************************************************************/
t_status Modbus_CB_GetException(int* Param1)
{
  t_status Status = NOK;
  return(Status);
}

// Class Interface : Device ///////////////////////////////////////////////////
/**************************************************************************//**
*   \brief      This function sets the type of Modbus RTU instance : Server or Client
*   \ingroup Device
*   \param[in]  Param Modbus device type
*   \return     OK if Param is a supported Modbus device type
*   \return     NOK if Param is not a supported Modbus device type
******************************************************************************/
t_status Modbus_RTU::SetType(t_devicetype Param)
{
  t_status Status = NOK;
  switch (Param)
  {
    case MDB_SERVER:
    case MDB_CLIENT:
        Mdb_Type = Param;
        Status = OK;
        break;
    default:
        Status = NOK;
        break;
  }  
  return (Status);
}

/**************************************************************************//**
*   \brief      This function provides the type of the Modbus instance : Server or Client
*   \ingroup Device  
*   \param[out] Param Pointer to a variable which will receive the device type
*   \return     OK
******************************************************************************/
t_status Modbus_RTU::GetType(t_devicetype* Param)
{
  *Param = Mdb_Type;
  return (OK);
}

/**************************************************************************//**
*   \brief      This function sets the Baudrate used for Modbus communication
*   \ingroup Device  
*   \param[in]  Param Modbus Baudrate (from 1200 to 19200)
*   \return     OK if Param value is a supported Baudrate value
*   \return     NOK if Param value is not a supported Baudrate value  
******************************************************************************/
t_status Modbus_RTU::SetBaudrate(t_baud Param)
{
  t_status Status;

  // Check if Param value is part of the baudrate list
  if ((Param != MDB_BAUD_1200) || 
      (Param != MDB_BAUD_2400) || 
      (Param != MDB_BAUD_4800) || 
      (Param != MDB_BAUD_9600) || 
      (Param != MDB_BAUD_19200)|| 
      (Param != MDB_BAUD_38400))
  {
    Status = NOK;
  }
  else
  {
    // Store the value
    Mdb_Baudrate = Param;
    Status = OK;
  }
  return (Status);
}

/**************************************************************************//**
*   \brief      This function provides the Baudrate used for Modbus communication
*   \ingroup Device  
*   \param[out] Param Pointer to a variable which will receive the baudrate value
*   \return     OK
******************************************************************************/
t_status Modbus_RTU::GetBaudrate(t_baud* Param)
{
  *Param = Mdb_Baudrate;
  return (OK);
}

/**************************************************************************//**
*   \brief      This function sets the parity used for Modbus communication
*   \ingroup Device  
*   \param[in]  Param Modbus parity (None, even odd)
*   \return     OK if Param value is a supported parity value
*   \return     NOK if Param value is not a supported parity value  
******************************************************************************/
t_status Modbus_RTU::SetParity(t_parity Param)
{
  t_status Status;

  // Check if Param value is part of the Parity list
  if ((Param != MDB_PARITY_EVEN) || 
      (Param != MDB_PARITY_ODD) || 
      (Param != MDB_PARITY_NONE))
  {
    Status = NOK;
  }
  else
  {
    // Store the value
    Mdb_Parity = Param;
    Status = OK;
  }
  return (Status);
}

/**************************************************************************//**
*   \brief      This function provides the parity used for Modbus communication
*   \ingroup Device  
*   \param[out] Param Pointer to a variable which will receive the parity value
*   \return     OK
******************************************************************************/
t_status Modbus_RTU::GetParity(t_parity* Param)
{
  *Param = Mdb_Parity;
  return (OK);
}

/**************************************************************************//**
*   \brief      This function provides the CRC16 for a given modbus frame
*   \ingroup Device  
*   \param[in]  msg Pointer to a the Modbus frame
*   \param[out] Value Pointer to a variable which will receive the CRC16 value
*   \return     OK if CRC16 is available
*   \return     NOK if CRC16 is not available (i.e. msg is empty)
******************************************************************************/
t_status Modbus_RTU::GetCRC16(Modbus_Frame* msg, unsigned short* Value)
{
  return (Modbus_CRC16 (msg, Value));
}

/**************************************************************************//**
*   \brief      This function provides the minimum time between 2 frames 
*               (should be equivalent to 3,5 char)
*   \ingroup Device  
*   \param[out] Value Pointer to a variable which will receive the time in µs
*   \return     OK if time is available
*   \return     NOK if time is not available
******************************************************************************/
t_status Modbus_RTU::GetFrameTimeout(unsigned long* Value)
{
  t_status Status;

  //Initialize the return value and Status
  *Value = 0;
  Status = OK;
  
  // Check if Param value is part of the Parity list
  switch (Mdb_Baudrate)
  {
    case MDB_BAUD_1200:
    case MDB_BAUD_2400:
    case MDB_BAUD_4800:
    case MDB_BAUD_9600:
    case MDB_BAUD_19200:
    case MDB_BAUD_38400:
        // 1 character = 11 bits
        //    if parity = even or odd, char length = 1 start bit + 8 bits data + 1 bit parity + 1 stop bit = 11 bits
        //    if parity is none, char length = 1 start bit + 8 bits data + 2 stop bits = 11 bits
        // Timeout value (second)= (3,5 * 11) / Baudrate
        *Value = (unsigned long)(3500000 * 11 / Mdb_Baudrate);
        break;
    default:
        Status = NOK;
        break;
    
  }
  return (Status);
}

// Class Interface : Server ////////////////////////////////////////////////////
/**************************************************************************//**
*   \brief      This function sets the Modbus server address for the device 
*   \ingroup Server  
*   \param[in]  Param Modbus address (from 1 to 247)
*   \return     OK if Param is a supported address value
*   \return     NOK if Param is not a supported address value or the device is not a server
******************************************************************************/
t_status Modbus_RTU::Server_SetAddress(int Param)
{
  t_status Status;
  
  //Server node address is only for server for sure !!
  if ((Param < MDB_ADDRESS_MIN) || 
      (Param > MDB_ADDRESS_MAX) || 
      (Mdb_Type == MDB_CLIENT))
  {
    Status = NOK;
  }
  else
  {
    Mdb_Address = Param;
    Status = OK;
  }
  return (Status);
}

/**************************************************************************//**
*   \brief      This function provides the Modbus server address of the device 
*   \ingroup Server  
*   \param[out] Param Pointer to a variable which will contain the device address
*   \return     OK if the device address exists even if it is not a valid one
*   \return     NOK if the device address doesn't exist (i.e. the device is not a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Server_GetAddress(int* Param)
{
  t_status Status;

  // Device Address exists only for Modbus server devices
  if (Mdb_Type == MDB_SERVER)
  {
    *Param = Mdb_Address;
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}

/**************************************************************************//**
*   \brief      This function serves Modbus frames sent by the Client 
*
*               This function shall be called in the server main loop 
*               after receiving a Modbus frame to generate the response frame
*   \ingroup Server  
*   \param[in,out]  msg Pointer to a message that contains the Modbus frame sent by the CLient 
*                 and will receive the response frame to be returned to the Client
*   \return     OK if a response frame should be sent on the bus
*   \return     NOK if no response frame should be sent on the bus
******************************************************************************/
t_status Modbus_RTU::Server_Update(Modbus_Frame* msg)
{
  t_status Status;
  unsigned short CRC16, crc1;
  
  // Wait for a message
  Mdb_FrameReceived++;
  
  // check if address is correct
  if ((msg->data[0] == (char)MDB_ADDRESS_BROADCAST) ||
      (msg->data[0]==(char)MDB_ADDRESS_MONODROP) ||
      (msg->data[0]==(char)Mdb_Address))
  {
    // Frame is for this server
    Mdb_FrameServerReceived++;
    
    // Check frame CRC
    CRC16 = GET_WORD(msg->data + msg->length-2);
    if (Modbus_CRC16(msg, &crc1))
    {
      if (crc1 != CRC16)
      {
        return(NOK);
      }
    }
      // Check function code
      switch (msg->data[1])
      {
#if defined(MDB_FUNCTIONCODE_01)
        case MDB_FC01: //Read Coils
            Modbus_ReadCoils (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_02)
        case MDB_FC02: //Read Discrete Inputs
            Modbus_ReadDiscreteInputs (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_03)
        case MDB_FC03: //Read Holding Registers
            Modbus_ReadHoldingRegisters (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_04)
        case MDB_FC04: //Read Input Registers
            Modbus_ReadInputRegisters (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_05)
        case MDB_FC05: //Write Single coil
            Modbus_WriteSingleCoil (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_06)
        case MDB_FC06: //Preset Single Register
            Modbus_PresetSingleRegister (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_07)
        case MDB_FC07: //Read Exception Status
            Modbus_ReadExceptionStatus (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_08)
        case MDB_FC08: //Read Exception Status
            Modbus_ReadDiagnostic (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_16)
        case MDB_FC16: //Preset Multiple Registers
            Modbus_PresetMultipleRegisters (msg);
            break;
#endif
#if defined(MDB_FUNCTIONCODE_23)
        case MDB_FC23: //Read/Write Multiple Registers
            Modbus_ReadWriteMultipleRegisters (msg);
            break;
#endif
        default:
            Modbus_Exception(MDB_EXCEPTION_ILLEGAL_FUNCTION, msg);
            break;
      }
      Status = OK;
  }
  else
  {
    // frame ignored
    Status = NOK;
    Mdb_FrameNotResponded++;
  }
  return (Status);
}

// CLass Interface : client ///////////////////////////////////////////////////
#if defined(MDB_FUNCTIONCODE_01)
/**************************************************************************//**
*   \brief      This function builds a Read Coils request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the first coil to be read
*   \param[in]  Nb Number of consecutive coils to read
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadCoils(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC01;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Nb);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_02)
/**************************************************************************//**
*   \brief      This function builds a Read Discrete Inputs request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the first input to be read
*   \param[in]  Nb Number of consecutive inputs to read
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadDiscreteInputs(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC02;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Nb);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_03)
/**************************************************************************//**
*   \brief      This function builds a Read Holding Registers request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted server
*   \param[in]  Addr Address of the first register to be read
*   \param[in]  Nb Number of consecutive registers to read
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadHoldingRegisters(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC03;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Nb);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_04)
/**************************************************************************//**
*   \brief      This function builds a Read Input Registers request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the first input register to be read
*   \param[in]  Nb Number of consecutive input registers to read
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadInputRegisters(int ServerAddr, unsigned short Addr, int Nb, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC04;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Nb);
    
    // Add CRC16
    Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  } 
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_05)
/**************************************************************************//**
*   \brief      This function builds a Write Single Coil request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the coil to write
*   \param[in]  Data Desired state of the coil
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_WriteSingleCoil(int ServerAddr, unsigned short Addr, int Data, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC05;
    if (Data != 0)
      Data = 0xFF;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Data);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_06)
/**************************************************************************//**
*   \brief      This function builds a Preset Single Register request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the register to write
*   \param[in]  Data Desired value of the register
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_PresetSingleRegister(int ServerAddr, unsigned short Addr, int Data, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC06;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Data);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_07)
/**************************************************************************//**
*   \brief      This function builds a Read Exception request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadException(int ServerAddr, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 4;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC07;
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status); 
}
#endif

#if defined(MDB_FUNCTIONCODE_08)
/**************************************************************************//**
*   \brief      This function builds a Read Diagnostic request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  DiagType Select which diagnostic value is requested
*   \param[in]  Data Additionnal information (depending on DiagType)
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadDiagnostic(int ServerAddr, t_diagtype DiagType, int Data, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 8;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC08;
    PUT_WORD(&msg->data[2], DiagType);
    PUT_WORD(&msg->data[4], Data);
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status); 
}
#endif

#if defined(MDB_FUNCTIONCODE_16)
/**************************************************************************//**
*   \brief      This function builds a Preset Multiple Registers request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  Addr Address of the first register to be written
*   \param[in]  Data Pointer to a structure which contains number of register to write 
*               and the values to write in them
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_PresetMultipleRegisters(int ServerAddr, unsigned short Addr, Modbus_Data* Data, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  char Nb;
  char* dest;
  int* src;
  int i;
  
  Nb = Data->length;
  
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 7 + Nb * 2 + 2;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC16;
    PUT_WORD(&msg->data[2], Addr);
    PUT_WORD(&msg->data[4], Nb);
    msg->data[6] = Nb * 2;
    
    // writes the data to send  in the Modbus frame
    for (i = 0; i < Nb; i++)
    {
      dest = &msg->data[7] + 2 * i;
      src = (int*)&Data->data[0] + i;         // because variable type is integer for Data
      PUT_WORD(dest, *src)
    }
    
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_23)
/**************************************************************************//**
*   \brief      This function builds a Read/Write Multiple Registers request 
*   \ingroup client  
*   \param[in]  ServerAddr Node address of the targeted Modbus server
*   \param[in]  rAddr Address of the first register to be read
*   \param[in]  rNb Number of consecutive registers registers to read
*   \param[in]  wAddr Address of the first register to be written
*   \param[in]  Data Pointer to a structure that contains the number of consecutive register 
*               and the values to write in them
*   \param[out] msg Pointer to a message which will receive the request to be sent on the network
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error, or device type is  a Modbus server)
******************************************************************************/
t_status Modbus_RTU::Client_ReadWriteMultipleRegisters(int ServerAddr, unsigned short rAddr, int rNb,unsigned short wAddr, Modbus_Data* Data, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  int i;
 
  if (Mdb_Type == MDB_CLIENT)
  {
    //Build the request
    msg->length = 11 + Data->length * 2 + 2;
    msg->data[0] = ServerAddr;
    msg->data[1] = MDB_FC23;
    PUT_WORD(&msg->data[2], rAddr);
    PUT_WORD(&msg->data[4], rNb);
    PUT_WORD(&msg->data[6], wAddr);
    PUT_WORD(&msg->data[8], Data->length);
    msg->data[10] = Data->length * 2;
    for (i = 0; i<Data->length; i++)
    {
      PUT_WORD(&msg->data[11+(i*2)], Data->data[i]);
    }
  
    // Add CRC16
    Status = Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[msg->length-2], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return(Status);
}
#endif

//#ifdef MODBUS_CLIENT
/**************************************************************************//**
*   \brief      This function extracts Data from the response frame sent by a Modbus server
*
*   This function shall be called after receiving a response to a request frame 
*   to extract required data.  
*   \ingroup Client  
*   \param[in]  msg Pointer to a message which contains the response frame received from the network
*   \param[out] Data Pointer to a structure which will receive the number of data and their values 
*   \return     OK if treatment is possible (in case of Modbus exception, length will be 0) 
*   \return     NOK if this function could not be executed ( i.e. if the device type is not a client)
******************************************************************************/
t_status Modbus_RTU::Client_Update(Modbus_Frame* msg, Modbus_Data* Data)
{
  t_status Status = OK;
  int i;
  unsigned short CRC16 = 0;
  unsigned short crc1 = 0xFFFF;
  
  // Init of the destination structure
  Data->length = 0;
  
  if (Mdb_Type == MDB_CLIENT)
  {   
    // Check frame CRC
    CRC16 = GET_WORD(msg->data + msg->length-2);
    if (Modbus_CRC16(msg, &crc1))
    {
      if (crc1 != CRC16)
      {
        return(NOK);
      }
    }

    switch(msg->data[1])
    {
#if defined(MDB_FUNCTIONCODE_01) || defined(MDB_FUNCTIONCODE_02)
      case MDB_FC01:
      case MDB_FC02:
          Data->length = msg->data[2];
          Data->type = MDB_BIT;
          for (i = 0; i<Data->length; i++)
          {
            Data->data[0+i] = msg->data[3 + i];
          }
          break;
#endif
#if defined(MDB_FUNCTIONCODE_03) || defined(MDB_FUNCTIONCODE_04)
      case MDB_FC03:
      case MDB_FC04:
          Data->length = msg->data[2] / 2;
          Data->type = MDB_WORD;
          for (i = 0; i<Data->length; i++)
          
          {
            Data->data[i * 2] = msg->data[3 + (i *2 )];
            Data->data[(i * 2) + 1] = msg->data[4 + (i *2 )];
          }
          break;
#endif
#if defined(MDB_FUNCTIONCODE_05) || defined(MDB_FUNCTIONCODE_06)
      case MDB_FC05:
      case MDB_FC06:
          break;
#endif
#if defined(MDB_FUNCTIONCODE_07)
      case MDB_FC07:
          Data->length = 1;
          Data->type = MDB_BYTE;
          Data->data[0] = msg->data[2];
          break;
#endif
#if defined(MDB_FUNCTIONCODE_16)
      case MDB_FC16:
          break;
#endif
#if defined(MDB_FUNCTIONCODE_23)
      case MDB_FC23:
          Data->length = msg->data[2] / 2;
          Data->type = MDB_WORD;
          for (i = 0; i<Data->length; i++)
          
          {
            Data->data[i * 2] = msg->data[3 + (i *2 )];
            Data->data[(i * 2) + 1] = msg->data[4 + (i *2 )];
          }
          break;
#endif
      default:
          break;
    }
  }
  else
  {
    Status = NOK;
  }
    return(OK);
}
//#endif

//=============================================================================
// Private functions
//=============================================================================
/**************************************************************************//**
*   \brief      This function builds Modbus exception response frame
*   \param[in]  Param Mosbus exception code
*   \param[in,out] msg Pointer to a message that contains the Modbus frame sent by the Client 
*                 and will receive the response frame to be returned to the Client
*   \return     OK if the request frame has been successfuly generated
*   \return     NOK if the request frame has not been generated (i.e. CRC16 error)
******************************************************************************/
t_status Modbus_Exception(int Param, Modbus_Frame* msg)
{
  t_status Status = OK;
  unsigned short CRC16 = 0;
  
  // Build exception frame
  msg->data[1] |= MDB_EXCEPTION_MASK; 
  msg->data[2] = (char)Param;
  msg->length = 5;
  
  // Add CRC16
  Status = Modbus_CRC16(msg, &CRC16);
  PUT_WORD(&msg->data[3], CRC16);
    
  return (Status);
}

/**************************************************************************//**
*   \brief      This function computes Modbus CRC16
*   \param[in] msg Pointer to a message that contains the Modbus frame
*                (data + length including server node address and CRC16) 
*   \param[out] Value Pointer to a variable that will receive the CRC16 value
*   \return     OK if the CRC16 has been successfuly generated
*   \return     NOK if the CRC16 has not been generated (i.e. frame length = 0)
******************************************************************************/
t_status Modbus_CRC16(Modbus_Frame* msg, unsigned short* Value)
{
  t_status Status = OK;
   
  unsigned short hi = 0x00FF;
  unsigned short lo = 0x00FF;
  unsigned char i;
  char* buffer;
  char tmp;
  int length;

  if ((msg != 0) && (msg->length > 2))
  {
    // Remove CRC from the message length
    length = msg->length - 2;
    buffer = &msg->data[0];
    while (length--)
    {
  tmp = *buffer;
       i = lo ^ *buffer++;
        lo = hi ^ Modbus_CRC_hi[i];
        hi = Modbus_CRC_lo[i];
   }

    // note that, while the above loop computes the byte swapped CRC
    // (e.g., lo is really hi and hi is really lo)
    // we have to re-swap when assembling a 16-bit word on a little-endian CPU
    *Value = (int)(lo << 8 | hi);
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}

// Response management function
#if defined(MDB_FUNCTIONCODE_01)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC01 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to sent
*                (data + length including Server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadCoils(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short CoilAddress;
  unsigned short CoilNb;
  int CoilValue;
  char* dest;
  unsigned short CRC16 = 0;
  char CoilByte = 0;
  int IndCoil= 0;
  int NbByte = 0;

  
  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    CoilAddress = GET_WORD(&msg->data[2]);
    CoilNb = GET_WORD(&msg->data[4]);
    
    // Check if data are correct
    if ((CoilAddress < 0) || 
        (CoilAddress > 0xFFFF - CoilNb + 1) || 
        (CoilNb <= 0) || (CoilNb > MDB_INP_NUMBER_MAX))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Prepare response frame
      dest = msg->data + 3;
      
      // loop on all inputs to read
      while (CoilNb--)
      {
        // Check if register exists
        if (Modbus_ReadCoil(CoilAddress, &CoilValue))
        {
          // Store value in the response frame
          CoilByte |= CoilValue << IndCoil;
          // prepare for next input
          CoilAddress++;
          IndCoil++;
          if ((IndCoil == 8) ||(CoilNb == 0))
          {
            IndCoil = 0;
            *dest = CoilByte;
            CoilByte = 0;
            dest+=1;
            NbByte++;
          }
        }          
        else
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
          CoilNb = 0;
        }
      }
      // Add nb of data bytes and frame length
      msg->data[2] = NbByte;
      msg->length = 3 + NbByte + 2;
      
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(dest, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_02)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC02 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadDiscreteInputs(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short InpAddress;
  unsigned short InpNb;
  int InpValue;
  char* dest;
  unsigned short CRC16 = 0;
  char InpByte = 0;
  int IndInput = 0;
  int NbByte = 0;

  
  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    InpAddress = GET_WORD(&msg->data[2]);
    InpNb = GET_WORD(&msg->data[4]);
    
    // Check if data are correct
    if ((InpAddress < 0) || 
        (InpAddress > 0xFFFF - InpNb + 1) || 
        (InpNb <= 0) || 
        (InpNb > MDB_INP_NUMBER_MAX))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Prepare response frame
      dest = msg->data + 3;
      
      // loop on all inputs to read
      while (InpNb--)
      {
        // Check if register exists
        if (Modbus_ReadInput(InpAddress, &InpValue))
        {
          // Store value in the response frame
          InpByte |= InpValue << IndInput;
          // prepare for next input
          InpAddress++;
          IndInput++;
          if ((IndInput == 8) ||(InpNb == 0))
          {
            IndInput = 0;
            *dest = InpByte;
            InpByte = 0;
            dest+=1;
            NbByte++;
          }
        }          
        else
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
          InpNb = 0;
        }
      }
      // Add nb of data bytes and frame length
      msg->data[2] = NbByte;
      msg->length = 3 + NbByte + 2;
      
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(dest, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_03)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC03 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadHoldingRegisters(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short RegAddress;
  unsigned short RegNb;
  int RegValue;
  char* dest;
  unsigned short CRC16 = 0;

  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    RegAddress = GET_WORD(&msg->data[2]);
    RegNb = GET_WORD(&msg->data[4]);
    
    // Check if data are correct
    if ((RegAddress < 0)  ||
        (RegAddress > 0xFFFF-RegNb+1) ||
        (RegNb <= 0)||(RegNb > MDB_REG_NUMBER_MAX))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Prepare response frame
      msg->length = 3 + (RegNb * 2) + 2;    //Length of the response including CRC      
      msg->data[2] = RegNb * 2;             //Number of data bytes
      dest = msg->data + 3;
      
      // loop on all registers to read
      while (RegNb--)
      {
        // Check if register exists
        if (Modbus_ReadRegister(RegAddress, &RegValue))
        {
          // Store value in the response frame
          PUT_WORD(dest, RegValue);
          // Prepare data for next register
          dest +=2;
          RegAddress++;
        }
        else
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
          RegNb = 0;
        }
      }
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(dest, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
  }
#endif
  
#if defined(MDB_FUNCTIONCODE_04)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC04 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadInputRegisters(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short RegAddress;
  unsigned short RegNb;
  int RegValue;
  char* dest;
  unsigned short CRC16 = 0;

  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    RegAddress = GET_WORD(&msg->data[2]);
    RegNb = GET_WORD(&msg->data[4]);

    // Check if data are correct
    if ((RegAddress < 0)  ||
        (RegAddress > 0xFFFF-RegNb+1) ||
        (RegNb <= 0)||(RegNb > MDB_REG_NUMBER_MAX))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Prepare response frame
      msg->length = 3 + (RegNb * 2) + 2;    //Length of the response including CRC      
      msg->data[2] = RegNb * 2;             //Number of data bytes
      dest = msg->data + 3;
      
      // loop on all registers to read
      while (RegNb--)
      {
        // Check if register exists
        if (Modbus_ReadInputRegister(RegAddress, &RegValue))
        {
          // Store value in the response frame
          PUT_WORD(dest, RegValue);
          // Prepare data for next register
          dest +=2;
          RegAddress++;
        }
        else
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
          RegNb = 0;
        }
      }
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(dest, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
  }
#endif

#if defined(MDB_FUNCTIONCODE_05)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC05 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_WriteSingleCoil(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short CoilAddress;
  int CoilValue;

  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    CoilAddress = GET_WORD(&msg->data[2]);
    CoilValue = GET_WORD(&msg->data[4]);
    
    // Check if data are correct
    if ((CoilAddress < 0) ||
        (CoilAddress > 0xFFFF) ||
        ((CoilValue != 0) && (CoilValue != 0xFF)))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      if (!Modbus_WriteCoil(CoilAddress, &CoilValue))
      {
        // One of the registers is not available
        Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
      }
    }
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

#if defined(MDB_FUNCTIONCODE_06)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC06 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_PresetSingleRegister(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short RegAddress;
  int RegValue;

  // Check if Request frame length is correct
  if (msg->length == 8)
  {
    // Extract the request data
    RegAddress = GET_WORD(&msg->data[2]);
    RegValue = GET_WORD(&msg->data[4]);
    
    // Check if data are correct
    if ((RegAddress < 0) ||
        (RegAddress > 0xFFFF))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      if (!Modbus_WriteRegister(RegAddress, &RegValue))
      {
        // One of the registers is not available
        Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
      }
    }
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

#if defined(MDB_FUNCTIONCODE_07)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC07 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadExceptionStatus(Modbus_Frame* msg)
{
  t_status Status;
  
  int ExceptionValue;
  unsigned short CRC16 = 0;

  // Check if Request frame length is correct
  if (msg->length == 4)
  {
    if (Modbus_ReadException( &ExceptionValue))
    {
      msg->length = 5;                //Length of the response including CRC      
      msg->data[2] = ExceptionValue;  //Number of data bytes
    }
    else
    {
      // One of the registers is not available
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
    }
    // Add CRC16
    Modbus_CRC16 (msg, &CRC16);
    PUT_WORD(&msg->data[3], CRC16);
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

#if defined(MDB_FUNCTIONCODE_08)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC08 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadDiagnostic (Modbus_Frame*msg)
{
  t_status Status;
  
  unsigned short RegAddress;
  unsigned short RegNb;
  int RegValue;
  char* src;
  unsigned short CRC16 = 0;

  // Extract the request data
  RegAddress = GET_WORD(&msg->data[2]);
  RegNb = GET_WORD(&msg->data[4]);

  // Check if Request frame length is correct
  if (msg->length == (char)(8))
  {
    // Check if data are correct
    if ((RegAddress < 0) || 
        (RegAddress > (0xFFFF - RegNb + 1)) || 
        (RegNb <= 0) || (RegNb > (MDB_REG_NUMBER_MAX - 2)))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Length of the response including CRC
      msg->length = 8;

      // Start of the register value list
      src = msg->data + 7;
      
      // Loop on all register
      while(RegNb--)
      {
        RegValue = GET_WORD(src);
        if (!Modbus_WriteRegister(RegAddress, &RegValue))
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
        }
        RegAddress++;
        src += 2;
      }
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(src, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

#if defined(MDB_FUNCTIONCODE_16)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC16 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including server node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_PresetMultipleRegisters(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short RegAddress;
  unsigned short RegNb;
  int RegValue;
  char* src;
  unsigned short CRC16 = 0;

  // Extract the request data
  RegAddress = GET_WORD(&msg->data[2]);
  RegNb = GET_WORD(&msg->data[4]);

  // Check if Request frame length is correct
  if (msg->length == (char)(7 + 2 * RegNb + 2))
  {
    // Check if data are correct
    if ((RegAddress < 0) || 
        (RegAddress > (0xFFFF - RegNb + 1)) || 
        (RegNb <= 0) || (RegNb > (MDB_REG_NUMBER_MAX - 2)))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Length of the response including CRC
      msg->length = 8;

      // Start of the register value list
      src = msg->data + 7;
      
      // Loop on all register
      while(RegNb--)
      {
        RegValue = GET_WORD(src);
        if (!Modbus_WriteRegister(RegAddress, &RegValue))
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
        }
        RegAddress++;
        src += 2;
      }
      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(src, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

#if defined(MDB_FUNCTIONCODE_23)
/**************************************************************************//**
*   \brief      This function builds the response frame to a FC23 command
*   \param[in,out] msg Pointer to a message that contains the Modbus frame received from the client
*                 and will receive the response frame to be sent
*                (data + length including node address and CRC16) 
*   \return     OK if the frame has been successfuly generated
*   \return     NOK if the frame has not been generated 
******************************************************************************/
t_status Modbus_ReadWriteMultipleRegisters(Modbus_Frame* msg)
{
  t_status Status;
  
  unsigned short rRegAddress, wRegAddress;
  unsigned short rRegNb, wRegNb;
  int RegValue;
  char* src;
  char* dest;
  unsigned short CRC16 = 0;

  // Extract the request data
  rRegAddress = GET_WORD(&msg->data[2]);
  rRegNb = GET_WORD(&msg->data[4]);
  wRegAddress = GET_WORD(&msg->data[6]);
  wRegNb = GET_WORD(&msg->data[8]);

  // Check if Request frame length is correct
  if (msg->length == (char)(11 + 2 * wRegNb + 2))
  {
    // Check if data are correct
    if ((rRegAddress < 0) ||
        (wRegAddress < 0) ||
        (rRegAddress > (0xFFFF - rRegNb + 1)) || 
        (wRegAddress > (0xFFFF - wRegNb + 1)) || 
        (rRegNb <= 0) || (rRegNb > (MDB_REG_NUMBER_MAX - 2)) ||
        (wRegNb <= 0) || (wRegNb > (MDB_REG_NUMBER_MAX_FC23 - 2)))
    {
      Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_VALUE, msg);
    }
    else
    {
      // Start of the register value list
      src = msg->data + 11;
      
      // Loop on all registers to be written
      while(wRegNb--)
      {
        RegValue = GET_WORD(src);
        if (!Modbus_WriteRegister(wRegAddress, &RegValue))
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
        }
        wRegAddress++;
        src += 2;
      }

      // Prepare response frame
      msg->length = 3 + (rRegNb * 2) + 2;   //Length of the response including CRC      
      msg->data[2] = rRegNb * 2;            //Number of data bytes
      dest = msg->data + 3;
      
      // loop on all registers to read
      while (rRegNb--)
      {
        // Check if register exists
        if (Modbus_ReadRegister(rRegAddress, &RegValue))
        {
          // Store value in the response frame
          PUT_WORD(dest, RegValue);
          // Prepare data for next register
          dest += 2;
          rRegAddress++;
        }
        else
        {
          // One of the registers is not available
          Modbus_Exception(MDB_EXCEPTION_ILLEGAL_DATA_ADDRESS, msg);
          rRegNb = 0;
        }
      }

      // Add CRC16
      Modbus_CRC16 (msg, &CRC16);
      PUT_WORD(dest, CRC16);
    }
    Status = OK;
  }
  else
  {
    Status = NOK;
  }
  return (Status);
}  
#endif

//Object access functions
#if defined(MDB_FUNCTIONCODE_01)
/**************************************************************************//**
*   \brief      This function provides the state of a single coil
*   \param[in] Addr Address of the coil to evaluate
*   \param[out] Value Pointer to a varaiable which will receive the state of the coil
*   \return     OK if the state is available
*   \return     NOK if the state is not available
******************************************************************************/
t_status Modbus_ReadCoil(unsigned short Addr, int* Value)
{
  t_status Status = OK;
 
 if (!Modbus_CB_GetCoil(Addr, Value))
  {
    Status = NOK;
  }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_02)
/**************************************************************************//**
*   \brief      This function provides the state of a single Input
*   \param[in] Addr Address of the input to evaluate
*   \param[out] Value Pointer to a varaiable which will receive the state of the input
*   \return     OK if the state is available
*   \return     NOK if the state is not available
******************************************************************************/
t_status Modbus_ReadInput(unsigned short Addr, int* Value)
{
  t_status Status = OK;
 
 if (!Modbus_CB_GetInput(Addr, Value))
  {
    Status = NOK;
  }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_03) || defined(MDB_FUNCTIONCODE_23)
/**************************************************************************//**
*   \brief      This function provides the value of a single Register
*   \param[in] Addr Address of the Register to read
*   \param[out] Value Pointer to a varaiable which will receive the value of the register
*   \return     OK if the value is available
*   \return     NOK if the value is not available
******************************************************************************/
t_status Modbus_ReadRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;
 
 if (!Modbus_CB_GetRegister(Addr, Value))
  {
    Status = NOK;
  }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_04)
/**************************************************************************//**
*   \brief      This function provides the value of a single input register
*   \param[in] Addr Address of the input register to read
*   \param[out] Value Pointer to a varaiable which will receive the value of the input register
*   \return     OK if the value is available
*   \return     NOK if the value is not available
******************************************************************************/
t_status Modbus_ReadInputRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;

  if (!Modbus_CB_GetInputRegister(Addr, Value))
  {
      Status = NOK;
  }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_05)
/**************************************************************************//**
*   \brief      This function sets the state of a single coil
*   \param[in] Addr Address of the coil to set
*   \param[out] Value Pointer to a varaiable which contains the state to apply
*   \return     OK if function is successful
*   \return     NOK if function is not successful
******************************************************************************/
t_status Modbus_WriteCoil(unsigned short Addr, int* Value)
{
  t_status Status = OK;
 
 if (!Modbus_CB_SetCoil(Addr, Value))
  {
    Status = NOK;
  }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_06) || defined(MDB_FUNCTIONCODE_16) || defined(MDB_FUNCTIONCODE_23)
/**************************************************************************//**
*   \brief      This function sets the value of a single register
*   \param[in] Addr Address of the register to write
*   \param[out] Value Pointer to a varaiable which contains the value to write
*   \return     OK if function is successful
*   \return     NOK if function is not successful
******************************************************************************/
t_status Modbus_WriteRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;
  
  if (!Modbus_CB_SetRegister(Addr, Value))
    {
      Status = NOK;
    }
  
  return (Status);
}
#endif

#if defined(MDB_FUNCTIONCODE_07)
/**************************************************************************//**
*   \brief      This function provides Exception register
*   \param[out] Value Pointer to a varaiable which contains the value of the exception register
*   \return     OK if function is successful
*   \return     NOK if function is not successful
******************************************************************************/
t_status Modbus_ReadException(int* Value)
{
  t_status Status = OK;
  
  if (!Modbus_CB_GetException(Value))
    {
      Status = NOK;
    }
  
  return (Status);
}
#endif

