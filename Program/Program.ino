#include "Decoder.h"

#define red 3
#define green 10

String Rcvd_string;
char Rcvd_char_arr[20];
unsigned char TokenNumber;
extern struct Token asToken[MAX_TOKEN_NR];

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  Rcvd_string = Serial.readStringUntil('\n');
  Rcvd_string.toCharArray(Rcvd_char_arr, Rcvd_string.length()+1);
  TokenNumber = DecodeMsg(Rcvd_char_arr);
  if (asToken[0].eType == KEYWORD && TokenNumber > 0){
    switch(asToken[0].uValue.eKeyword){
      case ID:
        Serial.println("Arduino");
        break;
      case LED:
        if(asToken[1].uValue.uiValue == 0){
          digitalWrite(red, digitalRead(red)==HIGH ? LOW : HIGH);
        }
        else if (asToken[1].uValue.uiValue == 1){
          digitalWrite(green, digitalRead(green)==HIGH ? LOW : HIGH);
        }
        break;
      default:
        Serial.println("unknown command");
        break;
    }
  }
  else{
    Serial.println("unknown command");
  }
}
