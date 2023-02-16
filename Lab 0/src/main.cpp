#include <Servo.h>
#include <Wire.h>

// for Servo
int servo_pin = GPIO_NUM_32;
Servo myservo; // create servo object to control a servo

// for Photoresistor 
const int photoresistor_pin = GPIO_NUM_39;
int max_light;
int min_light;
float light_val;
int rotation;

// for LED
int LED_outpin = GPIO_NUM_22;
int LED_inpin = GPIO_NUM_38;


void BlinkLight(){
  if(digitalRead(LED_inpin) == HIGH){
    digitalWrite(LED_outpin, LOW);
  } else{
    digitalWrite(LED_outpin, HIGH);
  }
}

void CalibrationSequence(){
  for(int i = 0; i < 10; i++){
    BlinkLight();

    delay(500);
  }
}

void setup(){
  Serial.begin(9600);
  
  pinMode(LED_outpin, OUTPUT);
  pinMode(LED_inpin, INPUT);

  // For Photoresistor 
  // finding max light
  CalibrationSequence();
  max_light = analogRead(photoresistor_pin);
  Serial.print("Max light is: ");
  Serial.print(max_light);
  
  // finding min light
  CalibrationSequence();
  min_light = analogRead(photoresistor_pin);
  Serial.print("\nMin Light is ");
  Serial.print(min_light);
  Serial.print("\n");

  // For Servo
	myservo.attach(servo_pin); // attaches the servo on port 32 to the servo object

  digitalWrite(LED_outpin, LOW);
}

void loop()
{
  //For Photoresistor
  light_val = analogRead(photoresistor_pin);

  rotation = light_val / max_light * 180;

  Serial.print("curr_rotation is: ");
  Serial.print(rotation);
  Serial.print("\n");

  myservo.write(rotation);

  Serial.println(light_val);
  

  delay(300);
}
