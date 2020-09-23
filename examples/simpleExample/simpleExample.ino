
#define send_pin PB0
#define receive_pin PA0

volatile unsigned long last_tim;
unsigned long tim = 0;

void inter()
{

  last_tim = micros();

}

void setup() {
  Serial.begin(250000);
  pinMode(send_pin, OUTPUT);
  pinMode(receive_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(receive_pin), inter, RISING);

}

void loop() {
  delay(100);
  digitalWrite(send_pin, LOW);
  delay(100);
  digitalWrite(send_pin, HIGH);
  last_tim = 0;
  tim = micros();
  while (last_tim == 0 && micros() - tim < 200000)
  {
    Serial.print("t ");
    Serial.println(tim);

  }
  Serial.println(last_tim - tim);

}
