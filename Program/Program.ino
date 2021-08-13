#include <OneWire.h>
#include <DallasTemperature.h>
#include "Decoder.h"

#define RED 3
#define GREEN 10
#define ID_BYTES 8

String Rcvd_string;
char Rcvd_char_arr[20];
unsigned char TokenNumber;
extern struct Token asToken[];

OneWire oneWire0(A0);
OneWire oneWire1(A1);
DallasTemperature sensor0(&oneWire0);
DallasTemperature sensor1(&oneWire1);

void byte_array_to_hex_string(unsigned char byte_array_size, unsigned char byte_array[], char hex_string[]){
  for(unsigned char i = 0; i<byte_array_size; i++){
    sprintf(hex_string+(2*i), "%.2X", byte_array[i]);
  }
  hex_string[byte_array_size*2] = NULL;
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  sensor0.begin();
  sensor1.begin();
    
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
        sensor0.requestTemperatures();
        Serial.println(sensor0.getTempCByIndex(0));
        sensor1.requestTemperatures();
        Serial.println(sensor1.getTempCByIndex(0));
        break;
      case TEMPID:
        unsigned char therm_id[ID_BYTES];
        char id_string_buffer[2*ID_BYTES+1];
        sensor1.getAddress(therm_id, 0);
        byte_array_to_hex_string(ID_BYTES, therm_id, id_string_buffer);
        Serial.println(id_string_buffer);
        sensor0.getAddress(therm_id, 0);
        byte_array_to_hex_string(ID_BYTES, therm_id, id_string_buffer);
        Serial.println(id_string_buffer);
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
