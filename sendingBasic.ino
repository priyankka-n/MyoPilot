#include <esp_now.h>    // Include the ESP-NOW library for wireless communication
#include <WiFi.h>       // Include the Wi-Fi library

// Receiver's MAC address
uint8_t receiverMac[] = {0x14, 0x2B, 0x2F, 0xD8, 0x60, 0x00}; // Replace with the MAC address of the receiver ESP32, this current one is for the ESP32 without pen on it.

// Structure to send data
typedef struct struct_message {
    int id;            // ID to identify the data packet
    float temperature; // Temperature value to be sent
    float humidity;    // Humidity value to be sent
} struct_message;

struct_message myData; // Declare a variable of type struct_message to hold the data to send

// Callback function to be called when data is sent
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Delivery status: ");
    // Print whether the data was sent successfully or not
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
    Serial.begin(115200); // Start serial communication at 115200 baud rate

    // Set device as Wi-Fi station (no AP connection needed)
    WiFi.mode(WIFI_STA); 

    // Initialize ESP-NOW for communication
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW"); // Print an error if ESP-NOW fails to initialize
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
        Serial.println("Failed to add peer"); // Print an error if the peer could not be added
        return;
    }
}

void loop() {
    // Set data values for the message
    myData.id = 1; // Set the ID for the data (could be used to identify the message type or sender)
    myData.temperature = random(20, 30) + random(0, 100) / 100.0; // Generate a random temperature between 20-30
    myData.humidity = random(40, 60) + random(0, 100) / 100.0; // Generate a random humidity between 40-60

    // Send the data using ESP-NOW to the receiver
    esp_err_t result = esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));

    // Check if the data was sent successfully
    if (result == ESP_OK) {
        Serial.println("Sent with success"); // Print success message
    } else {
        Serial.println("Error sending the data"); // Print error message if data send failed
    }

    delay(2000); // Wait for 2 seconds before sending the next data
}
