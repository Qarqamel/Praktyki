#include "Decoder.h"

#define red 3
#define green 10

String Rcvd_string;
char Rcvd_char_arr[20];
unsigned char i;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  if (Serial.available() > 0){
    Rcvd_string = Serial.readStringUntil('\n');
    Rcvd_string.toCharArray(Rcvd_char_arr, Rcvd_string.length()+1);
    DecodeMsg(Rcvd_char_arr);
    if (asToken[0].eType == KEYWORD){
      if (asToken[0].uValue.eKeyword == ID){
        Serial.println("Arduino");
      }
      else if(asToken[0].uValue.eKeyword == LED){
        if(asToken[1].eType == KEYWORD && asToken[1].uValue.eKeyword == ON){
          if(asToken[2].eType == NUMBER && asToken[2].uValue.uiValue == 0){
            digitalWrite(red, HIGH);
          }
          else if (asToken[2].eType == NUMBER && asToken[2].uValue.uiValue == 1){
            digitalWrite(green, HIGH);
          }
          else{
            Serial.println("unknown command");
          }
        }
        else if(asToken[1].eType == KEYWORD && asToken[1].uValue.eKeyword == OFF){
          if(asToken[2].eType == NUMBER && asToken[2].uValue.uiValue == 0){
            digitalWrite(red, LOW);
          }
          else if (asToken[2].eType == NUMBER && asToken[2].uValue.uiValue == 1){
            digitalWrite(green, LOW);
          }
          else{
            Serial.println("unknown command");
          }
        }
        else{
          Serial.println("unknown command");
        }
      }
      else{
        Serial.println("unknown command");
      }
    }
    else{
      Serial.println("unknown command");
    }
  }
}
