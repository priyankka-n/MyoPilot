#include <esp_now.h>  // Include the ESP-NOW library to handle peer-to-peer communication
#include <WiFi.h>     // Include the Wi-Fi library
#include <Stepper.h>

#define STEPS_PER_REV 2048  

// Define motor 1 pins (Left motor)
#define M1_IN1 14  // D14
#define M1_IN2 27  // D27
#define M1_IN3 26  // D26
#define M1_IN4 25  // D25

// Define motor 2 pins (Right motor)
#define M2_IN1 18  // D18
#define M2_IN2 19  // D19
#define M2_IN3 21  // D21
#define M2_IN4 23  // D23

Stepper stepper1(STEPS_PER_REV, M1_IN1, M1_IN3, M1_IN2, M1_IN4);
Stepper stepper2(STEPS_PER_REV, M2_IN1, M2_IN3, M2_IN2, M2_IN4);

// Structure to receive data (matching the sender's data structure)
typedef struct struct_message {
    int detector;            // data (2 bits)
} struct_message;

struct_message receivedData; // Declare a variable of type struct_message to hold the received data

// Callback function to be called when data is received
void onDataReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len) {

    // Copy the received data into the struct for further use
    memcpy(&receivedData, data, sizeof(receivedData));  // Copy the data into 'receivedData'
}

void setup() {
    // Set the device mode to Wi-Fi station (no need to connect to an AP, just need to use ESP-NOW)
    WiFi.mode(WIFI_STA);   

    // Initialize ESP-NOW for communication
    if (esp_now_init() != ESP_OK) {  // Check if ESP-NOW initialization succeeds
        return;  // Stop the setup process if initialization fails
    }

    // Register the callback function that handles incoming data
    esp_now_register_recv_cb(onDataReceived);  // Register the onDataReceived function to be called when data is received

    stepper1.setSpeed(10);
    stepper2.setSpeed(10);
}

void loop() {
    // The loop is empty because the receiving logic is handled by the callback function when data arrives
    // The receiver will simply wait for incoming data and process it in the onDataReceived callback
//    delay(1000);  // Optional: Add a small delay for processing
    int dataBits = receivedData.detector;
    int i;
    for(i=0;i<STEPS_PER_REV;i++){
      if((dataBits == 1) || (dataBits == 3)){
        stepper1.step(-1);
      }
      if((dataBits == 2) || (dataBits ==3)){
        stepper2.step(1);
      }
    }
    delay(500);
}
