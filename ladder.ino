#include <Servo.h>
#define PIN_TRIG 8
#define PIN_ECHO 7
#define flamePin 2
#define BuzzerPin 13
Servo myservo1;
Servo myservo2;
Servo myservo3;
void setup() {
  Serial.begin(115200);
  pinMode(flamePin, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo1.attach(11);  
  myservo2.attach(10);  
  myservo3.attach(9);  
}
int mo_thang(){
  myservo3.write(180);
  delay(100);
  myservo2.write(0);
  delay(100);
  myservo1.write(0);
  delay(100);
}
int dong_thang(){
  myservo1.write(90);
  delay(100);
  myservo2.write(90);
  delay(100);
  myservo3.write(0);
  delay(100);
}

void loop() {
  //Lấy thông tin từ cảm biến khoảng cách
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, LOW);
  int duration = pulseIn(PIN_ECHO, HIGH);
  float khoangcach = duration / 58;
  int flameState = digitalRead(flamePin);
  //Phát hiện cháy
  if (flameState == LOW) { 
    Serial.println("Lửa được phát hiện!");
    delay(100);
    mo_thang();
    tone(BuzzerPin, 262, 2000);
  }
  else if (flameState == HIGH && khoangcach > 25 ){
    Serial.println("Không có lửa.");
    delay(5000)
    dong_thang();
  }
  else 
  {
    Serial.println("Không có lửa.");
  }
  delay(1000);
}
