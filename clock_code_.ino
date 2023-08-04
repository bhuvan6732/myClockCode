#include <Wire.h>
#include <LiquidCrystal.h>
#include <RTClib.h>

#define aPin 2 //
#define bPin 3 //      _____
#define cPin 4 //     |  A  |
#define dPin 5 //   F |_____| B
#define ePin 6 //     |  G  |
#define fPin 7 //   E |_____| C
#define gPin 8 //        D     O dot

#define c1Pin 9  // Common pin for digit 1
#define c2Pin 10 // Common pin for digit 2
#define c3Pin 11 // Common pin for digit 3
#define c4Pin 12 // Common pin for digit 4

int Common = 1; //<Common=1; for Common anode> <Common=0; for Common cathode>
int On, Off, Off_C;
int DTime = 4; // Display timer

DateTime now;
RTC_DS3231 rtc;
void displayDate(void);
void displayTime(void);
void setup()
{
  if (Common == 1)
  {
    On = 0, Off = 1, Off_C = 0;
  } // for Common anode
  else
  {
    On = 1, Off = 0, Off_C = 1;
  } // for Common cathode
  Serial.begin(9600);
  if (!rtc.begin())
  {
    Serial.println(" RTC Module not Present");
    while (1)
      ;
  }
  if (rtc.lostPower())
  {
    Serial.println("RTC power failure, reset the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop()
{
  now = rtc.now();
  displayTime();
}

void displayTime()
{
  String hour = String(now.hour());
  String min = String(now.minute());
  String sec = String(now.second());
  String myStr = hour + min;
  String myStr1 = hour + ":" + min + ":" + sec;
  // Serial.println(myStr);
  delay(1000);
  int Counter = atoi(myStr.c_str());
  showNumber((Counter / 1000) % 10);
  digitalWrite(c1Pin, Common);
  delay(DTime);
  digitalWrite(c1Pin, Off_C);

  showNumber((Counter / 100) % 10);
  digitalWrite(c2Pin, Common);
  delay(DTime);
  digitalWrite(c2Pin, Off_C);

  showNumber((Counter / 10) % 10);
  digitalWrite(c3Pin, Common);
  delay(DTime);
  digitalWrite(c3Pin, Off_C);

  showNumber(Counter % 10);
  digitalWrite(c4Pin, Common);
  delay(DTime);
  digitalWrite(c4Pin, Off_C);
}
void showNumber(int x)
{

  Serial.println(x);
  switch (x)
  {
  case 1:
    one();
    break;
  case 2:
    two();
    break;
  case 3:
    three();
    break;
  case 4:
    four();
    break;
  case 5:
    five();
    break;
  case 6:
    six();
    break;
  case 7:
    seven();
    break;
  case 8:
    eight();
    break;
  case 9:
    nine();
    break;
  default:
    zero();
    break;
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
