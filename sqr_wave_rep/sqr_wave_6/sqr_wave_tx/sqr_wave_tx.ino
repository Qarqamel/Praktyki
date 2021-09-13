
unsigned int last_read = micros();

void Interrupt_Routine(){
  Serial.println(micros()-last_read);
  last_read = micros();  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  tone(2, 100);
  Serial.begin(115200);
  Serial.setTimeout(-1);
  attachInterrupt(digitalPinToInterrupt(5), Interrupt_Routine, RISING);
}

void loop() {
}
