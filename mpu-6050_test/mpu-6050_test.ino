#include <AsyncTimer.h>
AsyncTimer gyro;
AsyncTimer rgb;

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

const byte r = 11;
const byte g = 10;
const byte b = 9; 

void randomRGB()
{
  analogWrite(r, random(0, 255));
  analogWrite(g, random(0, 255));
  analogWrite(b, random(0, 255));
}

void gyroData()
{
  mpu6050.update();
  
  Serial.println("");
  Serial.print("temp : ");Serial.println(mpu6050.getTemp());
  Serial.print("accX : ");Serial.print(mpu6050.getAccX());
  Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
  Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());

  Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
  Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
  Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
  Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
  Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
  Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
  Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
  Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
  Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
}

void setup()
{
  Serial.begin(9600);
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  rgb.setInterval([]()
                      {
                       randomRGB();
                       }, 100);

  gyro.setInterval([]()
                      {
                       gyroData();
                       }, 1000);
}

void loop()
{ 
  rgb.handle();
  gyro.handle();
}
