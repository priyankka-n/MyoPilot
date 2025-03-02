/*#include <AsyncUDP.h>  // Required for ESP32 UDP communication (if used)

// Simulated Fake EMG Signal Generator (For Testing Without Hardware)

// Define virtual analog input pins
const int rightCheekPin = 36;  // GPIO36 (VP) - Right cheek EMG
const int leftCheekPin = 39;   // GPIO39 (VN) - Left cheek EMG

const int sampleSize = 50;     // Moving average sample size

float rightEMG[sampleSize];
float leftEMG[sampleSize];

void setup() {
    Serial.begin(115200);  // Start Serial Monitor
    pinMode(rightCheekPin, INPUT);
    pinMode(leftCheekPin, INPUT);
}

void loop() {
    float sumRight = 0, sumLeft = 0;
    int zcrRight = 0, zcrLeft = 0;
    float prevRight = 0, prevLeft = 0;

    Serial.println("----- NEW EMG READING -----");

    for (int i = 0; i < sampleSize; i++) {
        // 🚀 Fake EMG Data (Now Including Negative Values!)
        rightEMG[i] = (random(-3000, 3000) / 1000.0);  
        leftEMG[i] = (random(-3000, 3000) / 1000.0);  

        Serial.print("Raw Right: ");
        Serial.print(rightEMG[i]);
        Serial.print("\t Raw Left: ");
        Serial.println(leftEMG[i]);

        sumRight += abs(rightEMG[i]);
        sumLeft += abs(leftEMG[i]);

        // Zero Crossing Rate (ZCR) Calculation - Now Works!
        if ((rightEMG[i] > 0 && prevRight < 0) || (rightEMG[i] < 0 && prevRight > 0)) {
            zcrRight++;
        }
        if ((leftEMG[i] > 0 && prevLeft < 0) || (leftEMG[i] < 0 && prevLeft > 0)) {
            zcrLeft++;
        }

        prevRight = rightEMG[i];
        prevLeft = leftEMG[i];
    }

    float mavRight = sumRight / sampleSize;
    float rmsRight = sqrt(sumRight / sampleSize);
    float mavLeft = sumLeft / sampleSize;
    float rmsLeft = sqrt(sumLeft / sampleSize);

    // 🚀 Print Debug Data
    Serial.print("MAV Right: ");
    Serial.print(mavRight);
    Serial.print("\t RMS Right: ");
    Serial.print(rmsRight);
    Serial.print("\t ZCR Right: ");
    Serial.print(zcrRight);

    Serial.print("\t MAV Left: ");
    Serial.print(mavLeft);
    Serial.print("\t RMS Left: ");
    Serial.print(rmsLeft);
    Serial.print("\t ZCR Left: ");
    Serial.println(zcrLeft);

    delay(500);
}
*/

#include <Arduino.h>

// Define EMG input pins
const int rightCheekPin = 34;  // ADC pin for right cheek
const int leftCheekPin = 35;   // ADC pin for left cheek
const int sampleSize = 50;     // Moving average sample size

float rightEMG[sampleSize];
float leftEMG[sampleSize];

void setup() {
    Serial.begin(115200);
    pinMode(rightCheekPin, INPUT);
    pinMode(leftCheekPin, INPUT);
}

void loop() {
    float sumRight = 0, sumLeft = 0;
    int zcrRight = 0, zcrLeft = 0;
    float prevRight = 0, prevLeft = 0;

    for (int i = 0; i < sampleSize; i++) {
        rightEMG[i] = analogRead(rightCheekPin) * (3.3 / 4095.0); // Convert ADC to voltage
        leftEMG[i] = analogRead(leftCheekPin) * (3.3 / 4095.0);

        sumRight += abs(rightEMG[i]);
        sumLeft += abs(leftEMG[i]);

        // Zero Crossing Rate (ZCR)
        if ((rightEMG[i] > 0 && prevRight < 0) || (rightEMG[i] < 0 && prevRight > 0)) {
            zcrRight++;
        }
        if ((leftEMG[i] > 0 && prevLeft < 0) || (leftEMG[i] < 0 && prevLeft > 0)) {
            zcrLeft++;
        }

        prevRight = rightEMG[i];
        prevLeft = leftEMG[i];
    }

    float mavRight = sumRight / sampleSize;
    float rmsRight = sqrt(sumRight / sampleSize);
    float mavLeft = sumLeft / sampleSize;
    float rmsLeft = sqrt(sumLeft / sampleSize);

    // Send formatted data: Right_MAV, Right_RMS, Right_ZCR, Left_MAV, Left_RMS, Left_ZCR
    Serial.print(mavRight); Serial.print(",");
    Serial.print(rmsRight); Serial.print(",");
    Serial.print(zcrRight); Serial.print(",");
    Serial.print(mavLeft); Serial.print(",");
    Serial.print(rmsLeft); Serial.print(",");
    Serial.println(zcrLeft);

    delay(50);
}
