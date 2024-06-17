#include <ArduinoRS485.h>

const int DE_RE_PIN = 2;       
const int STRING_SIZE = 40;
char response[STRING_SIZE] = "This is a fixed 40-byte response string.";

void setup() {
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);        // recieve mode

  // rs485 init
  Serial.begin(9600);          
  RS485.begin(9600);
}

void loop() {
  // check read data from RS485
  if (RS485.available()) {
  // reading data
    while (RS485.available()) {
      char incomingByte = RS485.read();
      Serial.print("Received: ");
      Serial.println(incomingByte); 
    }

    // switching to transmit mode
    Serial.println("Switching to transmit mode");
    digitalWrite(DE_RE_PIN, HIGH);
    delay(1000);                       // increased delay for switching

    // send a reply string
    RS485.write(response, STRING_SIZE);
    RS485.flush();                     // waiting for the end of the transfer
    Serial.println("Response sent");

    // back to receiving mode
    digitalWrite(DE_RE_PIN, LOW);
    delay(1000);                       // increased delay for switching
    Serial.println("Switching to receive mode");
  }
}