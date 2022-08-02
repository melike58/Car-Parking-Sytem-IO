#include <HCSR04.h>
#include "config.h"

int trigPin1=D4;
int echoPin1=D3;

int trigPin2=D5;
int echoPin2=D6;

int led1 = D8;
int led2 = D1;

// set up the 'digital' feed
AdafruitIO_Feed *deneme = io.feed("deneme");

void setup() {
  Serial.begin(115200);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  io.run();

  long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

   if (distance1 >=500 || distance1 <= 0){
    Serial.println("Out of range");
    digitalWrite(led1,LOW);

  }
  else if(distance1>=1 && distance1<=20 ){
    Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
    digitalWrite(led1,HIGH);
    deneme->save(distance1);
  }
  delay(2000);

long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;

   if (distance2 >= 500 || distance2 <= 0){
    Serial.println("Out of range");
    digitalWrite(led2,LOW);

  }
    else if(distance2>=1 && distance2<=20 ){

    Serial.print("Sensor2  ");
    Serial.print(distance2);
    Serial.println("cm");
    digitalWrite(led2,HIGH);
  }
  delay(2000);

  
 

}
