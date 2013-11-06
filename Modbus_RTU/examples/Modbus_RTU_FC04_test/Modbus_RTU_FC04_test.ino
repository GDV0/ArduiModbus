
/*
  Modbus_RTU library
  Example of Mobus RTU Function code 04: Read Input registers
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

// Defines 1 Client and 1 Server devices
Modbus_RTU myServer = Modbus_RTU(0);
Modbus_RTU myClient = Modbus_RTU(0);

// Defines a message and data buffers 
Modbus_Frame myFrame;
Modbus_Data myData;

unsigned short CRC16;

t_baud Baudrate;
unsigned long MsgTimeout;
int i;

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
  Serial.println("   Test Function code 04: Read Input Registers");
  Serial.println("   -------------------------------------------");

  // configure the outputs
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
 }

void loop()
{
  Serial.println("");
  Serial.println("  --> Read 13 input registers from address 0");

  // Build Client request
  Serial.println("");
  Serial.println("  Request sent by the Client");
  myClient.Client_ReadInputRegisters(5, 0, 13, &myFrame);
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
* t_status Modbus_CB_GetInputRegister(unsigned short Addr, int* Value)
*     Callback function to read input register value
* Parameters: 
*     - Addr: Address of the input register
*     - Value: pointer to a variable which will contain the input register value
* Return value: 
*     - OK if register address exists
*     - NOK if register address doesn't exist
******************************************************************************/
t_status Modbus_CB_GetInputRegister(unsigned short Addr, int* Value)
{
  t_status Status = OK;
  
 // Value = f(Addr) To be defined by application
  if ((Addr >= 0) && (Addr <=15))  // for Arduino MEGA
    *Value = analogRead(Addr);
  else
    Status = NOK;
  return (Status);
}
