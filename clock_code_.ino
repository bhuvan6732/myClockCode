#include <Wire.h>
#include <RTClib.h>

#define aPin 2  //        
#define bPin 3  //      _____
#define cPin 4  //     |  A  |
#define dPin 5  //   F |_____| B
#define ePin 6  //     |  G  |
#define fPin 7  //   E |_____| C
#define gPin 8  //        D     O dot

#define c1Pin 9  // Common pin for digit 1
#define c2Pin 10 // Common pin for digit 2
#define c3Pin 11 // Common pin for digit 3
#define c4Pin 12 // Common pin for digit 4

int delaycounter=0;
int Common = 0; //<Common=1; for Common anode> <Common=0; for Common cathode>
int On, Off, Off_C; 
int DTime = 2; // Display timer
int mode=0;
int modesetter;
int Counter=0;
DateTime now;
RTC_DS3231 rtc;

void setup ()
{
 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT); 
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);

 pinMode(c1Pin, OUTPUT);
 pinMode(c2Pin, OUTPUT);
 pinMode(c3Pin, OUTPUT);
 pinMode(c4Pin, OUTPUT);

 

 if(Common==1){On=0, Off=1, Off_C=0;} //for Common anode
          else{On=1, Off=0, Off_C=1;} //for Common cathode

 // Indicate that system is ready
 for (int i = 9; i >=0; i--) {
 showNumber(i);
 digitalWrite(c1Pin, Common);
 digitalWrite(c2Pin, Common);
 digitalWrite(c3Pin, Common);
 digitalWrite(c4Pin, Common);
 delay(1000); 
 } 
  Serial.begin(9600);
  
  if (! rtc.begin()) 
  {
    Serial.println(" RTC Module not Present");
    while (1);
  }
  if (rtc.lostPower()) 
  {
    Serial.println("RTC power failure, reset the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
 // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () 
{
  now = rtc.now();
  displayTime();
  modesetter=digitalRead(A3);
  if (modesetter==0){
    delay(500);
    if (mode==1){mode=0; delay(500);}
    else {if (mode==0){mode=1;delay(500);}
    }}
}


 void displayTime()
 {  
    if (mode==0){
    String hour = String(now.hour());
    String newmin = String(now.minute());
    if (strlen(newmin.c_str())==1){
      newmin='0'+newmin;
      }
      else{
        newmin=newmin;}
    String sec = String(now.second());
    String myStr = hour+newmin;
    String myStr1 = hour+":"+newmin+":"+sec;
    Serial.println(myStr);
    Counter = atoi(myStr.c_str());
    }

    if (mode==1){
      String hour = String(now.day());
    String newmin = String(now.month());
    if (strlen(hour.c_str())==1){
      hour='0'+hour;
      }
      else{
        hour=hour;}
    if (strlen(newmin.c_str())==1){
      newmin='0'+newmin;
      }
      else{
        newmin=newmin;}
    String sec = String(now.second());
    String myStr = hour+newmin;
    String myStr1 = hour+":"+newmin+":"+sec;
    Serial.println(myStr);
    Counter = atoi(myStr.c_str());
    }
    
    showNumber((Counter/1000)%10);
    digitalWrite(c1Pin, Common);
    delay(DTime);
    digitalWrite(c1Pin, Off_C);
    
    showNumber((Counter/100)%10);
    digitalWrite(c2Pin, Common);
    delay(DTime);
    digitalWrite(c2Pin, Off_C);

    if (mode==0){
    if  (delaycounter>200){
    digitalWrite(13,HIGH);
    delaycounter+=2;
    if (delaycounter==400){
      delaycounter=0;}
      }
    else{
      digitalWrite(13,LOW);
      delaycounter+=2;}
    }
    else{
      digitalWrite(13,HIGH);
      }
    
    
    showNumber((Counter/10)%10);
    digitalWrite(c3Pin, Common);
    delay(DTime);
    digitalWrite(c3Pin, Off_C);
    
    showNumber(Counter%10);
    digitalWrite(c4Pin, Common);
    delay(DTime);
    digitalWrite(c4Pin, Off_C);
 
 } 
void showNumber(int x){

  //Serial.println(x);
  
   switch(x){
     case 1: one();   break;
     case 2: two();   break;
     case 3: three(); break;
     case 4: four();  break;
     case 5: five();  break;
     case 6: six();   break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine();  break;
     default: zero(); break;
   }
}

void one()
{
    digitalWrite(aPin, Off); //
    digitalWrite(bPin, On);  //      |
    digitalWrite(cPin, On);  //      |
    digitalWrite(dPin, Off); //      |
    digitalWrite(ePin, Off); //      |
    digitalWrite(fPin, Off);
    digitalWrite(gPin, Off);
}

void two()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, On);  //      |
    digitalWrite(cPin, Off); //  ____|
    digitalWrite(dPin, On);  // |
    digitalWrite(ePin, On);  // |____
    digitalWrite(fPin, Off);
    digitalWrite(gPin, On);
}

void three()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, On);  //      |
    digitalWrite(cPin, On);  //  ____|
    digitalWrite(dPin, On);  //      |
    digitalWrite(ePin, Off); //  ____|
    digitalWrite(fPin, Off);
    digitalWrite(gPin, On);
}

void four()
{
    digitalWrite(aPin, Off); //
    digitalWrite(bPin, On);  // |    |
    digitalWrite(cPin, On);  // |____|
    digitalWrite(dPin, Off); //      |
    digitalWrite(ePin, Off); //      |
    digitalWrite(fPin, On);
    digitalWrite(gPin, On);
}

void five()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, Off); // |
    digitalWrite(cPin, On);  // |____
    digitalWrite(dPin, On);  //      |
    digitalWrite(ePin, Off); //  ____|
    digitalWrite(fPin, On);
    digitalWrite(gPin, On);
}

void six()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, Off); // |
    digitalWrite(cPin, On);  // |____
    digitalWrite(dPin, On);  // |    |
    digitalWrite(ePin, On);  // |____|
    digitalWrite(fPin, On);
    digitalWrite(gPin, On);
}

void seven()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, On);  //      |
    digitalWrite(cPin, On);  //      |
    digitalWrite(dPin, Off); //      |
    digitalWrite(ePin, Off); //      |
    digitalWrite(fPin, Off);
    digitalWrite(gPin, Off);
}

void eight()
{
    digitalWrite(aPin, On); //  ____
    digitalWrite(bPin, On); // |    |
    digitalWrite(cPin, On); // |____|
    digitalWrite(dPin, On); // |    |
    digitalWrite(ePin, On); // |____|
    digitalWrite(fPin, On);
    digitalWrite(gPin, On);
}

void nine()
{
    digitalWrite(aPin, On);  //  ____
    digitalWrite(bPin, On);  // |    |
    digitalWrite(cPin, On);  // |____|
    digitalWrite(dPin, On);  //      |
    digitalWrite(ePin, Off); //  ____|
    digitalWrite(fPin, On);
    digitalWrite(gPin, On);
}

void zero()
{
    digitalWrite(aPin, On); //  ____
    digitalWrite(bPin, On); // |    |
    digitalWrite(cPin, On); // |    |
    digitalWrite(dPin, On); // |    |
    digitalWrite(ePin, On); // |____|
    digitalWrite(fPin, On);
    digitalWrite(gPin, Off);
}
 
