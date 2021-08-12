#include <OneWire.h>
#include <DallasTemperature.h>
#include "Decoder.h"

#define RED 3
#define GREEN 10
#define THERMOMETER

String Rcvd_string;
char Rcvd_char_arr[20];
unsigned char TokenNumber;
extern struct Token asToken[];

OneWire oneWire(A0);
DallasTemperature sensors(&oneWire);

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  sensors.begin();
  
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  Rcvd_string = Serial.readStringUntil('\n');
  Rcvd_string.toCharArray(Rcvd_char_arr, Rcvd_string.length()+1);
  TokenNumber = DecodeMsg(Rcvd_char_arr);
  if ((asToken[0].eType == KEYWORD) && (TokenNumber > 0)){
    switch(asToken[0].uValue.eKeyword){
      case ID:
        Serial.println("Arduino");
        break;
      case LED:
        switch (asToken[1].uValue.uiValue){
          case 0:
            digitalWrite(RED, !digitalRead(RED));
            break;
          case 1:
            digitalWrite(GREEN, !digitalRead(GREEN));
            break;
          default:
            Serial.println("wrong_led_number");
            break;
        }
        break;
      case TEMPVAL:
        sensors.requestTemperatures();
        Serial.println(sensors.getTempCByIndex(0));
        break;
      case TEMPID:
        Serial.println(sensors.getUserDataByIndex(0));
        break;
      default:
        Serial.println("unhanced_command");
        break;
    }
  }
  else{
    Serial.println("unknown_command");
  }
}
