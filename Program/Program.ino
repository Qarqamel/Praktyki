void setup() {
  //sensor.begin();
    
  Serial.begin(9600);
  Serial.setTimeout(-1);
}

void loop (){

  char Rcvd_char[1];

  Serial.readBytes(Rcvd_char, 1);
  if(Rcvd_char[0] != '\n'){
    Serial.print(Rcvd_char);
  }
  else{
    Serial.println(";0123456789ab 30.00");
  }
}
