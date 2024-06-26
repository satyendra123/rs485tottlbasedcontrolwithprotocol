// EXAMPLE-1 i have not connect the arduino with the arduino cable. in this code i simply connect the rs485tottl with the rs485tousb cable and read the data serially in docklight software
// in the docklight software i am getting the count value in decimal. remember one thing the rs485 to usb will be connected with the rs485tottl A to A and B to B. never get confused in this. it also work when i have not connected the rs485tousb gnd pin with rs485tottl gnd pin
/*
  Welcome to JP Learning
*/
/*
#include <SoftwareSerial.h>

// GPIO Pins
byte TX_PIN = 8, RX_PIN = 7;
byte LED_PIN = 2;

SoftwareSerial Soft_Serial(RX_PIN, TX_PIN);

long counter = 0;
void setup() {
  Serial.begin(115200);
  Soft_Serial.begin(115200);

  //pinMode(DE_RE_PIN, OUTPUT);     //DE/RE Controling pin of RS-485
  //digitalWrite(DE_RE_PIN, HIGH);  //DE/RE=HIGH Transmit Enabled
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  Serial.println("\n\nWelcome to JP Learning\n");
  Serial.println("Sender Start\n");
}
void loop() {
  counter++;
  Serial.println("counter = " + String(counter));
  Soft_Serial.write(counter);
  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
}
*/
/*
#include <SoftwareSerial.h>

// Define GPIO Pins
const byte RX_PIN = 7; // Connect to the TX pin of Hercules or the device you're communicating with
const byte TX_PIN = 8; // Connect to the RX pin of Hercules or the device you're communicating with
const byte LED_PIN = 13; // Define the pin connected to the LED

SoftwareSerial Soft_Serial(RX_PIN, TX_PIN);

String commandBuffer = ""; // Buffer to store received command

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Soft_Serial.begin(9600); // Initialize Software Serial for communication with Hercules
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initially turn off the LED

  Serial.println("\n\nWelcome to JP Learning\n");
  Serial.println("Receiver Start\n");

  // Debugging message to indicate LED state at startup
  Serial.print("Initial LED state: ");
  Serial.println(digitalRead(LED_PIN) == HIGH ? "ON" : "OFF");
}

void loop() {
  while (Soft_Serial.available()) {
    char receivedChar = Soft_Serial.read(); // Read the incoming character from Hercules
    Serial.print(receivedChar); // Print received characters for debugging
    
    if (receivedChar != '\r' && receivedChar != '\n') { // Ignore carriage return and newline characters
      processCommand(receivedChar); // Process the received command
    }
  }
}

void processCommand(char command) {
  if (command == 'N') { // Assuming 'N' is received for "ON" command
    digitalWrite(LED_PIN, HIGH); // Turn on the LED
    Serial.println("\nLED is on");
  } else if (command == 'F') { // Assuming 'F' is received for "OFF" command
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("\nLED is off");
  } else {
    Serial.println("\nInvalid command received: " + String(command)); // Print an error message for invalid commands
  }
}
*/
//EXAMPLE-3 when i send the command from the hercules serial ON then the LED is on and when i send the command OFF then led is OFF. i have used the rs485tottl module and connect this with the rs485tousb. and send the data from hercules software. i have not connected anywhere arduino usb cable.
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
    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("\nLED is on");
    Soft_Serial.write("\nBARRIER IS OPEN");
  }
  else if (command.equals("OFF")) 
  {
    //digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("\nLED is off");
    Soft_Serial.write("\nLED is off");
  }
  else 
  {
    Serial.println("\nInvalid command received: " + command); // Print an error message for invalid commands
  }
}

// this is the python code jisse mai apne arduino ko serially control karunga rs485tousb ke through. mera rs485tousb com6 se connect hai.
import serial
import time
serial_port = 'COM6'
baud_rate = 9600
ser = serial.Serial(serial_port, baud_rate, timeout=1)
def send_command(command):
    ser.write(command.encode())

time.sleep(2)
try:
    while True:
        print("Sending command: ON")
        send_command("ON\n")    
        time.sleep(2)
        print("Sending command: OFF")
        send_command("OFF\n")
        time.sleep(2)

except KeyboardInterrupt:
    ser.close()


// the same thing i will do using the esp32 module
      // Define GPIO Pins
const byte RX_PIN = 16; // Any GPIO pin can be used
const byte TX_PIN = 17; // Any GPIO pin can be used
const byte LED_PIN = 2; // Built-in LED pin on most ESP32 boards

String receivedString = ""; // Variable to store the received string

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize Hardware Serial1 for communication with Hercules
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initially turn off the LED

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
    Serial.println("\nLED is on");
  }
  else if (command.equals("OFF")) 
  {
    digitalWrite(LED_PIN, LOW); // Turn off the LED
    Serial.println("\nLED is off");
  }
  else 
  {
    Serial.println("\nInvalid command received: " + command); // Print an error message for invalid commands
  }
}
Note- connect the rx and tx pin of rs485tottl module pin 16 and 17.
// this is my micropython code for rs485tottl module
  from machine import Pin, UART
import time

# Define GPIO Pins
RX_PIN = 16  # Any GPIO pin can be used
TX_PIN = 17  # Any GPIO pin can be used
LED_PIN = 2  # Built-in LED pin on most ESP32 boards

# Initialize UART
uart = UART(1, baudrate=9600, tx=TX_PIN, rx=RX_PIN)

# Define function to process received command
def process_command(command):
    command = command.strip()
    if command == b'ON':
        led.value(1)  # Turn on the LED
        print("LED is on")
    elif command == b'OFF':
        led.value(0)  # Turn off the LED
        print("LED is off")
    else:
        print("Invalid command received:", command)

# Initialize LED pin
led = Pin(LED_PIN, Pin.OUT)
led.value(0)  # Initially turn off the LED

print("\n\nWelcome to JP Learning\n")
print("Receiver Start\n")

# Main loop
while True:
    if uart.any():
        received_data = uart.readline()
        process_command(received_data)
    time.sleep(0.1)


