#include <AsyncUDP.h>

#include <dummy.h>

#include <dummy.h>

const int rightCheekPin = A0;  // Right cheek EMG
const int leftCheekPin = A1;   // Left cheek EMG
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
        rightEMG[i] = analogRead(rightCheekPin) * (3.3 / 4095.0);
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

    // Send formatted data: rightMAV, rightRMS, rightZCR, leftMAV, leftRMS, leftZCR
    Serial.print(mavRight);
    Serial.print(",");
    Serial.print(rmsRight);
    Serial.print(",");
    Serial.print(zcrRight);
    Serial.print(",");
    Serial.print(mavLeft);
    Serial.print(",");
    Serial.print(rmsLeft);
    Serial.print(",");
    Serial.println(zcrLeft);

    delay(50);
}
