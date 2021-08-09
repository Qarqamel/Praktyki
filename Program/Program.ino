String Rcvd_string = "";
String Prnt_string = "";
char *Prnt_string_arr[10];
char TokenNr = 0;

char FindTokens(String str){
  char string[20];
  char *ptr = NULL;
  char ctr = 0;
  str.toCharArray(string, str.length()+1);
  ptr = strtok(string, " ");
  while(ptr != NULL){
    Prnt_string_arr[ctr] = ptr;
    ctr++;
    ptr = strtok(NULL, " ");
  }
  return ctr;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
}

void loop (){
  if (Serial.available()>0){
    Rcvd_string = Serial.readStringUntil('\n');
    TokenNr = FindTokens(Rcvd_string);
    for(unsigned char i = 0; i<TokenNr; i++){
      Serial.println(Prnt_string_arr[i]);
    }
  }
}
