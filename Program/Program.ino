<<<<<<< HEAD
#define red 3
#define green 10

String Rcvd_string = "";
char *Rcvd_string_arr[10];
char TokenNr = 0;

char FindTokens(String str){
  char string[20];
  char *ptr = NULL;
  char ctr = 0;
  str.toCharArray(string, str.length()+1);
  ptr = strtok(string, " ");
  while(ptr != NULL){
    Rcvd_string_arr[ctr] = ptr;
    ctr++;
    ptr = strtok(NULL, " ");
  }
  return ctr;
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Hello!");
}

void loop (){
  if (Serial.available()>0){
    Rcvd_string = Serial.readStringUntil('\n');
    TokenNr = FindTokens(Rcvd_string);
    if (strcmp(Rcvd_string_arr[0], "red") == 0){
      if (strcmp(Rcvd_string_arr[1], "on") == 0){
        digitalWrite(red, HIGH);
      }
      else if (strcmp(Rcvd_string_arr[1], "off") == 0){
        digitalWrite(red, LOW);
      }
    }
    else if (strcmp(Rcvd_string_arr[0], "green") == 0){
      if (strcmp(Rcvd_string_arr[1], "on") == 0){
        digitalWrite(green, HIGH);
      }
      else if (strcmp(Rcvd_string_arr[1], "off") == 0){
        digitalWrite(green, LOW);
      }
    }
  }
}
=======
#define red 3
#define green 10

String Rcvd_string = "";
char *Rcvd_string_arr[10];
char TokenNr = 0;

char FindTokens(String str){
  char string[20];
  char *ptr = NULL;
  char ctr = 0;
  str.toCharArray(string, str.length()+1);
  ptr = strtok(string, " ");
  while(ptr != NULL){
    Rcvd_string_arr[ctr] = ptr;
    ctr++;
    ptr = strtok(NULL, " ");
  }
  return ctr;
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Hello!");
}

void loop (){
  if (Serial.available()>0){
    Rcvd_string = Serial.readStringUntil('\n');
    TokenNr = FindTokens(Rcvd_string);
    if (strcmp(Rcvd_string_arr[0], "red") == 0){
      if (strcmp(Rcvd_string_arr[1], "on") == 0){
        digitalWrite(red, HIGH);
      }
      else if (strcmp(Rcvd_string_arr[1], "off") == 0){
        digitalWrite(red, LOW);
      }
    }
    else if (strcmp(Rcvd_string_arr[0], "green") == 0){
      if (strcmp(Rcvd_string_arr[1], "on") == 0){
        digitalWrite(green, HIGH);
      }
      else if (strcmp(Rcvd_string_arr[1], "off") == 0){
        digitalWrite(green, LOW);
      }
    }
  }
}
>>>>>>> ec0aada05b1ff1eb581cff47ba49e4e28180c423
