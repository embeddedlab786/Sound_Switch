#include <EEPROM.h>

#define Sensor A0 // Sound Sensor Pin
#define Relay 8 // Load Control Pin

// Variable to store the time when last event happened
unsigned long lastEvent = 0;
int relayState = 0;    // Variable to store the state of relay

void setup() { // put your setup code here, to run once:
  
pinMode(Sensor, INPUT);  // Set sensor pin as an INPUT
pinMode(Relay, OUTPUT);  // Set relay pin as an OUTPUT pin

relayState = EEPROM.read(1);
digitalWrite(Relay, relayState);
delay(1000); // Waiting for a while
}

void loop() {
int sensorData = digitalRead(Sensor); // Read Sound sensor
  
// If pin goes LOW, sound is detected
if (sensorData == LOW) {
  // If 25ms have passed since last LOW state, it means that
  // the clap is detected and not due to any spurious sounds
  if (millis() - lastEvent > 25) { //toggle relay and set the output
  relayState = !relayState;
  EEPROM.write(1, relayState); 
  digitalWrite(Relay, relayState);
  delay(500);
  }

  // Remember when last event happened
  lastEvent = millis();
 }
}
