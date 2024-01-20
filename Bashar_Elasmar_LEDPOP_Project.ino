//Bashar Elasmar 
//CS122A Project 2
//Jun 06 2023


#include <LedControl.h>

//initialization of hardware components
const int trig = 12;
const int echo = 13;
int duration = 0;
int distance = 0;
int buzzer = 7; 

//initialization of notes 
int A = 3729;
int B = 3951;
int C = 4435;
int D = 4699;
int DS7 = 2489;
int E = 2637;
int F = 3000;
int G = 3322;
int GS6 = 1661; 

int melody[] = {D, D, D, D, E, F, F, F, G, A, A, A, A, A, D, C, G, B, A, F};  //I Wanna Go 
double note_durations[] = {3, 3, 3, 4, 4, 3, 3, 3, 4, 4, 3, 3, 3, 3, 4, 3, 2, 4.5, 3, 3};

int melody2[] = {C, C, C, B, A, G, A, F, D, D, C, A, F, F, D, C, A, GS6}; //California Gurls 
double note_durations2[] = {3, 3, 3, 5, 4, 4, 1.5, 4, 4, 4, 3, 3, 4, 4, 3, 3, 3, 3}; 

int melody3[] = {F, F, D, D, C, C, B, A, G, F, F, D, D, C, B, A, G, A, G, G, F, F, DS7, F, DS7, A, A, G}; //21 Guns 
double note_durations3[] = {4, 4, 2, 4, 4, 4, 5, 3, 2, 4, 4, 2, 2, 4, 5, 4, 1.5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 1.5}; 

int melody4[] = {A, A, G, A, G, F, E, E, F, G, F, F, G, A, G, A, B, A, C, C, F, E, F, E}; //Eye of the Tuger 
double note_durations4[] = {5, 5, 4, 5, 4, 4, 5, 5, 4, 4, 4, 3.5, 4, 5, 4, 5, 5, 5, 4, 2, 4, 5, 3.5, 1.5}; 

//initialization of LED Matrix
int DIN = 10; 
int CS =  9;
int CLK = 8;

LedControl lc=LedControl(DIN,CLK,CS,0);

void setup()
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(buzzer, OUTPUT); 
 
 lc.shutdown(0,false);       
 lc.setIntensity(0,15);      //Adjust the brightness maximum is 15
 lc.clearDisplay(0);    

 Serial.begin(9600);

}

void loop()
{ 
    digitalWrite(trig , HIGH);
    delayMicroseconds(1000);
    digitalWrite(trig , LOW);
    
    duration = pulseIn(echo , HIGH);
    distance = (duration/2) / 28.5 ;
    Serial.println(distance);
    
    //Facial Expression
    byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C}; //smiley face 
    byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C}; //neutral face 
    byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C}; // sad face 
    byte s[8] = {0x7e,0x7e,0x40,0x7e,0x7e,0x02,0x7e,0x7e}; //s
    byte o[8] = {0x7e,0x7e,0x66,0x66,0x66,0x66,0x7e,0x7e}; //o
    byte s1[8] = {0x7e,0x7e,0x40,0x7e,0x7e,0x02,0x7e,0x7e}; //s
    byte ex[8] = {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x18}; //exclamtion mark
    byte creeper[8] = {0x00,0x66,0x66,0x00,0x00,0x18,0x3c,0x42}; //Minecraft creeper

    
    if ( distance <= 2 )
    {
      printByte(s);
      delay(400);
      printByte(o);
      delay(400);
      printByte(s1);
      delay(400);
      printByte(ex);
      delay(400);
      printByte(creeper);
      delay(400);

      for(int i = 0; i < 20; i++) //when i is less than the array of notes 
      {
        int n_duration = 1000/note_durations[i]; //divide the total duration of the melodies by 1000
        tone(buzzer, melody[i], n_duration);
        int pauseBetweenNotes = n_duration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer);
      }    
    }
    else if ( distance <= 8 )
    {
     printByte(sad);

     for(int i = 0; i < 18; i++)
      {
        int n_duration = 1000/note_durations2[i]; 
        tone(buzzer, melody2[i], n_duration);
        int pauseBetweenNotes = n_duration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer);
      }    
    }
    else if ( distance <= 15 )
    {
      printByte(neutral);  

      for(int i = 0; i < 28; i++)
      {
        int n_duration = 1000/note_durations3[i]; 
        tone(buzzer, melody3[i], n_duration);
        int pauseBetweenNotes = n_duration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer);
      }   
    }
    else if ( distance <= 25 )
    {
      printByte(smile);

      for(int i = 0; i < 24; i++)
      {
        int n_duration = 1000/note_durations3[i]; 
        tone(buzzer, melody4[i], n_duration);
        int pauseBetweenNotes = n_duration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzzer);
      }   
    }
  
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
