/*
#include <SoftwareSerial.h>

// Define GPIO Pins
const byte RX_PIN = 7;
const byte TX_PIN = 8;
const byte LED_PIN = 10;

SoftwareSerial Soft_Serial(RX_PIN, TX_PIN);

String receivedString = ""; // Variable to store the received string

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Soft_Serial.begin(9600); // Initialize Software Serial for communication with Hercules
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Initially turn off the LED

  Serial.println("\n\nWelcome to JP Learning\n");
  Serial.println("Receiver Start\n");

  Serial.print("Initial LED state: ");
  Serial.println(digitalRead(LED_PIN) == HIGH ? "ON" : "OFF");
}

void loop() {
  if (Soft_Serial.available() > 0) {
    receivedString = Soft_Serial.readStringUntil('\n');
    processCommand(receivedString);
  }
}

void processCommand(String command) 
{
  command.trim();
  if (command.equals("ON")) {
    digitalWrite(LED_PIN, LOW); // Turn on the LED
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("\nLED is on");
  }
  else if (command.equals("OFF")) 
  {
    //digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("\nLED is off");
  }
  else 
  {
    Serial.println("\nInvalid command received: " + command); // Print an error message for invalid commands
  }
}
*/
// this is the code of esp32 using rs485tottl module. 
const byte LED_PIN = 2; // Use any GPIO pin for the LED

String receivedString = ""; // Variable to store the received string

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, 1, 3); // Initialize Hardware Serial for communication with Hercules on pins 1 and 3

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Initially turn off the LED

  Serial.println("\n\nWelcome to JP Learning\n");
  Serial.println("Receiver Start\n");

  Serial.print("Initial LED state: ");
  Serial.println(digitalRead(LED_PIN) == HIGH ? "ON" : "OFF");
}

void loop() {
  if (Serial1.available() > 0) {
    receivedString = Serial1.readStringUntil('\n');
    processCommand(receivedString);
  }
}

void processCommand(String command) {
  command.trim();
  if (command.equals("ON")) {
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.print("\nLED is on");
  }
  else if (command.equals("OFF")) {
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.print("\nLED is off");
  }
  else {
    Serial.println("\nInvalid command received: " + command); // Print an error message for invalid commands
  }
}


