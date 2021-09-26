// project link at tinkercad: https://www.tinkercad.com/things/fbTCX6CvjIo-touchless-handwash/editel
#include <Servo.h>



Servo myservo;
Servo bigServo;

const int sonar1Big = 9;
const int sonar2Small = 7;
const int inputPir = 8;
const int relay1Small = 3;
int relay2 = 10;
int tempPin = 1;
int ledRed = 2;
int ledYellow = 4;
int ledGreen = 6;
//int servo2 = ;
  
void setup() {
  Serial.begin(9600);
  myservo.attach(5);
  bigServo.attach(11);
  myservo.write(0);
  bigServo.write(0);
  pinMode(inputPir,INPUT);
  pinMode(sonar1Big,OUTPUT);
  pinMode(sonar2Small,OUTPUT);
  pinMode(relay1Small,OUTPUT);
  pinMode(relay2,OUTPUT);
  analogReference(DEFAULT);
  //pinMode(tempPin,INPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledGreen,OUTPUT);
}

void loop() {
  ledOff();
  int tempVal = analogRead(tempPin);
  
  int celsius = map(((tempVal - 20) * 3.04), 0, 1023, -40, 125);
  // convert to Fahrenheit
  
  int fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.println("----------");
  Serial.println(tempVal);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  Serial.println("----------");
  
  long cm = 0;
  cm = checkForAvailableSmall();
  int motion = digitalRead(inputPir);
  if(cm<50 && motion==HIGH){
    digitalWrite(relay1Small,HIGH);
    delay(500);
    myservo.write(90); 
    delay(500);
    myservo.write(0); 
    delay(500);
    //Serial.print("under 50 ");
  //  Serial.print("Distance: ");
  //  Serial.print(cm);
  //  Serial.print("cm");
    Serial.println();
    
   	  if(fahrenheit<=98){
        digitalWrite(ledRed,LOW);
        digitalWrite(ledYellow,LOW);
        digitalWrite(ledGreen,HIGH);
        delay(3000);
        ledOff();
      }
      else if(fahrenheit<=100){
        digitalWrite(ledRed,LOW);
        digitalWrite(ledYellow,HIGH);
        digitalWrite(ledGreen,LOW);
        delay(3000);
        ledOff();
      } 
      else if(fahrenheit>100){
        digitalWrite(ledRed,HIGH);
        digitalWrite(ledYellow,LOW);
        digitalWrite(ledGreen,LOW);
        delay(3000);
        ledOff();
      }
    }
  else {
    digitalWrite(relay1Small,LOW);
    // servo1.write(i); 
      // Print the distance
   // Serial.print("below 50 ");
  //  Serial.print("Distance: ")
  //  Serial.print(cm);
  //  Serial.print("cm");
  //  Serial.println();

  }
  long depthLiquid = checkForAvailableBig();
  if(depthLiquid>50){
    digitalWrite(relay2,HIGH);
    for(int j=0;j<=10;j++){
		bigServo.write(0);
        delay(1000);
        bigServo.write(180);
        delay(1000);
    }
    //Serial.print("liquid far from 50 ");
   // Serial.print("Distance: ");
  //  Serial.print(cm);
  //  Serial.print("cm");
    Serial.println();
    bigServo.write(0);
  } else{
    digitalWrite(relay2,LOW);
    bigServo.write(90);
  //  Serial.print("liquid in range 50 ");
   // Serial.print("Distance: ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    bigServo.write(0);
  }
}

long checkForAvailableSmall(){
  pinMode(sonar2Small, OUTPUT);
  digitalWrite(sonar2Small, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar2Small, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonar2Small, LOW);

  pinMode(sonar2Small, INPUT);
  long duration = pulseIn(sonar2Small, HIGH);

  // convert the time into a distance
  long cm = microsecondToCentimeter(duration);
  return cm;
}
long checkForAvailableBig(){
  pinMode(sonar1Big, OUTPUT);
  digitalWrite(sonar1Big, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar1Big, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonar1Big, LOW);

  pinMode(sonar1Big, INPUT);
  long duration = pulseIn(sonar1Big, HIGH);

  // convert the time into a distance
  long cm = microsecondToCentimeter(duration);
  return cm;
}
long microsecondToCentimeter(long micro){
  return micro / 29 / 2;
}

void ledOff(){
  digitalWrite(ledRed,LOW);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledGreen,LOW);
}




