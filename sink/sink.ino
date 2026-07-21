
/*
NOTE: This should be compiled with the ESP32S3 Dev Module with CDC on Boot enabled.
*/

#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#define MAX_SENSOR_NODES 3
#define TDMA_SLOT_TIME 1000
#define JOIN_REQUEST_TIMEOUT 3000
#define SENSOR_RESPONSE_TIMEOUT (TDMA_SLOT_TIME * MAX_SENSOR_NODES)
#define DEBUG_PORT Serial

uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t sinkMAC[6];
bool sinkMACKnown = false;

const unsigned long packetInterval = 3000;  // Time in milliseconds
unsigned long lastPacketSentTime = 0;

// Default C++ enum values are type int
enum messageType : uint8_t {
  DISCOVERY = 1,
  JOIN_REQUEST,
  TDMA_SCHEDULE,
  SENSOR_DATA,
  AGGREGATE_DATA
};

// Packet structures
struct discoveryPacket_t {
  uint8_t type;      // Packet type identifier
  uint8_t hopCount;  // Hop count away from the sink
  uint8_t roundCounter;
};

struct joinRequestPacket_t {
  uint8_t type;
};

struct tdmaSchedulePacket_t {
  uint8_t type;
  uint8_t macs[MAX_SENSOR_NODES][6];  // List of sensor node MACs
};

struct sensorDataPacket_t {
  uint8_t type;
  float temperature;
  float humidity;
  uint16_t soilMoisture;
  unsigned long timestamp;
};

struct aggregateDataPacket_t {
  uint8_t type;
  uint8_t macs[MAX_SENSOR_NODES][6];
  float temperatures[MAX_SENSOR_NODES];
  float humidities[MAX_SENSOR_NODES];
  uint16_t soilMoistures[MAX_SENSOR_NODES];
  unsigned long timestamps[MAX_SENSOR_NODES];
  uint8_t readingsCount;
};

// Global variables
unsigned long discoverySentTime = 0;

bool sentDiscovery = false;
bool waitingForAggPacket = false;

aggregateDataPacket_t aggData;

unsigned long startTime;
unsigned long currentTime;
unsigned long sendTime;

esp_now_peer_info_t peerInfo;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
