
unsigned long last_read = micros();

void Interrupt_Routine(){
  Serial.println(micros());
  last_read = micros();  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
  tone(5, 400);
  Serial.begin(115200);
  Serial.setTimeout(-1);
  attachInterrupt(digitalPinToInterrupt(2), Interrupt_Routine, RISING);
}

void loop() {
}
