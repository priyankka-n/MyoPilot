#define ADC_PIN1 32
#define ADC_PIN2 33

uint8_t counter;
uint8_t detector = 0x00;
uint16_t leftCount = 0;
uint16_t rightCount = 0;
uint16_t thresh = 400;
uint8_t minCount = 5;

void setup() {
  Serial.begin(115200);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


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
  } else {
    counter++;
  }
}