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

int pressCount = 0;

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
  // if left value has changed no longer holding
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
   
   
   if ((trigButtonState1 == HIGH) && ((oldTrigButtonState1 == LOW) || holding1)){
       if (holding1){
         holding1Count++;
       }  
       switch(leftValue) {
        // empty
       case 0:
         Keyboard.print(" ");
         break;
       // 1
       case 1:
         Keyboard.print("a");
         break;
       case 2:
         Keyboard.print("f");
         break;  
       case 4:
         Keyboard.print("k");
         break;  
       case 8:
         Keyboard.print("p");
         break;  
       case 16:
         Keyboard.print("u");
         break;
         
       // CAPS  
       case 17:
         Keyboard.print("A");
         break;  
       case 24:
         Keyboard.print("P");
         break;  
       case 25:
         Keyboard.print("U");
         break;
       case 10:
         Keyboard.print("1");
         break;
       case 12:
         Keyboard.print("6");
         break;  
       case 9:
         Keyboard.print("z");
         break;    
       case 6:
         Keyboard.print("(");
         break;        
       
       //Movement 
       case 5:
         Keyboard.write(KEY_RETURN);
         break;  
         
       case 3: 
         
         xIn = analogRead(xpin);
         yIn = analogRead(ypin);        
       
        xMove = yMove = 0;   
         if (abs(yIn - yStart)> 1){
           yMove = yIn - yStart;
         }
         if (abs(xIn - xStart)> 1){
           xMove = xIn - xStart;
         }       
         Mouse.move(-xMove, yMove,0);
         holding1 = true; 
         delayTime = 30;
         
         Serial.print(xIn - xStart);
         Serial.print("\t");
         Serial.print(yIn - yStart);
         Serial.print("\t");
         Serial.println();
         break;       
         
       case 7:   
         Keyboard.press(KEY_LEFT_CTRL);
         Keyboard.write('c');
         Keyboard.release(KEY_LEFT_CTRL); 
         break; 
         
       case 21:  
         Keyboard.write(34);//@
        break; 
        
       case 28:  
         Keyboard.print("+");
        break;         
    } 
   }
   if ((trigButtonState2 == HIGH) && ((oldTrigButtonState2 == LOW) || holding2)){
       switch(leftValue) {
       case 0:
         Keyboard.print(",");
         break;
       case 1:
         Keyboard.print("b");
         break;
       case 2:
         Keyboard.print("g");
         break;  
       case 4:
         Keyboard.print("l");
         break;  
       case 8:
         Keyboard.print("q");
         break;  
       case 16:
         Keyboard.print("v");
         break; 
       // CAPS  
       case 17:
         Keyboard.print("B");
         break;
       case 18:
         Keyboard.print("G");
         break;  
       case 20:
         Keyboard.print("L");
         break;  
       case 24:
         Keyboard.print("Q");
         break;  
       case 25:
         Keyboard.print("V");
         break;  
       case 10:
         Keyboard.print("2");
         break;
       case 12:
         Keyboard.print("7");
         break;  
       case 9:
         Keyboard.print("?");
         break;    
       case 6:
         Keyboard.print(")");
         break;            
       //Movement
       case 5:
         Keyboard.write(KEY_LEFT_ARROW);
         break; 
         
       case 3: 
         Mouse.press();
         holding3 = true;
         break;           

       case 7:  
         Keyboard.press(KEY_LEFT_CTRL);
         Keyboard.write('v');
         Keyboard.release(KEY_LEFT_CTRL);
        break;   
        
      case 21:  
         Keyboard.write(163);
        break;  
        
      case 28:  
         Keyboard.print("-");
        break;       
    } 
   } 
   if ((trigButtonState3 == HIGH) && ((oldTrigButtonState3 == LOW) || holding3)){
       switch(leftValue) {
       case 0:
         Keyboard.print(".");
         break;
       case 1:
         Keyboard.print("c");
         break;
       case 2:
         Keyboard.print("h");
         break;  
       case 4:
         Keyboard.print("m");
         break;  
       case 8:
         Keyboard.print("r");
         break;  
       case 16:
         Keyboard.print("w");
         break; 
       // CAPS  
       case 17:
         Keyboard.print("C");
         break;
       case 18:
         Keyboard.print("H");
         break;  
       case 20:
         Keyboard.print("M");
         break;  
       case 24:
         Keyboard.print("R");
         break;  
       case 25:
         Keyboard.print("W");
         break; 
       case 10:
         Keyboard.print("3");
         break;
       case 12:
         Keyboard.print("8");
         break;  
       case 9:
         Keyboard.print("!");
         break;    
       case 6:
         Keyboard.print("[");
         break;            
       //Movement         
       case 5:
         Keyboard.write(KEY_UP_ARROW);
         break; 
         
      case 3:  
       Mouse.click(MOUSE_RIGHT); 
       break;           

      case 7:  
         Keyboard.press(KEY_LEFT_CTRL);
         Keyboard.write('x');
         Keyboard.release(KEY_LEFT_CTRL);
        break;              
   

       case 21:  
         Keyboard.print("|");
        break; 
        
      case 28:  
         Keyboard.print("*");
        break;         
         
    } 
   } 
   if ((trigButtonState4 == HIGH) && ((oldTrigButtonState4 == LOW) || holding4)){
       switch(leftValue) {
       case 0:
         Keyboard.print(",");
         break;
       case 1:
         Keyboard.print("d");
         break;
       case 2:
         Keyboard.print("i");
         break;  
       case 4:
         Keyboard.print("n");
         break;  
       case 8:
         Keyboard.print("s");
         break;  
       case 16:
         Keyboard.print("x");
         break; 
       // CAPS  
       case 17:
         Keyboard.print("D");
         break;
       case 18:
         Keyboard.print("I");
         break;  
       case 20:
         Keyboard.print("N");
         break;  
       case 24:
         Keyboard.print("S");
         break;  
       case 25:
         Keyboard.print("X");
         break; 
       case 10:
         Keyboard.print("4");
         break;
       case 12:
         Keyboard.print("9");
         break;  
       case 9:
         Keyboard.print("@");
         break;    
       case 6:
         Keyboard.print("]");
         break;            
       //Movement           
       case 5:
         Keyboard.write(KEY_DOWN_ARROW);
         break;  
       case 3:        
         Mouse.move(0,0,1);   
         holding4 = true; 
         delayTime = 30;       
         break;   
       case 7:  
        break;
        
       case 21:
         Keyboard.print("{");
        break;
        
      case 28:  
         Keyboard.print("/");
        break;          
    }
   }
   if ((trigButtonState5 == HIGH) && ((oldTrigButtonState5 == LOW) || holding5)){
       if (holding5){
         holding5Count++;
       }  
       switch(leftValue) {
       case 0:
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
         break;
       case 1:
         Keyboard.print("e");
         break;
       case 2:
         Keyboard.print("j");
         break;  
       case 4:
         Keyboard.print("o");
         break;  
       case 8:
         Keyboard.print("t");
         break;  
       case 16:
         Keyboard.print("y");
         break;  
       // CAPS  
       case 17:
         Keyboard.print("E");
         break;
       case 18:
         Keyboard.print("J");
         break;  
       case 20:
         Keyboard.print("O");
         break;  
       case 24:
         Keyboard.print("T");
         break;  
       case 25:
         Keyboard.print("Y");
         break; 
       case 10:
         Keyboard.print("5");
         break;
       case 12:
         Keyboard.print("0");
         break;  
       case 9:
         Keyboard.print("#");
         break;    
       case 6:
         Keyboard.print("/");
         break;            
       //Movement                   
       case 5:
         Keyboard.write(KEY_RIGHT_ARROW);
         break;  
       case 3: 
         Mouse.move(0,0,-1);   
         holding5 = true; 
         delayTime = 30;            
         break;
       case 7:  
        //Mouse.move(0,0,moveAmount); 
         Keyboard.write(KEY_TAB);
        break;     
        
       case 21:  
         Keyboard.print("}");
        break; 
        
      case 28:  
         Keyboard.print("%");
        break;          
    } 
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
  
  
 
     pressCount = 0;   
     oldTrigButtonState1 = trigButtonState1;
     oldTrigButtonState2 = trigButtonState2;
     oldTrigButtonState3 = trigButtonState3;
     oldTrigButtonState4 = trigButtonState4;
     oldTrigButtonState5 = trigButtonState5;   
     
     oldLeftValue = leftValue;
   
 delay(delayTime);  
   
}
