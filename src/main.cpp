#include <Arduino.h>
#include <SPI.h>
#include <main.h> 

#define CS_PIN 5               // Chip Select Pin for the flash chip
#define FLASH_SIZE 512 * 1024  // Flash size in bytes (4Mbit = 512KB)
#define CHUNK_SIZE 256         // Number of bytes to read per chunk

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, CS_PIN); // SCLK, MISO, MOSI, CS
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  // Optional: Verify the connection by reading the chip ID
  readFlashID();

  // Read the entire flash memory in chunks
  readFlashByChunk();
}

void readFlashID() {
  Serial.println("Reading Flash Chip ID...");
  digitalWrite(CS_PIN, LOW); // Select the flash chip
  SPI.transfer(0x9F);        // Send "Read ID" command

  byte manufacturerID = SPI.transfer(0x00);
  byte memoryType = SPI.transfer(0x00);
  byte capacity = SPI.transfer(0x00);

  digitalWrite(CS_PIN, HIGH); // Deselect the flash chip

  Serial.println("Flash Chip ID:");
  Serial.print("Manufacturer ID: 0x");
  Serial.println(manufacturerID, HEX);
  Serial.print("Memory Type: 0x");
  Serial.println(memoryType, HEX);
  Serial.print("Capacity: 0x");
  Serial.println(capacity, HEX);
}

void readFlashByChunk() {
  Serial.println("Reading Flash Memory in Chunks...");

  const uint32_t startAddress = 0x000000;   // Start from address 0
  const uint32_t endAddress = FLASH_SIZE;  // Read up to the chip's capacity
  byte buffer[CHUNK_SIZE];                 // Buffer to store chunk data

  uint32_t currentAddress = startAddress;

  while (currentAddress < endAddress) {
    uint32_t chunkLength = (currentAddress + CHUNK_SIZE <= endAddress)
                               ? CHUNK_SIZE
                               : endAddress - currentAddress;

    // Read a chunk of data
    readFlash(currentAddress, buffer, chunkLength);

    // Print the chunk data to the serial monitor
    //Serial.printf("Address: 0x%06X\n", currentAddress);
    for (uint16_t i = 0; i < chunkLength; i++) {
      if (i % 16 == 0) Serial.println(); // New line every 16 bytes
      Serial.printf("%02X ", buffer[i]);
    }
    Serial.println("\n");

    currentAddress += chunkLength;
  }

  Serial.println("Finished reading flash memory.");
}

void readFlash(uint32_t address, byte *buffer, uint32_t length) {
  digitalWrite(CS_PIN, LOW); // Select the flash chip
  
  SPI.transfer(0x03); // Send "Read Data" command (0x03 for sequential read)

  // Send 24-bit address (MSB first)
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);

  // Sequentially read the specified length of bytes
  for (uint32_t i = 0; i < length; i++) {
    buffer[i] = SPI.transfer(0x00); // Read data byte-by-byte
  }

  digitalWrite(CS_PIN, HIGH); // Deselect the flash chip
}

void loop() {
  // Leave the loop empty
}
 