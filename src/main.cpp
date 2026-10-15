#include <Arduino.h>
#include "Motor.h"
#include "Wifi.h"

void setup() {
  Serial.begin(115200);
  motorInit();
  wifiInit();
}

void loop() {
  wifiHandleClient();
}
