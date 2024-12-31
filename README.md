
# Flash Memory Reader with ESP32

This ESP32 project demonstrates how to read the entire memory content of a flash chip in chunks using SPI communication. It includes functions to read the flash chip ID and to print memory contents in a readable format.

## Features
- Reads and displays the flash chip ID.
- Reads flash memory in configurable chunks.
- Outputs data to the Serial Monitor.

## Hardware Requirements
- ESP32 Microcontroller
- SPI Flash Chip (compatible with standard SPI protocol)
- Jumper wires

## Pinout for ESP32
```markdown
| ESP32 Pin | Flash Chip Pin | Description                  |
|-----------|----------------|------------------------------|
| GPIO 5    | CS             | Chip Select                  |
| GPIO 18   | SCLK           | Serial Clock                 |
| GPIO 19   | MISO           | Master In Slave Out          |
| GPIO 23   | MOSI           | Master Out Slave In          |
| GND       | GND            | Ground                       |
| 3.3V      | VCC            | Power Supply for Flash Chip  |
```
## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/lahirunirmalx/spi-eeprom-tool.git
   ```
2. Open the ` src/main.cpp` file in the Arduino IDE or PlatformIO.
3. Install the ESP32 board package:
   - In the Arduino IDE, go to **File > Preferences** and add the following URL in the "Additional Board Manager URLs" field: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Then, go to **Tools > Board > Boards Manager**, search for `ESP32`, and install the package.
4. Set the correct COM port and board in the IDE:
   - Select **Tools > Board > ESP32 Dev Module** (or your specific ESP32 board).
   - Choose the correct port under **Tools > Port**.
5. Upload the sketch to your ESP32.

## Usage
1. Wire your ESP32 to the flash chip as per the pinout table.
2. Power on the ESP32 and connect it to your computer.
3. Open the Serial Monitor at a baud rate of 115200.
4. View the flash chip ID and memory contents.

## Configuration
- **Chip Select Pin**: Ensure `CS_PIN` is correctly set in the code to match your wiring.
- **Flash Size**: Update `FLASH_SIZE` in the code to match your flash chip's memory capacity.
- **Chunk Size**: Modify `CHUNK_SIZE` for reading memory in smaller or larger chunks.

## Example Output
```
Reading Flash Chip ID...
Flash Chip ID:
Manufacturer ID: 0xEF
Memory Type: 0x40
Capacity: 0x15

Reading Flash Memory in Chunks...
Address: 0x000000
00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
...
Finished reading flash memory.
```

## Notes
- Ensure your flash chip operates at 3.3V to avoid damaging it or your ESP32.
- Double-check your wiring, especially for `CS`, `SCLK`, `MISO`, and `MOSI` connections.

## License
This project is open source and available under the MIT License.

## Contributions
Contributions are welcome! Please open an issue or submit a pull request for improvements or bug fixes.

 
```
