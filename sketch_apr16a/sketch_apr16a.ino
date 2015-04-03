#include <Servo.h>
#include <legopowerfunctions.h>

Servo servoMain; // Define our Servo
int fwdSpeed[] = {PWM_FLT, PWM_FWD1, PWM_FWD2, PWM_FWD3, PWM_FWD4, PWM_FWD5, PWM_FWD6, PWM_FWD7};
int revSpeed[] = {PWM_FLT, PWM_REV1, PWM_REV2, PWM_REV3, PWM_REV4, PWM_REV5, PWM_REV6, PWM_REV7};
int curSpeed = 0;
// IR led on port 13
LEGOPowerFunctions lego(13);
int val = 0;
int setSpeed = 3;
int irPin = 12;
int count = 0;
int buttonState=0;
int fwdRev=0;
int stationPin = 2;//9;
int buzzerPin = 11;

//irPin - conta  as voltas
//ledpin - pins com leds
//count - variavel que conta as voltas
//stationpin - para o comboio na estacao
//buzzerpin - apito de saida de estacao

void setup()
{
  Serial.begin(9600);
  pinMode(irPin, INPUT);
  pinMode(stationPin,INPUT);
  servoMain.attach(10); // servo on digital pin 10
  pinMode(buzzerPin,OUTPUT);
}

void loop()
{  
  if ( digitalRead(irPin) == 0 ) 
  {
    count++;
    delay(3000);
  }
  if (count <= 1)
  {
      Serial.print("Estacao: ");
      Serial.println(digitalRead(stationPin));

      Serial.print("contador:");
      Serial.println(count);
      if(setSpeed>7) setSpeed=7;

      if (fwdRev==0)
      {
        curSpeed=fwdSpeed[setSpeed];
      } 
      lego.SingleOutput( PWM, PWM_FWD5, RED, CH1);
      delay(100);
      if (digitalRead(stationPin) == 0)
      {
        Serial.print("teste");
        delay(1000);
        Serial.print("teste2");
        lego.SingleOutput( PWM, PWM_FLT, RED, CH1);
        servoMain.write(0);  // Turn Servo Left to 45 degrees
        delay(2000);
        tone(11,2000,1000);
        delay(500);
     }
  }
  else
  {
    servoMain.write(90);  // Turn Servo Left to 45 degrees
    Serial.print("contador:");
    Serial.println(count);
    count = 0; 
  }
}

