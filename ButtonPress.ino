#include <Servo.h>
const int buttonPin = 7;
int buttonState = 0;
int pos = 0;
int i;
int ledpin = 6;
int photoresistor = A0;
#define SERIAL    

Servo myservo; //create the servo object
Servo myservo2;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// change this to make the song slower or faster
int tempo = 225;

// change this to whichever pin you want to use
#define SPEAKER 6   // Piezo Speaker pin (positive, other pin to ground)



  
void setup() 
{
  myservo.attach(3);
  myservo2.attach(4);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledpin, OUTPUT);  
  Serial.begin(9600);
  #ifdef SERIAL
   Serial.begin(9600);
  #endif
  pinMode(SPEAKER,OUTPUT);
}
void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER, LOW);
     delayMicroseconds(tone1);
  }     
}
void ruff() {   // dog ruff
  uint16_t i;
  for(i=800; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}
void beep (int16_t frequencyInHertz, long timeInMilliseconds) {
    long x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) {   
       digitalWrite(SPEAKER,HIGH);
       delayMicroseconds(delayAmount);
       digitalWrite(SPEAKER,LOW);
       delayMicroseconds(delayAmount);
    }  
}

void scale() {
  for(uint16_t i=50; i<15000; i++)  {
     playTone(i,20);
  }
}

void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}

void loop()
{   
  int value;
  
  value = analogRead(A0); //Read the photoresistor
  Serial.println(value); //Print to serial monitor

  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState); 

  if(buttonState == 0)
   i = 3;
  

  if(i > 0) //If button is pressed
  { 
    
   if(value < 70)
   {
    //Mouth open
     ruff();
     for(pos = 0; pos <= 90; pos += 8)
     {
      myservo.write(pos);
      delay(35);
      digitalWrite(ledpin,HIGH);
     }
     meow2();
     //Lift hand
      // goes from 0 degrees to 180 deg in steps of 1 deg
     
       myservo2.write(90);              // tell servo to go to position in variable 'pos'
       //myservo2.write(pos);
       delay(15);                       // waits 15 ms for the servo to reach the position
     

      for(pos = 90; pos >= 0; pos -= 5)
      {
        myservo2.write(pos);              // tell servo to go to position in variable 'pos'
        //myservo2.write(pos);
        delay(15);    
      } 
      meow2();

      
      //Lower Mouth
      
        myservo.write(0);
        delay(15);
        digitalWrite(ledpin, LOW);
       
       ruff();

      i-=1;
    } 
  } 
}
     
