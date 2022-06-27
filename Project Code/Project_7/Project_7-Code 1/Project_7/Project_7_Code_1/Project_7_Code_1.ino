char ble_val; 
void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) 
  {
    ble_val = Serial.read();  
    Serial.println(ble_val);  
  }
}
