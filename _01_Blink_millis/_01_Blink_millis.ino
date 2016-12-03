/* 
 Basado en:
 ESP8266 BlinkWithoutDelay by Simon Peter
 Blink the blue LED on the ESP-01 module
 Based on the Arduino Blink without Delay example
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED

 Modificado por Marino Linaje y testado en ESP-12E nodemcu v3 lolin
*/
#define LED_BUILTIN 2 //Es una definición redeclarada para que que corresponda con la versión v3

int LED_state = LOW;     

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (LED_state == LOW)
      LED_state = HIGH;
    else
      LED_state = LOW;
    digitalWrite(LED_BUILTIN, LED_state);
  }
}
