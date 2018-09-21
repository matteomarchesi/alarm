bool hwEnable = false;
bool swEnable = true;
bool movement = false;
bool alarm = false;

int pinHWdisable = A0;
int pinPIR = A1;
int ledGreen = 2;
int ledYellow = 3;
int ledRed = 4;


int highPIR = 400;
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
}

bool movecheck(){
  if (analogRead(pinPIR) > highPIR){
    return true;
  }else{
    return false;
  }
}

void setup(){
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop(){
  hwEnable = hwEnablecheck();

//  swEnable = SIMCHECK??
  
  bool prevMove = movement;
  movement = movecheck();

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
  
  if (alarm) {
    digitalWrite(ledRed,HIGH);
  } else{
    digitalWrite(ledRed,LOW);
  }
  
}

