#include <Arduino.h>
#include <math.h>  // Required for sqrt() and abs()

// Define EMG input pins
const int rightCheekPin = 34;  // ADC pin for right cheek
const int leftCheekPin = 35;   // ADC pin for left cheek
const int sampleSize = 50;     // Moving average sample size

float rightEMG[sampleSize];  // Array to hold EMG readings for right cheek
float leftEMG[sampleSize];   // Array to hold EMG readings for left cheek

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
        // 🚀 Injecting fake EMG values instead of ADC readings
        rightEMG[i] = (i % 2 == 0) ? 1.2 : -2.5;  // Alternating values
        leftEMG[i] = (i % 2 == 0) ? 0.8 : -2.2;   // Alternating values

        sumRight += abs(rightEMG[i]);
        sumLeft += abs(leftEMG[i]);

        // Zero Crossing Rate (ZCR) calculation
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

    // ✅ Serial output to check processing
    Serial.print("MAV Right: "); Serial.print(mavRight, 2); Serial.print("\t");
    Serial.print("RMS Right: "); Serial.print(rmsRight, 2); Serial.print("\t");
    Serial.print("ZCR Right: "); Serial.print(zcrRight); Serial.print("\t");

    Serial.print("MAV Left: "); Serial.print(mavLeft, 2); Serial.print("\t");
    Serial.print("RMS Left: "); Serial.print(rmsLeft, 2); Serial.print("\t");
    Serial.print("ZCR Left: "); Serial.println(zcrLeft);

    delay(500);
}
