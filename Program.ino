#include <OneWire.h>
#include <DallasTemperature.h>
#include "Decoder.h"

String Rcvd_string;
char Rcvd_char_arr[20];
unsigned char therm_id[8];
char id_buffer[2];
unsigned char TokenNumber;
extern struct Token asToken[];

OneWire oneWire0(A0);
DallasTemperature sensor0(&oneWire0);

void setup() {
  sensor0.begin();
    
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  
  Rcvd_string = Serial.readStringUntil('\n');
  Serial.print(Rcvd_string + ";");
  sensor0.getAddress(therm_id, 0);
  for(unsigned char i = 1; i < 7; i++){
    sprintf(id_buffer, "%.2X", therm_id[i]);
    Serial.print(id_buffer);
  }
  sensor0.requestTemperatures();
  Serial.print(" ");
  Serial.println(sensor0.getTempCByIndex(0));
}
