# Senior Care 👵📡

**Final Project — Internet of Things (IoT) Implementation**
Tecnológico de Monterrey

## Description

Senior Care is an IoT system designed for monitoring and caring for elderly adults, combining an ESP32 microcontroller with connected sensors and a Python backend/processing layer to collect, analyze, and visualize data in real time.

## Authors

- Regina Fernanda Portela Palacios (A01786698)
- Aixa Elenka Mendoza Filisola (A01782727)
- Nicolás Casillas Larrañaga (A01787292)

## Features

- [ ] Monitoring of [variable, e.g. heart rate / temperature / motion]
- [ ] Alerts triggered by [anomalous event]
- [ ] Real-time data dashboard / visualization
- [ ] Historical storage of readings

## System Architecture

```
[Sensors] → [ESP32] → [Communication protocol, e.g. MQTT/WiFi/HTTP] → [Google Sites] → [Storage / Dashboard]

[Python code] -> [MQTT] -> [ESP32]
```

## Hardware Used

- ESP32 microcontroller
- Sensor(s): [Pulse Sensor, DHT22, motion sensor, Distance Sensor]
- [Other components: buzzer, display, battery, LEDs]

## Software & Technologies

- **Firmware:** Arduino / MicroPython (ESP32)
- **Backend / data processing:** Python / ArduinoIDE
- **Project website:** Google Sites

## Repository Structure

```
├── ArduinoCode/          # Microcontroller code
├── Documentation/        # Documentation and report
├── PythonCode/           # Python Signals sent
└── README.md
```
### Prerequisites
- [ ] Arduino IDE or PlatformIO set up for ESP32
- [ ] Python 3.x installed

### Steps
1. Flash the code in `esp32/` to the microcontroller.
2. Configure WiFi credentials and the communication endpoint.
3. Run the main Python script:
   ```bash
   python main.py
   ```

## Project Resources

| Resource | Link |
|---|---|
| Python Code | [Google Drive](https://drive.google.com/file/d/14pP5lvmMPcLNYIoVjw3OE-BZYKoaIwf8/view?usp=sharing) |
| ESP32 Code | [Google Drive](https://drive.google.com/file/d/1obWtx0jt9x1bcoqph0jQ9ztMeYO6dSZd/view?usp=sharing) |
| Project Website | [Google Sites](https://sites.google.com/tec.mx/seniorcare/p%C3%A1gina-principal) |
| Demo Video | [Google Drive](https://drive.google.com/file/d/1HULLVJf2B1XlLYs79hIxWUMKVQmRsdqB/view?usp=drivesdk) |

## License

Academic project — Tecnológico de Monterrey.
