# ESP32 Smart Home Gas and Water Tank Level Monitoring System — Parent Safety Alert

This project monitors gas and household tank water level, updates a mobile app, and supports app commands to switch a light and an audio appliance on or off.

## Functions and data flow

- Gas sensor and tank-level inputs → ESP32 → Wi-Fi/app update.
- Mobile app commands → ESP32 → relay control for light/audio equipment.
- Relay controls power on/off; it does not stream audio or control volume.

The original app, cloud protocol, sensor model, and relay board were not supplied here. The diagram and firmware are generated references using the assumptions below; confirm against the actual build before claiming these exact parts or implementation.

## Circuit diagram

![ESP32 smart-home gas, tank level and appliance-control reference circuit](docs/circuit.svg)

## Assumed reference parts and pins

| Part | Reference connection |
|---|---|
| Classic ESP32 DevKit | Controller and Wi-Fi |
| MQ-2 analog output | 15 kΩ / 22 kΩ divider to GPIO34 ADC |
| Three float switches | Low / mid / high to GPIO26 / 27 / 14, each closing to GND |
| Two-channel isolated relay inputs | GPIO18 / 19 for light / audio power |
| Grounds | Common low-voltage ground where required |

Three float switches indicate discrete level bands, not a precise continuous level. If the actual sensor or app is different, update the reference to match.

## Firmware

src/smart_home_monitor.ino demonstrates gas sampling, discrete tank-level sensing, and low-voltage relay-control hooks. The mobile-app/cloud adapter is intentionally a placeholder because the app platform was not identified. Keep Wi-Fi/app credentials out of this public repository.

The MQ-2 value is raw ADC, not ppm; its threshold is a placeholder that needs calibration for the exact module and controlled conditions.

## Safety

**This reference is not a certified gas alarm and must not be relied on for life safety or property protection. Keep a certified gas detector in use.** Do not release flammable gas to test the sensor.

The diagram shows low-voltage control only, not household mains wiring. A qualified electrician must install and check mains-rated relay and appliance wiring; keep mains isolated from the ESP32 and follow relay ratings/local code.

## Interview summary

“My ESP32 home-monitoring project monitors gas and tank water level, updates a mobile app, and lets the app switch a light and audio-system power channel. It combines sensor interfacing, Wi-Fi/app communication, and isolated output control.” Describe the actual app, sensors, relays, and tests you personally used.

## Author

Abinavu M — Electronics and Communication Engineering student focused on embedded systems and IoT.
