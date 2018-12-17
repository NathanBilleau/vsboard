void setup() {
  Serial.begin(9600);
  String hexstring = "0059c5a1";

  long number = (long) strtol( &hexstring[0], NULL, 16);

  Serial.println(number);
  Serial.println(number, HEX);
}

void loop() {

}
