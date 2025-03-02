#include <esp_now.h>    // Include the ESP-NOW library for wireless communication
#include <WiFi.h>       // Include the Wi-Fi library
#define ADC_PIN1 32
#define ADC_PIN2 33

uint8_t counter;
uint8_t detector = 0x00;
uint16_t leftCount = 0;
uint16_t rightCount = 0;
uint16_t thresh = 400;
uint8_t minCount = 5;

// Receiver's MAC address
uint8_t receiverMac[] = {0x14, 0x2B, 0x2F, 0xD8, 0x60, 0x00}; // Replace with the MAC address of the receiver ESP32, this current one is for the ESP32 without pen on it.

// Structure to send data
typedef struct struct_message {
    int detector;            // data (2 bits)
} struct_message;

struct_message myData; // Declare a variable of type struct_message to hold the data to send

// Callback function to be called when data is sent
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void setup() {
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
    // Set device as Wi-Fi station (no AP connection needed)
    WiFi.mode(WIFI_STA); 

    // Initialize ESP-NOW for communication
    if (esp_now_init() != ESP_OK) {
        return;
    }

    // Register the callback function that handles the sending status
    esp_now_register_send_cb(onDataSent);

    // Register the peer (receiver) ESP32 to send data to
    esp_now_peer_info_t peerInfo = {}; // Initialize a structure to hold peer info
    memcpy(peerInfo.peer_addr, receiverMac, 6); // Copy the receiver's MAC address into the peer structure
    peerInfo.channel = 0; // Set the communication channel (0 means auto channel)
    peerInfo.encrypt = false; // Disable encryption (no encryption for this example)

    // Add the peer to ESP-NOW's peer list
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        return;
    }
}

void loop() {
  delay(4);
  detector = 0x00;
  
  uint16_t adcValue1 = analogRead(ADC_PIN1);
  uint16_t adcValue2 = analogRead(ADC_PIN2);

  // Print with printf-style formatting
//   Serial.printf("ADC1: %04d ADC2: %04d\n", adcValue1, adcValue2);

  if(adcValue1 > thresh){
    leftCount++;
  }
  if(adcValue2 > thresh){
    rightCount++;
  }
  if(counter >= 125){
    if(leftCount >= minCount){
      detector |= 0x01;
    }
    if(rightCount >= minCount){
      detector |= 0x02;
    }
    counter = 0; 
    Serial.printf("Detector = %03d\n",detector);
    
    if(detector & 0x01){
      digitalWrite(12,HIGH);
    } else {
      digitalWrite(12,LOW);
    }
    if(detector & 0x02){
      digitalWrite(13,HIGH);
    } else {
      digitalWrite(13,LOW);
    }
    leftCount=0;
    rightCount=0;
    myData.detector = detector;
    esp_err_t result = esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));
  
  } else {
    counter++;
  }

}
