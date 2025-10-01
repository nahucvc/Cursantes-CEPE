/*
 * SimpleMotionDetection.ino - Simple motion detection for LD2420 Radar Sensor
 * 
 * This example only displays "Motion detected at XXcm" when the distance value changes.
 * No repeated messages for the same distance.
 * 
 * Hardware connections:
 * - LD2420 VCC -> 3.3V or 5V
 * - LD2420 GND -> GND  
 * - LD2420 TX  -> Pin 8 (RX of SoftwareSerial)
 * - LD2420 RX  -> Pin 9 (TX of SoftwareSerial)
 * 
 * Author: cyrixninja
 * Date: July 22, 2025
 */

#include <SoftwareSerial.h>
#include "LD2420.h"

// Define RX and TX pins for SoftwareSerial
#define RX_PIN 8
#define TX_PIN 9

// Create instances
SoftwareSerial sensorSerial(RX_PIN, TX_PIN);
LD2420 radar;  // Use default constructor

// Track last distance to detect changes
int lastDistance = -1;
bool wasDetecting = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("=== Simple Motion Detection ===");
  
  // Initialize SoftwareSerial for LD2420
  sensorSerial.begin(115200);
  
  // Initialize the radar sensor
  if (radar.begin(sensorSerial)) {
    Serial.println("Radar ready. Waiting for motion...");
  } else {
    Serial.println("Failed to initialize radar!");
    while (1) delay(1000);
  }
  
  // Configure sensor
  radar.setDistanceRange(0, 600);
  radar.setUpdateInterval(50); // 20Hz update rate
}

void loop() {
  radar.update();  // Update radar readings
  
  // Check if motion is detected
  bool isDetecting = radar.isDetecting();
  int currentDistance = radar.getDistance();
  
  if (isDetecting) {
    // Only print when distance changes
    if (currentDistance != lastDistance) {
      Serial.print("Motion detected at ");
      Serial.print(currentDistance);
      Serial.println("cm");
      
      lastDistance = currentDistance;
      wasDetecting = true;
    }
  } else {
    // Motion stopped - reset for next detection
    if (wasDetecting) {
      lastDistance = -1;
      wasDetecting = false;
    }
  }
  
  delay(10);
}