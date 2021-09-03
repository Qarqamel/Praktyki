#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include "MCP3424.h"

#define ID_BYTES 8

OneWire oneWire(3);
DallasTemperature sensor(&oneWire);
char id_string_buffer[ID_BYTES*2+1];
float temp_buffer;
MCP3424 adc(0b01101000);

static char * errmsg[] = {"", "underflow", "overflow", "i2c", "in progress", "timeout"};

void setup() {
  unsigned char therm_id[ID_BYTES];

  Wire.begin();
  sensor.begin();
  sensor.setResolution(9);  
  Serial.begin(9600);
  Serial.setTimeout(-1);

  adc.generalCall(GC_RESET);

  adc.creg[CH1].bits = { GAINx1, R16B, CONTINUOUS, CH1, 1 };
  
  sensor.getAddress(therm_id, 0);
  byte_array_to_hex_string(6, therm_id+1, id_string_buffer);
  sensor.requestTemperatures();
  temp_buffer = sensor.getTempCByIndex(0);
}

void loop (){
   char rx_char, mode;
   double value;
   
   // odczyt trybu
   Serial.readBytes(&mode, 1);
   Serial.write(&mode, 1);
   
   // forwardowanie obcych pomiarów
   while (true) {
      Serial.readBytes(&rx_char, 1);
      if (rx_char == '\n') break;
      Serial.write(&rx_char, 1);
   }
   
   // dołożenie swojego
   Serial.print(";");
   switch(mode){
      case 'i':      
      Serial.println(id_string_buffer);
      break;
      case 't':
      Serial.println(temp_buffer);
      sensor.requestTemperatures();
      temp_buffer = sensor.getTempCByIndex(0);
      break;
      case 'x':
      ConvStatus err = adc.read(CH1, value);
      if (err == R_OK) 
        Serial.println(value, DEC); 
      else {
        Serial.print("conversion error: ");
        Serial.println(errmsg[err]);
      }
      asm volatile ("nop");
      break;
      default:
      Serial.println("nomode");
      break;
   }    
}

void byte_array_to_hex_string(unsigned char byte_array_size, unsigned char byte_array[], char hex_string[]){
  for(unsigned char i = 0; i<byte_array_size; i++){
    sprintf(hex_string+(2*i), "%.2X", byte_array[i]);
  }
  hex_string[byte_array_size*2] = NULL;
}
