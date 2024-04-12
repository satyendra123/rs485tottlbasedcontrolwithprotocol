const int LED_PIN = 13; // Define the pin connected to the LED

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
}

void loop() {
  if (Serial.available() > 0) { // Check if there's data available to read
    String command = Serial.readStringUntil('\n'); // Read the incoming command
    command.trim(); // Remove any leading/trailing whitespace

    // Check the received command and take action accordingly
    if (command == "on") {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED
      Serial.println("LED is on");
    } else if (command == "off") {
      digitalWrite(LED_PIN, LOW); // Turn off the LED
      Serial.println("LED is off");
    } else {
      Serial.println("Invalid command"); // Print an error message for invalid commands
    }
  }
}




/*
// this is the code for python. just remembered that the arduinon port name should be mentioned in the com port. 
import serial
import time

serialcomm = serial.Serial('COM22', 9600)
serialcomm.timeout = 1
while True:
    i = input("Enter Input: ").strip()
    if i == "Done":
        print('finished')
        break
    serialcomm.write(i.encode())
    time.sleep(0.5)
    print(serialcomm.readline().decode('ascii'))
serialcomm.close()
*/