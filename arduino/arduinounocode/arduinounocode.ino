#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);  // RX, TX

//Outputs
int buzzerPin = 4;
int LedRedPin = 8;
int LedGreenPin = 9;
int LedYellowPin = 10;

int MAX_Gaz = 400;
int MIN_Flame = 420;


// Flame Sensor Module
int FlamePin = A0;  // This is our input pin
int flameValue;
// Gaz Sensor Module
int GazPin = A1;  // This is our input pin
int GazValue;

void playTone(int pin, int frequency, int duration) {
  const int toneDelay = 50;
  tone(pin, frequency, duration);
  delay(duration);
  noTone(pin);
  delay(toneDelay);  // Small delay between tones
}

void welcomeMessage() {
  int tones[] = {523, 587, 659, 880, 784}; // C5 D5 E5 A5 G5
  // Delay duration for each LED blink
  // Play tones and blink the LEDs
  for (int i = 0; i < sizeof(tones) / sizeof(tones[0]); i++) {
    digitalWrite(LedRedPin, HIGH);
    playTone(buzzerPin, tones[i], 100);
    digitalWrite(LedRedPin, LOW);

    digitalWrite(LedYellowPin, HIGH);
    playTone(buzzerPin, tones[i], 100);
    digitalWrite(LedYellowPin, LOW);

    digitalWrite(LedGreenPin, HIGH);
    playTone(buzzerPin, tones[i], 100);
    digitalWrite(LedGreenPin, LOW);
  }
}



void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

  pinMode(GazPin ,INPUT);
  pinMode(FlamePin ,INPUT);
  pinMode(LedRedPin ,OUTPUT);
  pinMode(LedGreenPin ,OUTPUT);
  pinMode(LedYellowPin ,OUTPUT);
  pinMode(buzzerPin ,OUTPUT);
  //The system isn't working due the initial run
  digitalWrite(LedGreenPin, LOW);


  // Call the welcome message function
  welcomeMessage();

}

unsigned long lastUpdate = millis();
String TurnAlert = "Off";
int detectionCount=0;
int lastDetectionCount=0;unsigned long lastDetectionDate=millis();
void loop() {

  if (mySerial.available()) {
    TurnAlert = mySerial.readString();
    Serial.print(TurnAlert + " : ");

    flameValue = analogRead(FlamePin);
    GazValue = analogRead(GazPin);

    if(TurnAlert.indexOf("On") >= 0){
      digitalWrite(LedYellowPin, LOW);
      digitalWrite(LedGreenPin, HIGH);
    }else{                              //The alert is disabled
      digitalWrite(LedYellowPin, HIGH);
      digitalWrite(LedGreenPin, LOW);
    }


    if ((GazValue >= MAX_Gaz) || (flameValue < MIN_Flame)) {
      Serial.println(" : LEAKING ALERT !!!!!!");
      if(millis() - lastDetectionDate < 10000){
        detectionCount=lastDetectionCount+1;
      }else{
        detectionCount++;
      }

      if(TurnAlert.equalsIgnoreCase("On")==0){
        //RUN THE ALERT
        digitalWrite(LedRedPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
      }
    }else{
      
      digitalWrite(LedRedPin, LOW);
      digitalWrite(buzzerPin, LOW);
      detectionCount=0;
    }
    


      Serial.println("flame=" + String(flameValue) + "&gaz="+ String(GazValue) + "&detectionCount="+ String(detectionCount)+ "&TurnAlert="+String(TurnAlert));
      mySerial.println("flame=" + String(flameValue) 
                      + "&gaz="+ String(GazValue) 
                      + "&detectionCount="+ String(detectionCount)
                      + "&TurnAlert="+String(TurnAlert));
      Serial.println(" > Sent to ESP");
    
  }else{
    //The system isn't working due an error
  }
}
