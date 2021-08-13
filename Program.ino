String Rcvd_string;
char Rcvd_char_arr[20];

void setup() {  
  Serial.begin(9600);
  Serial.setTimeout(-1);
  Serial.println("Hello!");
}

void loop (){
  Rcvd_string = Serial.readStringUntil('\n');
  Serial.println("echo_" + Rcvd_string);
}
