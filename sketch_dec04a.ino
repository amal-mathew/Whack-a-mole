const int LED[]={2,3,4,5};
const int Button[]={6,7,8,9};
int mole;
volatile int state;
int counter = 0;
float timep= 2000;
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);

  //initalize Buttons as input
  pinMode(Button[0], INPUT);
  pinMode(Button[1], INPUT);
  pinMode(Button[2], INPUT);
  pinMode(Button[3], INPUT);
  Serial.begin(9600);      // open the serial port at 9600 bps: 
  randomSeed(analogRead(0)); // seed the random() function with an open pin
  fail();  // first call of the fail (reset) function defined below
}

void ledOn(int colorON) { // function to switch on an LED
  if (colorON == LED[0]) {digitalWrite(LED[0], HIGH);}
  else if (colorON == LED[1]) {digitalWrite(LED[1], HIGH);}
  else if (colorON == LED[2]) {digitalWrite(LED[2], HIGH);}
  else if (colorON == LED[3]) {digitalWrite(LED[3], HIGH);}
}

void ledOff(int colorOFF) { // function to switch off an LED
  if (colorOFF == LED[0]) {digitalWrite(LED[0], LOW);}
  else if (colorOFF == LED[1]) {digitalWrite(LED[1], LOW);}
  else if (colorOFF == LED[2]) {digitalWrite(LED[2], LOW);}
  else if (colorOFF == LED[3]) {digitalWrite(LED[3], LOW);}
}

void blinkall(){  // function to blink all LEDs together
  for(int i=0; i<4;i++){ledOn(LED[i]);}
  delay(100);
  for(int i=0; i<4;i++){ledOff(LED[i]);}
  delay(100);
}

void fail(){  // the reset function: sets the counter to 0 and the state to -1, then blinks the LEDs
  counter = 0;
  state = -1;
  blinkall();
  blinkall();
  blinkall();
  blinkall();
  blinkall();
  delay(500);
}

void displayMole() {
  mole = rand() % 4; // one of the four moles is randomly chosen and switched on
  for(int i = 0; i<4;i++){
    if(mole==i){ledOn(LED[i]);}
  }
}

void whackMole() {
  unsigned long current;
  unsigned long endt;
  if(counter==0){timep=2000;}  // time period is initially set to 2 seconds
  else{timep = timep*0.9;} // with each succesful attempt, time period reduces by 10% 
  current = millis();
  endt = millis() + timep;
  while  (millis()<endt) {  // program scans for button presses in the set time period
    if(digitalRead(Button[0])==1){state=0;}
    else if(digitalRead(Button[1])==1){state=1;}
    else if(digitalRead(Button[2])==1){state=2;}
    else if(digitalRead(Button[3])==1){state=3;}
    if(mole==state){  // if a correct press is detected, LED is switched off and the program moves on
      counter+=1;
      delay(500);
      ledOff(LED[state]);
      Serial.print("here");
      break;
    } 
  }
  if(mole!=state){fail();}  // if a correct press is not detected, the counters and timer reset
}
 
void loop() { // main loop of whack a mole
  displayMole();
  whackMole();
  Serial.print(state);
  Serial.print(counter);
}
