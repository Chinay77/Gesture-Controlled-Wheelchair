#include <Wire.h>
#include <MPU6050.h>
 
#define first_motor_pin1 5
#define first_motor_pin2 6
#define second_motor_pin1 9
#define second_motor_pin2 10

MPU6050 sensor;
int16_t ax, ay, az;
int16_t gx, gy, gz;

int first_motor_speed;
int second_motor_speed;

void setup ( )
{
  Wire.begin( );
  Serial.begin (9600);
  Serial.println ("Initializing the sensor");
  sensor.initialize ( );
  Serial.println(sensor.testConnection( ) ? "Successfully Connected" : "Connection failed");
  delay(1000);
  Serial.println("Taking Values from the sensor");
  delay(1000);
}

void loop ( )
{
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, 0, 255 ); //Send X axis data
  ay = map(ay, -17000, 17000, 0, 255);  //Send Y axis data
  first_motor_speed = 255-ax;
  second_motor_speed = 255+ax;
  Serial.print("X: ");
  Serial.print(ax);
  Serial.print("    ");
  Serial.print("Y: ");
  Serial.print(ay);
  Serial.print("\n");
   
  //analogWrite (first_motor_pin2, first_motor_speed);
  //analogWrite (second_motor_pin2, second_motor_speed);
  //delay (200);
  while(true){
    if (ay < 80) { //Reverse
      digitalWrite(first_motor_pin1, HIGH);
      digitalWrite(first_motor_pin2, LOW);
      digitalWrite(second_motor_pin1, LOW);
      digitalWrite(second_motor_pin2, HIGH);

    }

    if (ay > 145) {//forward
      digitalWrite(first_motor_pin1, LOW);
      digitalWrite(first_motor_pin2, HIGH);
      digitalWrite(second_motor_pin1, HIGH);
      digitalWrite(second_motor_pin2, LOW);
    }

    if (ax > 155) {//right turn
      digitalWrite(first_motor_pin1, LOW);
      digitalWrite(first_motor_pin2, HIGH);
      digitalWrite(second_motor_pin1, LOW);
      digitalWrite(second_motor_pin2, HIGH);
    }

    if (ax < 80) {//left turn
      digitalWrite(first_motor_pin1, HIGH);
      digitalWrite(first_motor_pin2, LOW);
      digitalWrite(second_motor_pin1, HIGH);
      digitalWrite(second_motor_pin2, LOW);
    }

    if (ax > 100 && ax < 170 && ay > 80 && ay < 130) { //stop
      digitalWrite(first_motor_pin1, LOW);
      digitalWrite(first_motor_pin2, LOW);
      digitalWrite(second_motor_pin1, LOW);
      digitalWrite(second_motor_pin2, LOW);
    }
  }
}
