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
int rotation; // holds rotation for servo

// for LED
int LED_outpin = GPIO_NUM_22;
int LED_inpin = GPIO_NUM_38;

/* changes state of LED based on current state */
void BlinkLight(){
  if(digitalRead(LED_inpin) == HIGH){
    digitalWrite(LED_outpin, LOW);
  } else{
    digitalWrite(LED_outpin, HIGH);
  }
}

/* makes LED blink 5 times when called */
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
  // blinks 5 times then checks for max light (max light will be intentional/forced)
  CalibrationSequence();
  max_light = analogRead(photoresistor_pin);
  Serial.print("Max light is: ");
  Serial.print(max_light);
  
  // blinks 5 times then checks for min light (min light will be intentional/forced)
  CalibrationSequence();
  min_light = analogRead(photoresistor_pin);
  Serial.print("\nMin Light is ");
  Serial.print(min_light);
  Serial.print("\n");

  // For Servo
  myservo.attach(servo_pin); // attaches the servo on port 32 to the servo object

  // turns off LED for main function in loop()
  digitalWrite(LED_outpin, LOW);
}

void loop()
{
  //For Photoresistor
  light_val = analogRead(photoresistor_pin);

  // find the percentage of current light to max light, multiply by 180 to find next angle
  rotation = light_val / max_light * 180;

  Serial.print("curr_rotation is: ");
  Serial.print(rotation);
  Serial.print("\n");

  // output rotation to servo
  myservo.write(rotation);

  Serial.println(light_val);
  

  delay(300);
}
