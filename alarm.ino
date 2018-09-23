bool hwEnable = false;
bool swEnable = true;
bool movement = false;
bool checkMove = false;
bool alarm = false;
bool prevMove = false;
bool visto = false;

int pinHWdisable = A0;
int pinPIR = A1;
int ledGreen = 2;
int ledBlue = 3;
int ledRed = 4;
int counter = 0;

int highPIR = 300;
int maxMove = 3;
unsigned long alarmDelay = 30 * 1000;
unsigned long toggleStart = 0;
unsigned long moveTime = 0;

int LL = 400;
int UL = 800;

void setup(){
  Serial.begin(9600);
  Serial.println("Alarm!");
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop(){

// check if disable jack is inserted
  if ((analogRead(pinHWdisable) > LL) and (analogRead(pinHWdisable) < UL)){ //aaa and bbb to be defined
    hwEnable = false;
    alarm = false;
    movement = false;
  }else{
    hwEnable = true;
  }

//  swEnable = SIMCHECK??

  prevMove = checkMove;
  
/*  if (analogRead(pinPIR) > highPIR){
    checkMove = true;
  }else{
    checkMove = false;
  }
*/
  checkMove = (analogRead(pinPIR) > highPIR)?true:false;

  if (checkMove != prevMove) {
     if (checkMove) {
       counter ++;
     }
  }
  moveTime = millis();
  if (counter < 1){
    toggleStart = moveTime;
  }
  
  if (moveTime - toggleStart >= alarmDelay) {
    if ((checkMove) or (counter > maxMove)) {
      movement = true;
    }
    counter = 0;
  }
  Serial.print(analogRead(pinPIR));
  Serial.print("\t");
  Serial.print(counter); 
  Serial.print("\t");
  Serial.print(moveTime);
  Serial.print("\t");
  Serial.print(toggleStart);
  Serial.print("\t");
  Serial.println(moveTime - toggleStart);
  
  alarm = hwEnable and swEnable and movement;

  if (hwEnable) {
    digitalWrite(ledGreen,LOW);
    digitalWrite(ledRed,LOW);
    digitalWrite(ledBlue,LOW);
  } else {
    digitalWrite(ledGreen,HIGH);
  }
  
  if (movement) {
    digitalWrite(ledBlue,HIGH);
    digitalWrite(ledRed,LOW);
    digitalWrite(ledGreen,LOW);

  } else {
    digitalWrite(ledBlue,LOW);
  }

  
  if (alarm) {
    digitalWrite(ledRed,HIGH);
    digitalWrite(ledBlue,LOW);
    digitalWrite(ledGreen,LOW);
  }
  
}

