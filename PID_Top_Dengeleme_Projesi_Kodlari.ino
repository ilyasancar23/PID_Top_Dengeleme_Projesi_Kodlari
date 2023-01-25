#include<Servo.h>
#include<PID_v1.h>
const int servoPin = 9; // Sarı Kablo
float Kp = 2.5;// İlk Oransal Kazanç
float Ki = 0.1; // İlk İntegral Kazancı
float Kd = 0.5; //İlk Türev Kazancı
double Setpoint, Input, Output, ServoOutput;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
Servo myServo;
#define trigPin 6 
#define echoPin 7
void setup() {
 
Serial.begin(9600);
myServo.attach(servoPin);
Input = readPosition();
myPID.SetMode(AUTOMATIC);
myPID.SetOutputLimits(-20,20); // -80 ile 80 derece arası
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
 
void loop()
{
Setpoint = 15; // Denge Noktası
Input = readPosition();
 
myPID.Compute();
 
ServoOutput=102+Output;
myServo.write(ServoOutput);
}
 
float readPosition() {
delay(40);
long duration, cm;
unsigned long now = millis();
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
cm = (duration/2) / 29.1;
 
if(cm > 30) // 30 cm top için maksimum pozisyon
{cm=30;}
 
Serial.println(cm);
 
return cm; //Mesafe değerini döndürür.
}