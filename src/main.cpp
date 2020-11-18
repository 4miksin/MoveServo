#include <Arduino.h>

#define mx_en A2
#define mx_z  5
#define mx_s0 9
#define mx_s1 8
#define mx_s2 7
#define mx_s3 6
#define X_ang00  570
#define X_ang90 1250
#define Z_ang00  350
#define Z_ang90 1485

int pos1 = 350;
int pos2 = 1400;



void setup() {
  // put your setup code here, to run once:
  // pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Start!");
  
  pinMode(mx_s0, OUTPUT);
  pinMode(mx_s1, OUTPUT);
  pinMode(mx_s2, OUTPUT);
  pinMode(mx_s3, OUTPUT);
  
  pinMode(mx_z, OUTPUT);
  digitalWrite(mx_z, LOW);
  
  pinMode(mx_en, OUTPUT);
  digitalWrite(mx_en, LOW);

  // X servo selected in clip 0
  digitalWrite(mx_s0, LOW);
  digitalWrite(mx_s1, HIGH);
  digitalWrite(mx_s2, LOW);
  digitalWrite(mx_s3, LOW);

  moveservo(mx_z, X_ang90);
  //delay(1000);
  
  // Z servo selected
  digitalWrite(mx_s1, LOW);
  moveservo(mx_z, Z_ang90);
  // Waiting reski out
  digitalWrite(mx_s0, HIGH);
  pinMode(mx_z,INPUT_PULLUP);
  //int t = millis()+5000;
  //while(!digitalRead(mx_z) !! millis()>t) {delay(1);}
  if (digitalRead(mx_z))
  {
    Serial.println("Ch 1 HIGH");
  } else
  {
    Serial.println("Ch 1 LOW");
  }
  digitalWrite(mx_s0, LOW);
  pinMode(mx_z,OUTPUT);
  // return Z servo
  moveservo(mx_z, Z_ang00);
  // X servo selected
  digitalWrite(mx_s1, HIGH);
  moveservo(mx_z, X_ang00);

  Serial.println("Stop setup!");

}

int pos = 0;
int incomingByte = 0;

void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(LED_BUILTIN, HIGH);
  delay(400);
  digitalWrite(LED_BUILTIN, LOW);
  delay(400);
  */
  digitalWrite(mx_z, LOW);
	if (Serial.available() > 0) {
	  incomingByte = Serial.read()-48;
	  if (incomingByte>=0 and incomingByte<=9) {
	    pos=pos*10+incomingByte;
	    Serial.println(pos, DEC);
	  } else {
	    Serial.print("move: ");Serial.println(pos, DEC);Serial.print(" - ");Serial.println(pos, DEC);
	    for (int i=1;i<=180;i++){
	      digitalWrite(mx_z, HIGH);
	      delayMicroseconds(pos);
	      digitalWrite(mx_z, LOW);
	      delayMicroseconds(20000-pos);
	      delay(1);
	    }
     pos=0;
	  }
	}
}
