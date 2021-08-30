#include <OneWire.h>
#include <DallasTemperature.h>

#define ID_BYTES 8

OneWire oneWire(A0);
DallasTemperature sensor(&oneWire);
char id_string_buffer[ID_BYTES*2+1];
float temp_buffer;

void setup() {
  unsigned char therm_id[ID_BYTES];
      
  sensor.begin();
  sensor.setResolution(9);  
  Serial.begin(9600);
  Serial.setTimeout(-1);

  sensor.getAddress(therm_id, 0);
  byte_array_to_hex_string(6, therm_id+1, id_string_buffer);
  sensor.requestTemperatures();
  temp_buffer = sensor.getTempCByIndex(0);
}

void loop (){
   char rx_char, mode;
   
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
