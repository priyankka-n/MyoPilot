#include <esp_now.h>  // Include the ESP-NOW library to handle peer-to-peer communication
#include <WiFi.h>     // Include the Wi-Fi library 


// Structure to receive data (matching the sender's data structure)
typedef struct struct_message {
    int id;            // ID to identify the data packet
    float temperature; // Temperature value
    float humidity;    // Humidity value
} struct_message;

struct_message receivedData; // Declare a variable of type struct_message to hold the received data

// Callback function to be called when data is received
void onDataReceived(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
    // Print a message indicating that data has been received
    Serial.println("Data received!");

    // info->des_addr contains the sender's MAC address. Sort of unneccesary
    Serial.print("Received from MAC: ");
    for (int i = 0; i < 6; i++) {
        Serial.print(info->des_addr[i], HEX);  // Print each byte of the MAC address in HEX
        if (i < 5) {
            Serial.print(":");  // Print a colon between MAC address bytes (except the last one)
        }
    }
    Serial.println();  // Print a new line after the MAC address

    // Copy the received data into the struct for further use
    memcpy(&receivedData, data, sizeof(receivedData));  // Copy the data into 'receivedData'

    // Print the received data. This part is to simply tell if the code is working
    Serial.print("Received ID: ");
    Serial.println(receivedData.id);            // Print the 'id' field
    Serial.print("Temperature: ");
    Serial.println(receivedData.temperature);   // Print the 'temperature' field
    Serial.print("Humidity: ");
    Serial.println(receivedData.humidity);      // Print the 'humidity' field
}

void setup() {
    Serial.begin(115200);  // Start serial communication at 115200 baud rate for debugging

    // Set the device mode to Wi-Fi station (no need to connect to an AP, just need to use ESP-NOW)
    WiFi.mode(WIFI_STA);   

    // Initialize ESP-NOW for communication
    if (esp_now_init() != ESP_OK) {  // Check if ESP-NOW initialization succeeds
        Serial.println("Error initializing ESP-NOW");  // Print an error if ESP-NOW fails to initialize
        return;  // Stop the setup process if initialization fails
    }

    // Register the callback function that handles incoming data
    esp_now_register_recv_cb(onDataReceived);  // Register the onDataReceived function to be called when data is received
}

void loop() {
    // The loop is empty because the receiving logic is handled by the callback function when data arrives
    // The receiver will simply wait for incoming data and process it in the onDataReceived callback
    delay(2000);  // Optional: Add a small delay for processing
}
