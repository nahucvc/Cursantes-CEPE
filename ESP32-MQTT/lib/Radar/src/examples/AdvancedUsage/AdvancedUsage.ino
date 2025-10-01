/*
 * AdvancedUsage.ino - Advanced example for LD2420 Radar Sensor Library
 * 
 * This example demonstrates advanced features of the LD2420 library including:
 * - Multiple detection zones
 * - Data filtering
 * - Configuration management
 * - Error handling
 * 
 * Hardware connections:
 * - LD2420 VCC -> 3.3V or 5V
 * - LD2420 GND -> GND  
 * - LD2420 TX  -> Pin 8 (RX of SoftwareSerial)
 * - LD2420 RX  -> Pin 9 (TX of SoftwareSerial)
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

// Detection zones
struct DetectionZone {
  int minDistance;
  int maxDistance;
  String name;
  bool isActive;
  unsigned long lastDetection;
};

DetectionZone zones[] = {
  {0, 50, "Close Range", false, 0},
  {51, 150, "Medium Range", false, 0},
  {151, 300, "Far Range", false, 0}
};

const int NUM_ZONES = sizeof(zones) / sizeof(zones[0]);

// Data filtering
const int FILTER_SIZE = 5;
int distanceFilter[FILTER_SIZE];
int filterIndex = 0;
bool filterFull = false;

// Configuration
unsigned long statusInterval = 5000; // Print status every 5 seconds
unsigned long lastStatusPrint = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("=== LD2420 Advanced Example ===");
  
  // Initialize SoftwareSerial for LD2420
  sensorSerial.begin(115200);
  Serial.println("SoftwareSerial initialized on RX:8, TX:9");
  
  // Initialize the radar sensor
  if (radar.begin(sensorSerial)) {
    Serial.println("✓ LD2420 initialized successfully!");
  } else {
    Serial.println("❌ Failed to initialize LD2420!");
    while (1) delay(1000);
  }
  
  // Configure sensor
  radar.setDistanceRange(0, 400);
  radar.setUpdateInterval(50);
  
  // Set up callbacks
  radar.onDetection(onDetectionEvent);
  radar.onStateChange(onStateChangeEvent);
  radar.onDataUpdate(onDataUpdateEvent);
  
  // Initialize filter
  initializeFilter();
  
  Serial.println("Setup complete. Monitoring detection zones...");
  printZoneInfo();
}

void loop() {
  radar.update();  // Update radar readings
  
  // Check zone status
  updateZones();
  
  // Print periodic status
  if (millis() - lastStatusPrint > statusInterval) {
    printDetailedStatus();
    lastStatusPrint = millis();
  }
  
  delay(10);
}

// Initialize the distance filter
void initializeFilter() {
  for (int i = 0; i < FILTER_SIZE; i++) {
    distanceFilter[i] = 0;
  }
  filterIndex = 0;
  filterFull = false;
}

// Add a value to the filter and return the filtered result
int addToFilter(int newValue) {
  distanceFilter[filterIndex] = newValue;
  filterIndex = (filterIndex + 1) % FILTER_SIZE;
  
  if (!filterFull && filterIndex == 0) {
    filterFull = true;
  }
  
  // Calculate average
  int sum = 0;
  int count = filterFull ? FILTER_SIZE : filterIndex;
  
  for (int i = 0; i < count; i++) {
    sum += distanceFilter[i];
  }
  
  return count > 0 ? sum / count : 0;
}

// Update detection zones
void updateZones() {
  bool isDetecting = radar.isDetecting();
  int currentDistance = radar.getDistance();
  
  for (int i = 0; i < NUM_ZONES; i++) {
    bool wasActive = zones[i].isActive;
    
    // Check if object is in this zone
    if (isDetecting && 
        currentDistance >= zones[i].minDistance && 
        currentDistance <= zones[i].maxDistance) {
      
      zones[i].isActive = true;
      zones[i].lastDetection = millis();
      
      // Print zone activation
      if (!wasActive) {
        Serial.print("🎯 Zone activated: ");
        Serial.print(zones[i].name);
        Serial.print(" (");
        Serial.print(currentDistance);
        Serial.println(" cm)");
      }
    } else {
      zones[i].isActive = false;
    }
  }
}

// Callback functions
void onDetectionEvent(int distance) {
  int filteredDistance = addToFilter(distance);
  
  Serial.print("📡 Raw: ");
  Serial.print(distance);
  Serial.print(" cm, Filtered: ");
  Serial.print(filteredDistance);
  Serial.println(" cm");
}

void onStateChangeEvent(LD2420_DetectionState oldState, LD2420_DetectionState newState) {
  Serial.print("🔄 State change: ");
  Serial.print(stateToString(oldState));
  Serial.print(" → ");
  Serial.println(stateToString(newState));
  
  // Reset all zones when no detection
  if (newState == LD2420_NO_DETECTION) {
    for (int i = 0; i < NUM_ZONES; i++) {
      zones[i].isActive = false;
    }
    Serial.println("🔄 All zones cleared");
  }
}

void onDataUpdateEvent(LD2420_Data data) {
  // This callback gets called for every data update
  // Use it for continuous monitoring or logging
  
  static unsigned long updateCounter = 0;
  updateCounter++;
  
  // Print data rate every 100 updates
  if (updateCounter % 100 == 0) {
    static unsigned long lastRateCheck = 0;
    unsigned long now = millis();
    
    if (lastRateCheck > 0) {
      float rate = 100000.0 / (now - lastRateCheck); // Updates per second
      Serial.print("📊 Data rate: ");
      Serial.print(rate, 1);
      Serial.println(" Hz");
    }
    lastRateCheck = now;
  }
}

// Convert detection state to string
String stateToString(LD2420_DetectionState state) {
  switch (state) {
    case LD2420_NO_DETECTION: return "No Detection";
    case LD2420_DETECTION_ACTIVE: return "Active Detection";
    case LD2420_DETECTION_LOST: return "Detection Lost";
    default: return "Unknown";
  }
}

// Print zone information
void printZoneInfo() {
  Serial.println("\n=== Detection Zones ===");
  for (int i = 0; i < NUM_ZONES; i++) {
    Serial.print(zones[i].name);
    Serial.print(": ");
    Serial.print(zones[i].minDistance);
    Serial.print("-");
    Serial.print(zones[i].maxDistance);
    Serial.println(" cm");
  }
  Serial.println("=====================\n");
}

// Print detailed status
void printDetailedStatus() {
  Serial.println("\n--- Detailed Status ---");
  
  LD2420_Data currentData = radar.getCurrentData();
  
  Serial.print("Target detected: ");
  Serial.println(radar.isDetecting() ? "Yes" : "No");
  
  Serial.print("Distance: ");
  Serial.print(radar.getDistance());
  Serial.println(" cm");
  
  Serial.print("State: ");
  Serial.println(stateToString(radar.getState()));
  
  Serial.print("Data valid: ");
  Serial.println(radar.isDataValid() ? "Yes" : "No");
  
  Serial.print("Last update: ");
  Serial.print(radar.getLastUpdateTime());
  Serial.println(" ms ago");
  
  Serial.println("\nZone Status:");
  for (int i = 0; i < NUM_ZONES; i++) {
    Serial.print("  ");
    Serial.print(zones[i].name);
    Serial.print(": ");
    
    if (zones[i].isActive) {
      Serial.print("ACTIVE (");
      Serial.print(millis() - zones[i].lastDetection);
      Serial.println(" ms ago)");
    } else {
      Serial.println("Inactive");
    }
  }
  
  Serial.println("---------------------\n");
}