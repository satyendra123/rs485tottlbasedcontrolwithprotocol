/*
const int LED_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() >= 2) { // Wait for at least 2 bytes (1 byte for each hexadecimal digit)
    char command[2];
    Serial.readBytes(command, 2); // Read 2 bytes (2 hexadecimal digits)
    
    // Convert hexadecimal digits to integer
    int value = strtol(command, NULL, 16);
    
    // Check the value and control the LED accordingly
    if (value == 0x00) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is off");
      Serial.write("0xaa 0xab 0xac 0xde");
    } else if (value == 0x01) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is on");
      Serial.write("0xaa 0xab 0xac 0xde");
    } else {
      Serial.println("Invalid command");
    }
  }
}
*/
// i am sending the data from hercules software serially and control the relay. when i send the hex data 00 then led turn on and if i send 00 then led is turned off. but 
// remember one thing if your arduino connect in com22 then the hercules serially also connects with com22. AA 00 AC led off and AA 01 AC led on


// Pin connected to LED
const int ledPin = 13;

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if there are bytes available to read
  if (Serial.available() >= 3) {
    // Read the first byte
    byte head = Serial.read();
    
    // Check if the first byte matches the head communication (0xAA)
    if (head == 0xAA) {
      // Read the second byte
      byte data = Serial.read();
      
      // Read the third byte
      byte tail = Serial.read();
      
      // Check if the third byte matches the tail communication (0xAC)
      if (tail == 0xAC) {
        // Control LED based on the second byte
        if (data == 0x01) {
          // Turn on the LED
          digitalWrite(ledPin, HIGH);
          Serial.println("LED ON");
        } else if (data == 0x00) {
          // Turn off the LED
          digitalWrite(ledPin, LOW);
          Serial.println("LED OFF");
        }
      }
    }
  }
}

//EXAMPLE-3 when i send the command AA 01 AC from the docklight then led connected to pin number 13 will be glow. and if i send AA 00 AC then led will be turned off
/*
// Pin connected to LED
const int ledPin = 13;

// Define a struct for your data
struct CommunicationData {
  byte start;
  byte counter;
  byte end;
};

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if there are bytes available to read
  if (Serial.available() >= sizeof(CommunicationData)) {
    // Read the bytes into the struct
    CommunicationData receivedData;
    Serial.readBytes((char*)&receivedData, sizeof(CommunicationData));
    
    // Check if the received data is valid
    if (receivedData.start == 0xAA && receivedData.end == 0xAC) {
      // Control LED based on the counter value
      if (receivedData.counter == 0x01) {
        // Turn on the LED
        digitalWrite(ledPin, HIGH);
      } else if (receivedData.counter == 0x00) {
        // Turn off the LED
        digitalWrite(ledPin, LOW);
      }
      
      // Send back the received data
      Serial.write((byte*)&receivedData, sizeof(CommunicationData));
    }
  }
}

//Example-4 
/*
// Pin connected to LED
const int ledPin = 13;

// Define a struct for your data
struct CommunicationData {
  byte start;
  byte address;
  byte end;
};

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Seed the random number generator
  randomSeed(analogRead(0));
}

void loop() {
  // Check if there are bytes available to read
  if (Serial.available() >= sizeof(CommunicationData)) {
    // Read the bytes into the struct
    CommunicationData receivedData;
    Serial.readBytes((char*)&receivedData, sizeof(CommunicationData));
    
    // Check if the received data is valid
    if (receivedData.start == 0xAA && receivedData.end == 0xAC && receivedData.address == 0x01) {
      // Generate a random value (0x01 for ON, 0x00 for OFF)
      byte sensorValue = random(2); // Generates a random number between 0 and 1
      
      // Send back the received data with sensor value
      Serial.write(0xAA); // Start byte
      Serial.write(receivedData.address); // Address
      Serial.write(sensorValue); // Sensor value
      Serial.write(0xAC); // End byte
    }
  }
}
*/
// Example-5 when it gets the request AA 01 AC then it sends back the static response. in the next example i will send the dynamic response
/*
void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  // Define the command to be received
  byte command[] = {0xAA, 0x01, 0xAC};
  byte receivedCommand[3]; // Array to store received bytes

  // Wait until the command is received
  if (Serial.available() >= 3) {
    // Read the received bytes into the receivedCommand array
    for (int i = 0; i < 3; i++) {
      receivedCommand[i] = Serial.read();
    }
    
    // Check if the received command matches the expected command
    if (memcmp(receivedCommand, command, 3) == 0) {
      // Send the response
      byte response[] = {0x7E, 0x00, 0x78, 0xF0, 0x7E};
      Serial.write(response, sizeof(response));
    }
  }
}
*/
// Example-6 In this code i am sending the dynamic data to docklight when it gets the request by AA 01 AC.
/*
// Define the packet structure
struct Packet {
  byte startByte;
  byte endByte;
  byte address;
  byte status;
};


void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  // Define the command to be received
  byte command[] = {0xAA, 0x01, 0xAC};
  byte receivedCommand[3]; // Array to store received bytes

  // Wait until the command is received
  if (Serial.available() >= 3) {
    // Read the received bytes into the receivedCommand array
    for (int i = 0; i < 3; i++) {
      receivedCommand[i] = Serial.read();
    }
    
    // Check if the received command matches the expected command

    // Create a packet
  Packet packetToSend;
  packetToSend.startByte = 0x7E;
  packetToSend.endByte = 0x7E;
  packetToSend.address = 0x00; // Address can be any value
  packetToSend.status = 0xF0; // Status can be any value


    if (memcmp(receivedCommand, command, 3) == 0) {
      // Send the response
        // Send the packet
      Serial.write((byte*)&packetToSend, sizeof(packetToSend));
      delay(1000); // Delay for readability, adjust as needed
    }
  }
}
*/

/*
//Example-7 AA 01 17 03 31 32 33 8C. when it received these protocol then i need to extract the byte 31 33 33 and convert it to ascii code which is 123 and if it receive 123 then turn on the led.
const int ledPin = 13;

// Define a struct for your data
struct CommunicationData {
  byte start;
  byte address;
  byte command;
  byte length;
  byte data[3]; // Array to store 3 bytes of data
  byte checksum;
};

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if there are bytes available to read
  if (Serial.available() >= sizeof(CommunicationData)) {
    // Read the bytes into the struct
    CommunicationData receivedData;
    Serial.readBytes((char*)&receivedData, sizeof(CommunicationData));
    
    // Verify if the received data is valid
    if (receivedData.start == 0xAA && receivedData.checksum == 0x8C && receivedData.length == 3) {
      // Verify if the received command is 0x17 and length is 3
      if (receivedData.command == 0x17 && receivedData.length == 3) {
        // Convert the received data to ASCII characters
        char receivedChars[4]; // Extra byte for null terminator
        for (int i = 0; i < 3; i++) {
          receivedChars[i] = receivedData.data[i];
        }
        receivedChars[3] = '\0'; // Null terminate the string
        
        // Check if the received data is "123"
        if (strcmp(receivedChars, "123") == 0) {
          // Turn on the LED
          digitalWrite(ledPin, HIGH);
        } else {
          // Turn off the LED
          digitalWrite(ledPin, LOW);
        }
      }
    }
    
    // Send back the received data
    Serial.write((byte*)&receivedData, sizeof(CommunicationData));
  }
}
*/