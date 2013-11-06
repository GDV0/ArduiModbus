
/*
  Modbus_RTU library
  Example of Mobus RTU Function code 16: Write Multiple Registers
  Copyright (C) 2012  Gilles DE VOS

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

#include <Modbus_RTU.h>

// Create Client and Server devices
Modbus_RTU myServer = Modbus_RTU(0);
Modbus_RTU myClient = Modbus_RTU(0);

// Define  message data buffers 
Modbus_Frame myFrame;
Modbus_Data myData;

unsigned short CRC16;

t_baud Baudrate;
unsigned long MsgTimeout;
int i;

// Registers (1 to 65536)
int DeviceObj10 = 0;
int DeviceObj11 = 0;
int DeviceObj12 = 0;
int DeviceObj13 = 0;
int DeviceObj14 = 0;

void setup()
{
  // Force type for each device
  myServer.SetType(MDB_SERVER);
  myClient.SetType(MDB_CLIENT);
 
  // Preset Server address
  myServer.Server_SetAddress(5);

  // Initialize serial line
  myClient.GetBaudrate(&Baudrate);
  Serial.begin(Baudrate);
  
  // Get the inter-frame time (equivalent to 3,5 char)
  myClient.GetFrameTimeout(&MsgTimeout);
  
  Serial.println("");
  Serial.println("Test Modbus_RTU library");
  Serial.println("=======================");
 
  // Modbus test type 
  Serial.println("");
  Serial.println("   Test Function code 16: Write Multiple Registers");
  Serial.println("   -----------------------------------------------");
}

void loop()
{
  Serial.println("");
  Serial.println(" --> Read 5 registers from address 10");
  // Build Client request
  Serial.println("");
  Serial.println("  Request sent by the Client");
  myClient.Client_ReadHoldingRegisters(5, 10, 5, &myFrame);
  DisplayFrame(&myFrame);
    
  // Build Server response
  if (myServer.Server_Update(&myFrame))
  {
    Serial.println("  --> OK Response available");
    Serial.println("");
    Serial.println("  Packet sent by the Server");
    DisplayFrame(&myFrame);
    
    // extract Data received by the Client
    myClient.Client_Update(&myFrame, &myData);
    Serial.println("");
    Serial.println("  Data");
    DisplayData(&myData);
  }
  else
    Serial.println("  --> No response available");

  Serial.println("");
  Serial.println(" --> Write 5 registers from address 10");
  // 5 registers from address 10
  myData.length = 5;
  myData.data[0] = 0x1111;
  myData.data[1] = 0x2222;
  myData.data[2] = 0x3333;
  myData.data[3] = 0x4444;
  myData.data[4] = 0x5555;
  myClient.Client_PresetMultipleRegisters(5, 10, &myData, &myFrame);
    Serial.println("");
    Serial.println("  Request sent by the Client");
  DisplayFrame(&myFrame);
  
  if (myServer.Server_Update(&myFrame))
  {
    Serial.println(" OK Response available");
    Serial.println("");
    Serial.println("  Packet sent by the Server");
    DisplayFrame(&myFrame);
    myClient.Client_Update(&myFrame, &myData);
    Serial.println("");
    Serial.println("  Data");
    DisplayData(&myData);
  }
  else
    Serial.println(" No response available");
  
  Serial.println("");
  Serial.println(" --> Read 5 registers from address 10");
  Serial.println("     Result should be 0x1111, 0x2222, 0x3333, 0x4444, 0x5555");
  
  // 5 register from address 10
  myClient.Client_ReadHoldingRegisters(5, 10, 5, &myFrame);
    Serial.println("");
    Serial.println("  Request sent by the Client");
  DisplayFrame(&myFrame);
  if (myServer.Server_Update(&myFrame))
  {
    Serial.println("  --> OK Response available");
    Serial.println("");
    Serial.println("  Packet sent by the Server");
    DisplayFrame(&myFrame);
    myClient.Client_Update(&myFrame, &myData);
    Serial.println("");
    Serial.println("  Data");
    DisplayData(&myData);
  }
  else
    Serial.println("  --> No response available");
  while(1)
  {
  }
}

// Function to display a complete frame (Debug mode)
void DisplayFrame(Modbus_Frame* msg)
{
  int i;
  
  Serial.print("  Frame size ");
  Serial.print(msg->length, DEC);
  Serial.print(" -> ");
  if (msg->length > 0)
  {
    for (i = 0; i < msg->length; i++)
    {
      Serial.print((unsigned char)(msg->data[i])>>4, HEX); 
      Serial.print((unsigned char)(msg->data[i])&0x0F, HEX); 
      Serial.print(" ");
    }  
  Serial.println();
  }
}

// Function to display Data received
void DisplayData(Modbus_Data* Data)
{
  int i;
  
  Serial.print("    ==> Number of data received = ");
  Serial.println(Data->length, DEC);
  if (Data->length > 0)
  {
    Serial.print("        Data type = ");
    switch (Data->type)
    {
      case MDB_BIT:
          Serial.println("BIT");
          Serial.print("        Data = ");
          for (i = 0; i < Data->length; i++)
          {
            Serial.print(Data->data[i] & 1, DEC);
            Serial.print((Data->data[i] & 2)>>1, DEC);
            Serial.print((Data->data[i] & 4)>>2, DEC);
            Serial.print((Data->data[i] & 8)>>3, DEC);
            Serial.print((Data->data[i] & 18)>>4, DEC);
            Serial.print((Data->data[i] & 32)>>5, DEC);
            Serial.print((Data->data[i] & 64)>>6, DEC);
            Serial.print((Data->data[i] & 128)>>7, DEC);
          }
          break;
      case MDB_BYTE:
          Serial.println("BYTE");
          Serial.print("        Data = ");
          for (i = 0; i < Data->length; i++)
          {
            Serial.print("0x"); 
            Serial.print((unsigned char)(Data->data[i])>>4, HEX); 
            Serial.print((unsigned char)(Data->data[i])&0x0F, HEX); 
            Serial.print(" ");
          }
          break;
      case MDB_WORD:
          Serial.println("WORD");
          Serial.print("        Data = ");
          for (i = 0; i < Data->length; i++)
          {
            Serial.print("0x"); 
            Serial.print((unsigned char)(Data->data[i*2])>>4, HEX); 
            Serial.print((unsigned char)(Data->data[i*2])&0x0F, HEX); 
            Serial.print((unsigned char)(Data->data[i*2+1])>>4, HEX); 
            Serial.print((unsigned char)(Data->data[i*2+1])&0x0F, HEX); 
            Serial.print(" ");
          }
          break;
      default:
          Serial.println("Unknown");
          break;
    }
  Serial.println();
  }
}

void DisplayDataOnly(Modbus_Data* Data)
{
  int i;
  if (Data->length > 0)
  {
    for (i = 0; i < Data->length; i++)
    {
      if (Data->type == MDB_BIT)
      {
        Serial.print(Data->data[i] & 1, DEC);
        Serial.print((Data->data[i] & 2)>>1, DEC);
        Serial.print((Data->data[i] & 4)>>2, DEC);
        Serial.print((Data->data[i] & 8)>>3, DEC);
        Serial.print((Data->data[i] & 18)>>4, DEC);
        Serial.print((Data->data[i] & 32)>>5, DEC);
        Serial.print((Data->data[i] & 64)>>6, DEC);
        Serial.print((Data->data[i] & 128)>>7, DEC);
      }
      if (Data->type == MDB_BYTE)
      {
        Serial.print("0x"); 
        Serial.print((unsigned char)(Data->data[i])>>4, HEX); 
        Serial.print((unsigned char)(Data->data[i])&0x0F, HEX); 
        Serial.print(" ");
      }
      if (Data->type == MDB_WORD)
      {
        Serial.print("0x"); 
        Serial.print((unsigned char)(Data->data[i*2])>>4, HEX); 
        Serial.print((unsigned char)(Data->data[i*2])&0x0F, HEX); 
        Serial.print((unsigned char)(Data->data[i*2+1])>>4, HEX); 
        Serial.print((unsigned char)(Data->data[i*2+1])&0x0F, HEX); 
        Serial.print(" ");
      }
      
    }  
  Serial.println();
  }
}


/******************************************************************************
*  Callback functions
*  Allow the user to define all device objects
******************************************************************************/

/******************************************************************************
* t_status Modbus_CB_SetRegister (unsigned short Addr, int* Value)
*     Callback function to write register value
* Parameters: 
*     - Addr: Address of the register
*     - Value: pointer to a variable which contain the register state
* Return value: 
*     - OK if register address exists
*     - NOK if register address doesn't exist
******************************************************************************/
t_status Modbus_CB_SetRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;
  
  // Device Address for Register = Modbus address + 1
  // Action to do regarding the device address
  switch (Addr)
  {
    //Volatile registers
    case 10:
        DeviceObj10 = *Value;
        break;
    case 11:
        DeviceObj11 = *Value;
        break;
    case 12:
        DeviceObj12 = *Value;
        break;
    case 13:
        DeviceObj13 = *Value;
        break;
    case 14:
        DeviceObj14 = *Value;
        break;
    default:
        Status = NOK;
      break;
  }
  return (Status);
}

/******************************************************************************
* t_status Modbus_CB_GetRegister (unsigned short Addr, int* Value)
*     Callback function to read register value
* Parameters: 
*     - Addr: Address of the register
*     - Value: pointer to a variable which will contain the register value
* Return value: 
*     - OK if register address exists
*     - NOK if register address doesn't exist
******************************************************************************/
t_status Modbus_CB_GetRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;
  
  // Device Address for Register = Modbus address + 1 
  // Action to do regarding the device address
  switch (Addr)
  {
    //Volatile registers (lost on Power cycle)
    case 10:
        *Value = DeviceObj10;
        break;
    case 11:
        *Value = DeviceObj11;
        break;
    case 12:
        *Value = DeviceObj12;
        break;
    case 13:
        *Value = DeviceObj13;
        break;
    case 14:
        *Value = DeviceObj14;
        break;
    default:
        Status = NOK;
        break;
  }
  return (Status);
}

