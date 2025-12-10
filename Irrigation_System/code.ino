const int soilDO = 6;      // Soil sensor digital output
const int relayPin = 3;    // Relay control pin

void setup() {
  Serial.begin(9600);

  pinMode(soilDO, INPUT);
  pinMode(relayPin, OUTPUT);

  // Relay OFF initially (Active LOW relay)
  digitalWrite(relayPin, HIGH);
}

void loop() {

  int soilState = digitalRead(soilDO);

  if (soilState == HIGH) {
    // Soil is dry → pump ON
    digitalWrite(relayPin, LOW); // Active LOW relay
    Serial.println("Soil Dry → Pump ON");
  } 
  else {
    // Soil is wet → pump OFF
    digitalWrite(relayPin, HIGH); 
    Serial.println("Soil Wet → Pump OFF");
  }

  delay(500);
}
