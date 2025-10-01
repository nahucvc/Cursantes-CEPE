# LD2420 Radar Sensor Library
Arduino library for the HLK LD2420 radar sensor that makes interaction easy and intuitive.

The **HLK-LD2420** is a high-performance 24GHz human presence and motion radar sensor module. It is designed for detecting motion, micro-motion, and stationary human bodies, making it suitable for intelligent IoT, automation, and smart home applications.

## Features

- ✅ Easy initialization with any Stream interface (Hardware/Software Serial)
- ✅ Automatic data parsing and validation  
- ✅ Configurable distance ranges and update intervals
- ✅ Event-driven callbacks for detections and state changes
- ✅ Built-in data filtering capabilities
- ✅ Support for multiple detection zones
- ✅ Comprehensive error handling
- ✅ Factory reset and restart functionality

## Hardware Requirements

- Arduino board (Uno, Nano, ESP32, etc.)
- HLK LD2420 radar sensor
- Connecting wires

## Installation

1. Download this library as a ZIP file
2. Open Arduino IDE
3. Go to **Sketch** → **Include Library** → **Add .ZIP Library...**
4. Select the downloaded ZIP file
5. Include the library in your sketch: `#include "LD2420.h"`

## Quick Start

### Arduino Uno
| LD2420 | Arduino Uno |
|--------|-------------|
| VCC    | 5V or 3.3V  |
| GND    | GND         |
| TX     | Pin 8 (RX)  |
| RX     | Pin 9 (TX)  |

![circuit](/assets/circuit.png)

**Arduino Example:**

```cpp
#include <SoftwareSerial.h>
#include "LD2420.h"

SoftwareSerial sensorSerial(8, 9); // RX, TX
LD2420 radar;

void setup() {
  Serial.begin(115200);
  sensorSerial.begin(115200);
  
  if (radar.begin(sensorSerial)) {
    Serial.println("Radar initialized!");
    radar.onDetection(onObjectDetected);
  }
}

void loop() {
  radar.update();
  delay(10);
}

void onObjectDetected(int distance) {
  Serial.print("Object at ");
  Serial.print(distance);
  Serial.println(" cm");
}
```

### NodeMCU (ESP8266) Example
| LD2420 | NodeMCU     |
|--------|-------------|
| VCC    | 3.3V        |
| GND    | GND         |
| TX     | D2 (GPIO4)  |
| RX     | D1 (GPIO5)  |

![circuit](/assets/circuit2.png)

**NodeMCU Example:**
```cpp
#include <SoftwareSerial.h>
#include "LD2420.h"

SoftwareSerial sensorSerial(D2, D1); // RX, TX
LD2420 radar;

void setup() {
  Serial.begin(115200);
  sensorSerial.begin(115200);
  
  if (radar.begin(sensorSerial)) {
    Serial.println("Radar initialized with Software Serial!");
    radar.onDetection(onObjectDetected);
  }
}

void loop() {
  radar.update();
  delay(10);
}

void onObjectDetected(int distance) {
  Serial.print("Object at ");
  Serial.print(distance);
  Serial.println(" cm");
}
```

## Examples

The library includes several examples:

- **BasicUsage**: Simple detection with callbacks
- **AdvancedUsage**: Multiple zones, filtering, and advanced features
- **SimpleMotionDetection**: Minimal example showing distance changes only



## API Reference

### Initialization

#### `bool begin(Stream& serial)`
Initialize the radar with default baud rate (115200).

#### `bool begin(Stream& serial, unsigned long baudRate)`
Initialize the radar with custom baud rate.

#### `void end()`
Disconnect from the radar sensor.

### Configuration

#### `void setDistanceRange(int minDistance, int maxDistance)`
Set the valid detection range in centimeters.

#### `void setUpdateInterval(unsigned long interval)`
Set how often to check for new data (in milliseconds).

#### `bool sendInitCommand()`
Send initialization command to the sensor.

#### `bool restart()`
Restart the sensor.

#### `bool factoryReset()`
Reset sensor to factory defaults.

### Data Reading

#### `void update()`
Check for new data. Call this regularly in your main loop.

#### `LD2420_Data getCurrentData()`
Get the complete current sensor data structure.

#### `int getDistance()`
Get the current distance reading in centimeters.

#### `LD2420_DetectionState getState()`
Get the current detection state.

#### `bool isDetecting()`
Check if an object is currently being detected.

#### `bool isDataValid()`
Check if the current data is valid.

### Callbacks

#### `void onDetection(LD2420_DetectionCallback callback)`
Set callback for when an object is detected.

```cpp
radar.onDetection([](int distance) {
  Serial.print("Detected at ");
  Serial.println(distance);
});
```

#### `void onStateChange(LD2420_StateChangeCallback callback)`
Set callback for detection state changes.

```cpp
radar.onStateChange([](LD2420_DetectionState oldState, LD2420_DetectionState newState) {
  Serial.println("State changed!");
});
```

#### `void onDataUpdate(LD2420_DataCallback callback)`
Set callback for every data update.

```cpp
radar.onDataUpdate([](LD2420_Data data) {
  // Process all data updates
});
```

### Utility Methods

#### `bool isInitialized()`
Check if the radar is properly initialized.

#### `String getVersionInfo()`
Get library version information.

## Data Structures

### LD2420_Data
```cpp
struct LD2420_Data {
  int distance;                    // Distance in cm
  LD2420_DetectionState state;     // Current detection state
  unsigned long timestamp;         // When the reading was taken
  bool isValid;                    // Whether the reading is valid
};
```

### LD2420_DetectionState
```cpp
enum LD2420_DetectionState {
  LD2420_NO_DETECTION = 0,
  LD2420_DETECTION_ACTIVE = 1,
  LD2420_DETECTION_LOST = 2
};
```

## Troubleshooting

### Common Issues

1. **No readings**: Check wiring and baud rate
2. **Invalid data**: Ensure proper power supply (3.3V)
3. **Intermittent readings**: Use data filtering for stable results

### Debug Tips

```cpp
// Check if sensor is responding
if (!radar.isInitialized()) {
  Serial.println("Sensor not initialized!");
}

// Check data validity
if (!radar.isDataValid()) {
  Serial.println("No valid data received");
}

// Monitor data age
LD2420_Data data = radar.getCurrentData();
unsigned long age = millis() - data.timestamp;
if (age > 1000) {
  Serial.println("Data is stale");
}
```

## Technical Specifications

| Parameter              | Typical Value     | Range/Notes                                                                                     |
|------------------------|------------------|-------------------------------------------------------------------------------------------------|
| **Operating Frequency**| 24GHz            | 24.00–24.25GHz                                                                                  |
| **Sweep Bandwidth**    | 0.25GHz          |                                                                                                 |
| **Supply Voltage**     | 3.3V             | 3.0–3.6V                                                                                        |
| **Operating Current**  | 50mA             | Average                                                                                         |
| **Detection Range**    | Up to 8m         | Wall-mounted: - Motion: 8m - Micro-motion: 6m  Ceiling: - Motion: 5m - Micro-motion: 4m |
| **Detection Accuracy** | ±0.35m           | Within 8m range                                                                                 |
| **Proximity Sensing**  | 0.2m minimum     | No blind zone                                                                                   |
| **Detection Angle**    | ±60°             | Wide area coverage                                                                              |
| **Data Refresh Rate**  | 10Hz             |                                                                                                 |
| **Module Size**        | 20mm × 20mm      |                                                                                                 |
| **Operating Temp.**    | -40°C to +85°C   |                                                                                                 |
| **Max Radiated Power** | 11dBm            |                                                                                                 |

## Contributing

Feel free to submit issues and pull requests to improve this library.