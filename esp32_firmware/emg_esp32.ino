#include <Arduino.h>
#include "model_rules.h" // 🚀 Include the trained AI model

// Define EMG input pins
#define ADC_PIN1 32 // Left cheek
#define ADC_PIN2 33 // Right cheek

// Define parameters
const int sampleSize = 50;  // Matches feature extraction window
uint16_t leftSignal[sampleSize];
uint16_t rightSignal[sampleSize];

void setup() {
    Serial.begin(115200);
    pinMode(ADC_PIN1, INPUT);
    pinMode(ADC_PIN2, INPUT);
}

// Function to compute MAV, RMS, ZCR
void compute_features(float &mavLeft, float &rmsLeft, int &zcrLeft,
                      float &mavRight, float &rmsRight, int &zcrRight) {
    float sumLeft = 0, sumRight = 0;
    int zcrCountLeft = 0, zcrCountRight = 0;
    float prevLeft = 0, prevRight = 0;

    for (int i = 0; i < sampleSize; i++) {
        leftSignal[i] = abs(analogRead(ADC_PIN1) - 2048);
        rightSignal[i] = abs(analogRead(ADC_PIN2) - 2048);

        sumLeft += leftSignal[i];
        sumRight += rightSignal[i];

        if ((leftSignal[i] > 0 && prevLeft < 0) || (leftSignal[i] < 0 && prevLeft > 0)) {
            zcrCountLeft++;
        }
        if ((rightSignal[i] > 0 && prevRight < 0) || (rightSignal[i] < 0 && prevRight > 0)) {
            zcrCountRight++;
        }

        prevLeft = leftSignal[i];
        prevRight = rightSignal[i];
    }

    mavLeft = sumLeft / sampleSize;
    rmsLeft = sqrt(sumLeft / sampleSize);
    mavRight = sumRight / sampleSize;
    rmsRight = sqrt(sumRight / sampleSize);
    zcrLeft = zcrCountLeft;
    zcrRight = zcrCountRight;
}

void loop() {
    float mavLeft, rmsLeft, mavRight, rmsRight;
    int zcrLeft, zcrRight;

    // Compute features
    compute_features(mavLeft, rmsLeft, zcrLeft, mavRight, rmsRight, zcrRight);

    // Prepare feature array for model
    float X[6] = {mavLeft, rmsLeft, zcrLeft, mavRight, rmsRight, zcrRight};

    // Predict movement using AI model
    int movement = predict_movement(X);

    // Print prediction result
    Serial.print("Predicted Movement: ");
    switch (movement) {
        case 0: Serial.println("STOP"); break;
        case 1: Serial.println("LEFT"); break;
        case 2: Serial.println("RIGHT"); break;
        case 3: Serial.println("FORWARD"); break;
    }

    delay(500); // Adjust delay for stability
}
