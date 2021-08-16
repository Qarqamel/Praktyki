#include <OneWire.h>
#include <DallasTemperature.h>
#include "Decoder.h"

#define RED 3
#define GREEN 10
#define ID_BYTES 8
#define TERM_NR 3

OneWire oneWire(A0);
DallasTemperature sensors;

void byte_array_to_hex_string(unsigned char byte_array_size, unsigned char byte_array[], char hex_string[]){
  for(unsigned char i = 0; i<byte_array_size; i++){
    sprintf(hex_string+(2*i), "%.2X", byte_array[i]);
  }
  hex_string[byte_array_size*2] = NULL;
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  sensors.setOneWire(&oneWire);

  sensors.begin();
    
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  
  String Rcvd_string;
  char Rcvd_char_arr[20];
  unsigned char TokenNumber;
  extern struct Token asToken[];
  
  Rcvd_string = Serial.readStringUntil('\n');
  Rcvd_string.toCharArray(Rcvd_char_arr, Rcvd_string.length()+1);
  TokenNumber = DecodeMsg(Rcvd_char_arr);
  if ((asToken[0].eType == KEYWORD) && (TokenNumber > 0)){
    switch(asToken[0].uValue.eKeyword){
      case ID:
        Serial.println("Arduino");
        break;
      case TEMPVAL:
        sensors.requestTemperatures();
        for(unsigned char i = 0; i < TERM_NR; i++){
          Serial.print(sensors.getTempCByIndex(i));
          Serial.print(' ');
        }
          Serial.print('\n');
        break;
      case TEMPID:
        unsigned char therm_id[ID_BYTES];
        char id_string_buffer[2*ID_BYTES+1];
        for(unsigned char i = 0; i < TERM_NR; i++){
          sensors.getAddress(therm_id, i);
          byte_array_to_hex_string(ID_BYTES, therm_id, id_string_buffer);
          Serial.print(id_string_buffer);
          Serial.print(' ');
        }
         Serial.print('\n');
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
