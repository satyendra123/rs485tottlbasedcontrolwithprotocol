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

