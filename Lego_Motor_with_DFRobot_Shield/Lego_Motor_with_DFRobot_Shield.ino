const byte rtMotorPin1 = 4;
const byte rtMotorPin2 = 5;  //pwm
const byte ltMotorPin2 = 6;  //pwm
const byte ltMotorPin1 = 7;
const byte radioPinA = 8;
const byte radioPinB = 9;
const byte radioPinC = 10;
const byte radioPinD = 11;
const byte light = 13;
const byte reader = A5;

boolean lightMode = 0;
int currentMode = 0;;
int motorDir = 0;
int count = 0;
int rtSpeed = 255;
int ltSpeed = 255;
void setup()
{
  
  Serial.begin(9600);
  Serial.println("  ");
  pinMode(rtMotorPin1, OUTPUT);
  pinMode(rtMotorPin2, OUTPUT);
  pinMode(ltMotorPin1, OUTPUT);
  pinMode(ltMotorPin2, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(2, INPUT);
  pinMode(radioPinA, INPUT);
  pinMode(radioPinB, INPUT);
  pinMode(radioPinC, INPUT);
  pinMode(radioPinD, INPUT);
  digitalWrite(light, HIGH);
  attachInterrupt(0, radioSignal, RISING);
}

void loop()
{
  lightSensor();
  currentMode = lightMode;
    
  rtMotor(rtSpeed, lightMode);
  ltMotor(ltSpeed, lightMode);
  //Serial.println(lightMode);
}

void rtMotor(int rtPwm, boolean reverse)
{
  analogWrite(rtMotorPin2, rtPwm);
  if (reverse) {
    digitalWrite(rtMotorPin1, LOW);
  }
  else {
    digitalWrite(rtMotorPin1, HIGH);
  }
}

void ltMotor(int ltPwm, boolean reverse)
{
  analogWrite(ltMotorPin2, ltPwm);
  if (reverse) {
    digitalWrite(ltMotorPin1, LOW);
  }
  else
  {
    digitalWrite(ltMotorPin1, HIGH);
  }
}

int lightSensor()
{
  int signal;
  signal = analogRead(reader);
  if (signal >= 600 && currentMode == 0 && count >= 1) {
    lightMode = 1;
    count = 0;
  }
  else if (signal >= 600 && currentMode == 1 && count >= 1) {
    lightMode = 0;
    count = 0;
  }
  else if (signal < 600 && currentMode == 1) {
    lightMode = 1;
    count++;
  }
  else if (signal < 600 && currentMode == 0) {
    lightMode = 0;
    count++;
  }
  else
  {
    lightMode = lightMode;
  }
  return lightMode;
}

void radioSignal()
{
  //Protect against rtSpeed or ltSpeed >> 255 or << 0
  
  if (digitalRead(radioPinA) == HIGH)
  {
    
    if (ltSpeed <= 255) {
    ltSpeed++;
    }
  }
  else if (digitalRead(radioPinB) == HIGH)
  {
    if (rtSpeed <= 255) {
    rtSpeed++;
    }
  }
  else if (digitalRead(radioPinC) == HIGH)
  {
    if (ltSpeed >= 0) {
    ltSpeed--;
    }
  }
  else if (digitalRead(radioPinD) == HIGH)
  {
    if (rtSpeed >= 0) {
    rtSpeed--;
    }
  }
}
