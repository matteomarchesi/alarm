bool hwEnable = false;
bool swEnable = true;
bool movement = false;
bool alarm = false;

int pinHWdisable = A0;
int pinPIR = A1;
int ledGreen = 2;
int ledBlue = 3;
int ledRed = 4;


int highPIR = 300;
unsigned long alarmDelay = 30000;
unsigned long toggleStart = 0;
int LL = 400;
int UL = 800;

// MUST returns true if disable jack is NOT inserted (true = alarm on)
bool hwEnablecheck(){
  if ((analogRead(pinHWdisable) > LL) and (analogRead(pinHWdisable) < UL)){ //aaa and bbb to be defined
    return false;
  }else{
    return true;
  }
  Serial.print("HWdis\t");
  Serial.println(analogRead(pinHWdisable));
}

bool movecheck(){
  if (analogRead(pinPIR) > highPIR){
    return true;
  }else{
    return false;
  }
  Serial.print("PIR\t");
  Serial.println(analogRead(pinPIR));
}


void setup(){
  Serial.begin(9600);
  Serial.println("Alarm!");
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop(){
//  hwEnable = hwEnablecheck();

  if ((analogRead(pinHWdisable) > LL) and (analogRead(pinHWdisable) < UL)){ //aaa and bbb to be defined
    hwEnable = false;
  }else{
    hwEnable = true;
  }

//  swEnable = SIMCHECK??
  
  bool prevMove = movement;
//  movement = movecheck();
  if (analogRead(pinPIR) > highPIR){
    movement = true;
  }else{
    movement = false;
  }
  
  Serial.print("HWdis\t");
  Serial.print(analogRead(pinHWdisable));
  Serial.print("\t");
  Serial.print("PIR\t");
  Serial.println(analogRead(pinPIR));



  if (movecheck and !prevMove){
    toggleStart = millis();
  }
  
  if (movecheck and prevMove){
    unsigned long moveTime = millis();
    if ((moveTime-toggleStart) >= alarmDelay){
      movement = true;
    }
  }
  
  alarm = hwEnable and swEnable and movement;

  if (hwEnable) {
    digitalWrite(ledGreen,HIGH);
  } else {
    digitalWrite(ledGreen,LOW);
  }
  
  if (movement) {
    digitalWrite(ledBlue,HIGH);
  } else {
    digitalWrite(ledBlue,LOW);
  }

  
  if (alarm) {
    digitalWrite(ledRed,HIGH);
  } else{
    digitalWrite(ledRed,LOW);
  }
  
}

