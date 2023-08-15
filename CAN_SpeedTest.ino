#include <mcp2515.h>
 
struct can_frame canMsg;
/*Adjust these to match the ESP32 board*/
#define MOSI_PIN 18
#define MISO_PIN 19
#define SCLK_PIN 5
#define CS_PIN  13 // CS Pin for where MCP2515 connects to ESP32

MCP2515 mcp2515(MOSI_PIN, MISO_PIN, SCLK_PIN, CS_PIN);
int cntr = 0;
unsigned long oldTime = 0;
 
 
void setup() {
  Serial.begin(115200);
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
 
  Serial.println("------- CAN Speedtest ----------");
}
 
void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    cntr++;
  }
 
  if ((millis()-oldTime)>1000) {
    oldTime = millis();
    Serial.print(cntr);
    Serial.println(" msg/sec");
    cntr = 0;      
  }
}
