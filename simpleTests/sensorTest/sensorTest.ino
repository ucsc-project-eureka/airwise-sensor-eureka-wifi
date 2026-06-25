// Gives a current readout of every sensor's data on the UCSC Atmos Lab Airwise sensor V2.

#include <WiFi.h>
#include <esp_wifi.h>

// Setup pinouts --------------------------------------
// Use DEBUG_PORT for the Native Port
#define DEBUG_PORT SerialUSB
SFE_UBLOX_GNSS myGNSS;
#define SOIL_I2C 0x36

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

// From Airwise's ESP32 UART connections.
#define ESP_PIN_TX 8
#define ESP_PIN_RX 9

// Reference values for sensor data processing.
#define SEALEVELPRESSURE_HPA (1013.25)

// Reference all appropriate fields.
#define wirePort Wire               // I2C Bus port name.
Adafruit_BME680 bme(&wirePort);     // I2C
Adafruit_INA3221 ina3221;

void readMacAddress(){
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial.println("Failed to read MAC address");
  }
}

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.STA.begin();

  Serial.print("[DEFAULT] ESP32 Board MAC Address: ");
  readMacAddress();


}
 
void loop(){

}
