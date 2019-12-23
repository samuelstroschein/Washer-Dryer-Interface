
#include <neotimer.h> //Uses millis from hardware to create a Timer.


//Change these to match the pins on your Arduino - make sure theyre PWM capable
int redPin1 = 14;
int greenPin1 = 12;
int redPin2 = 4;
int greenPin2 = 5;

bool ledBlink;

//Timer
Neotimer blinkingInterval = Neotimer(750);         //Intervall in welchem die LED blinken soll

void setup(){
  pinMode(greenPin1, OUTPUT);
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(redPin2, OUTPUT);
  Serial.begin(9600);
}


void loop(){

  Serial.print("HELLO");
  analogWrite(greenPin1, 200);
  analogWrite(redPin1, 1000);
  analogWrite(greenPin2, 200);
  analogWrite(redPin2, 1000);
}


/*
void loop(){
  analogWrite(greenPin1, 0);
  analogWrite(redPin2, 0);
  delay(1000);
  analogWrite(greenPin1, 200);
  analogWrite(redPin2, 200);
  delay(1000);
  analogWrite(greenPin1, 400);
  analogWrite(redPin2, 400);
  delay(1000);
  analogWrite(greenPin1, 600);
  analogWrite(redPin2, 600);
  delay(1000);
  analogWrite(greenPin1, 800);
  analogWrite(redPin2, 800);
  delay(1000);
  analogWrite(greenPin1, 1000);
  analogWrite(redPin2, 1000);
  delay(1000);
}
*/


/*
void loop(){
    analogWrite(greenPin, 0);
    if (blinkingInterval.repeat()){
      ledBlink = !ledBlink;
    }
    if (ledBlink){
      analogWrite(greenPin, 200);
    } else {
      analogWrite(greenPin,0);
    }
  }
*/
