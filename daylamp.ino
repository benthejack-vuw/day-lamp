#include "alarm_clock.h"

void setup() {
  Serial.begin(9600);
  alarm_setup();
}

void loop() {
  alarm_update();
}

