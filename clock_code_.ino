#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  // Set the time of the RTC module if necessary
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  String timeString = now.toString("HH:mm:ss");

  Serial.println(timeString);
  Serial.println(now.second());
  delay(1000);
}
