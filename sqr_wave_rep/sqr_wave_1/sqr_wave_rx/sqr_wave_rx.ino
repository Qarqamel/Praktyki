//unsigned int counter = 0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(2, INPUT);
  Serial.begin(9600);
  Serial.setTimeout(-1);
  attachInterrupt(digitalPinToInterrupt(2), Interrupt_Routine, RISING);
}

unsigned int counter = 0;

void Interrupt_Routine(){
  Serial.println(counter++);
}

void loop() {
  // put your main code here, to run repeatedly:
}
