#include <Bounce.h>

#define SETBUTTON1   0 //a-e
#define SETBUTTON2   1
#define SETBUTTON3   2
#define SETBUTTON4   3
#define SETBUTTON5   4

#define TRIGBUTTON1  5
#define TRIGBUTTON2  6
#define TRIGBUTTON3  7
#define TRIGBUTTON4  8
#define TRIGBUTTON5  9

#define LED 13
int delayTime = 0;
// Gyro Stuff
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
int xIn;
int yIn;

// change find these at runtime
int xStart = 479;
int yStart = 493;
//         Serial.print(xIn - xStart);
//        Serial.print("\t");
//        Serial.print(yIn - yStart);

int xMove;
int yMove;
int scrollMove;

//Key Stuff

int bounceTime = 50;
int moveAmount = 1;
Bounce bouncer1 = Bounce(TRIGBUTTON1 ,bounceTime); 
Bounce bouncer2 = Bounce(TRIGBUTTON2 ,bounceTime); 
Bounce bouncer3 = Bounce(TRIGBUTTON3 ,bounceTime); 
Bounce bouncer4 = Bounce(TRIGBUTTON4 ,bounceTime); 
Bounce bouncer5 = Bounce(TRIGBUTTON5 ,bounceTime); 

int oldTrigButtonState1 = 0;
int oldTrigButtonState2 = 0;
int oldTrigButtonState3 = 0;
int oldTrigButtonState4 = 0;
int oldTrigButtonState5 = 0;

boolean holding1 = false;
boolean holding2 = false;
boolean holding3 = false;
boolean holding4 = false;
boolean holding5 = false;

boolean first = true;

int holding1Count = 0;
int holding2Count = 0;
int holding3Count = 0;
int holding4Count = 0;
int holding5Count = 0;

int oldLeftValue = 0;




void setup() {
pinMode(LED,OUTPUT);

pinMode(SETBUTTON1 , INPUT);
pinMode(SETBUTTON2 , INPUT);
pinMode(SETBUTTON3 , INPUT);
pinMode(SETBUTTON4 , INPUT); 
pinMode(SETBUTTON5 , INPUT);    

pinMode(TRIGBUTTON1 , INPUT);
pinMode(TRIGBUTTON2 , INPUT);
pinMode(TRIGBUTTON3 , INPUT);
pinMode(TRIGBUTTON4 , INPUT);  
pinMode(TRIGBUTTON5 , INPUT);  


// initialize control over the keyboard and mouse
Keyboard.begin();
Mouse.begin();
Serial.begin(9600);
}

String getLetter(int leftHandCode, rightHandTrigger){
int Matrix[32][5] = {
{" ", ".", ",", "'", "FN-BACKSPACE"},//0
{"a", "b", "c", "d", "e"},
{"f", "g", "h", "i", "j"},
{"0","1","2","3","4"},
{"k", "l", "m", "n", "o"},
{"5","6","7","8","9"},
{"+","-","*","="},
{}
{"p", "q", "r", "s", "t"},
{},
{"&", "|", "{", "}", ""},
{},
{},
{},
{},
{},
{"u", "v", "w", "x", "y"},//16
{"A", "B", "C", "D", "E"},
{"F", "G", "H", "I", "J"},
{}
{"K", "L", "M", "N", "O"},
{},
{},
{},
{"P", "Q", "R", "S", "T"},
{"U", "V", "W", "X", "Y"},
{"(", ")","{","}", "#"},
{},
{},
{},
{},
{},
}

return[lefthandCode][rightHandTrigger]
}

void loop() {
//  if (first){
//    xStart = analogRead(xpin);
//    yStart = analogRead(ypin);
//    first = false;
//  }  
//  int delayTime  = 0;
//What has left hand set for us
int setState1 = digitalRead(SETBUTTON1);
int setState2 = digitalRead(SETBUTTON2);
int setState3 = digitalRead(SETBUTTON3);
int setState4 = digitalRead(SETBUTTON4);     
int setState5 = digitalRead(SETBUTTON5);

int leftValue = 0;  
//Serial.println(analogRead(xpin));
//Serial.println(analogRead(ypin)); 

if (setState1 == HIGH) {
leftValue = leftValue + 1; 
}
if (setState2 == HIGH) {
leftValue = leftValue + 2;    
}
if (setState3 == HIGH) {
leftValue = leftValue + 4;    
}

if (setState4 == HIGH) {
leftValue = leftValue + 8;    
}   
if (setState5 == HIGH) {
leftValue = leftValue + 16;    
} 

if (oldLeftValue != leftValue){
holding1 = false;
holding2 = false;
holding3 = false;
holding4 = false;
holding5 = false;
}  




//What right finger has triggered and what do we need to do
bouncer1.update ( );
bouncer2.update ( );
bouncer3.update ( );
bouncer4.update ( );
bouncer5.update ( );   


int trigButtonState1 = bouncer1.read();
int trigButtonState2 = bouncer2.read();
int trigButtonState3 = bouncer3.read();
int trigButtonState4 = bouncer4.read();
int trigButtonState5 = bouncer5.read();


int rightValue = -1
if (trigButtonState1 == HIGH && oldTrigButtonState1 == LOW){
holding1Count++;
rightValue = 0
} else if(trigButtonState1 == HIGH && oldTrigButtonState1 == LOW) {
holding2Count++;
rightValue = 1
} else if(trigButtonState1 == HIGH && oldTrigButtonState1 == LOW) {
holding3Count++;
rightValue = 2
} else if(trigButtonState1 == HIGH && oldTrigButtonState1 == LOW) {
holding4Count++;
rightValue = 3
} else if(trigButtonState1 == HIGH && oldTrigButtonState1 == LOW) {
holding5Count++;
rightValue = 4
}



if(rightValue >=0 ){
String letter = getLetter(leftValue, rightValue)
if(letter = "FN-ENTER"){
Keyboard.write(KEY_RETURN);
}else if(letter = "FN-PASTE"){
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.write('v');
Keyboard.release(KEY_LEFT_CTRL);
}else if(letter = "FN-BACKSPACE"){
if (!holding5){//initial press
Keyboard.write(KEY_BACKSPACE);
holding5 = true; // set holding
}
else{//holding
if (holding5Count > 5){
Keyboard.write(KEY_BACKSPACE);    
}  
delayTime = 100;
}
}
Keyboard.print(letter);
}


if ((trigButtonState1 == LOW) && (oldTrigButtonState1 == HIGH)){
holding1 = false;
holding1Count = 0;
}  

if ((trigButtonState2 == LOW) && (oldTrigButtonState2 == HIGH)){
holding2 = false;
holding2Count = 0;
Mouse.release();
Serial.println("button 2 released");
}    
if ((trigButtonState3 == LOW) && (oldTrigButtonState3 == HIGH)){
holding3 = false;
holding3Count = 0;
Mouse.release();
}  
if ((trigButtonState4 == LOW) && (oldTrigButtonState4 == HIGH)){
holding4 = false;
holding4Count = 0;
}    

if ((trigButtonState5 == LOW) && (oldTrigButtonState5 == HIGH)){
holding5 = false;
holding5Count = 0;
}  

oldTrigButtonState1 = trigButtonState1;
oldTrigButtonState2 = trigButtonState2;
oldTrigButtonState3 = trigButtonState3;
oldTrigButtonState4 = trigButtonState4;
oldTrigButtonState5 = trigButtonState5;   

oldLeftValue = leftValue;

delay(delayTime);  

}
