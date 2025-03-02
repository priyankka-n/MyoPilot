#include <TensorFlowLite_ESP32.h>


#include <Arduino.h>
#include <math.h>
#include <TensorFlowLite.h>  // TFLM Library
#include "model_data.h"      // AI Model
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Define EMG input pins
const int rightCheekPin = 34;  // ADC pin for right cheek
const int leftCheekPin = 35;   // ADC pin for left cheek
const int sampleSize = 50;     // Moving average sample size

float rightEMG[sampleSize];  // Array for EMG readings (right cheek)
float leftEMG[sampleSize];   // Array for EMG readings (left cheek)

// TensorFlow Lite Micro variables
const int tensor_arena_size = 8 * 1024;  // Memory allocation for model
uint8_t tensor_arena[tensor_arena_size];

tflite::MicroInterpreter* interpreter;
TfLiteTensor* input;
TfLiteTensor* output;

// Movement Labels
enum Movements {STOP = 0, LEFT = 1, RIGHT = 2, FORWARD = 3};

// Function to preprocess EMG signals
void processEMG(float& mavRight, float& rmsRight, int& zcrRight, 
                float& mavLeft, float& rmsLeft, int& zcrLeft) {
    float sumRight = 0, sumLeft = 0;
    int zcrCountRight = 0, zcrCountLeft = 0;
    float prevRight = 0, prevLeft = 0;

    for (int i = 0; i < sampleSize; i++) {
        rightEMG[i] = abs(analogRead(rightCheekPin) - 2048); // Read & Normalize
        leftEMG[i] = abs(analogRead(leftCheekPin) - 2048); 

        sumRight += rightEMG[i];
        sumLeft += leftEMG[i];

        // Zero Crossing Rate (ZCR)
        if ((rightEMG[i] > 0 && prevRight < 0) || (rightEMG[i] < 0 && prevRight > 0)) {
            zcrCountRight++;
        }
        if ((leftEMG[i] > 0 && prevLeft < 0) || (leftEMG[i] < 0 && prevLeft > 0)) {
            zcrCountLeft++;
        }

        prevRight = rightEMG[i];
        prevLeft = leftEMG[i];
    }

    mavRight = sumRight / sampleSize;
    rmsRight = sqrt(sumRight / sampleSize);
    mavLeft = sumLeft / sampleSize;
    rmsLeft = sqrt(sumLeft / sampleSize);
    zcrRight = zcrCountRight;
    zcrLeft = zcrCountLeft;
}

// Function to classify movement using AI model
Movements classifyMovement(float mavRight, float rmsRight, int zcrRight, 
                           float mavLeft, float rmsLeft, int zcrLeft) {
    input->data.f[0] = mavRight;
    input->data.f[1] = rmsRight;
    input->data.f[2] = zcrRight;
    input->data.f[3] = mavLeft;
    input->data.f[4] = rmsLeft;
    input->data.f[5] = zcrLeft;

    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("AI Inference Failed!");
        return STOP;
    }

    int predicted = output->data.f[0];
    return static_cast<Movements>(predicted);
}

void setup() {
    Serial.begin(115200);
    pinMode(rightCheekPin, INPUT);
    pinMode(leftCheekPin, INPUT);

    // Load TensorFlow Lite Micro Model
    static tflite::AllOpsResolver resolver;
    static tflite::MicroInterpreter static_interpreter(
        tflite::GetModel(model_data), resolver, tensor_arena, tensor_arena_size);

    interpreter = &static_interpreter;
    if (interpreter->AllocateTensors() != kTfLiteOk) {
        Serial.println("Tensor allocation failed!");
        while (1);
    }

    input = interpreter->input(0);
    output = interpreter->output(0);
}

void loop() {
    float mavRight, rmsRight, mavLeft, rmsLeft;
    int zcrRight, zcrLeft;

    // Process EMG Signals
    processEMG(mavRight, rmsRight, zcrRight, mavLeft, rmsLeft, zcrLeft);

    // Run AI Inference
    Movements move = classifyMovement(mavRight, rmsRight, zcrRight, mavLeft, rmsLeft, zcrLeft);

    // Print Movement Prediction
    Serial.print("Predicted Movement: ");
    switch (move) {
        case STOP: Serial.println("STOP"); break;
        case LEFT: Serial.println("LEFT"); break;
        case RIGHT: Serial.println("RIGHT"); break;
        case FORWARD: Serial.println("FORWARD"); break;
    }

    delay(500); // Adjust delay as needed
}
