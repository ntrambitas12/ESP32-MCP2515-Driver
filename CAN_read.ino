#include "mcp2515.h"


struct can_frame canMsg;


/*Adjust these to match the ESP32 board*/
#define MOSI_PIN 18
#define MISO_PIN 19
#define SCLK_PIN 5
#define CS_PIN  13 // CS Pin for where MCP2515 connects to ESP32

MCP2515 mcp2515(MOSI_PIN, MISO_PIN, SCLK_PIN, CS_PIN);
void setup() {
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    //Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
}