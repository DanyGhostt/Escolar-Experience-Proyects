# ⚡ Escolar Experience Projects | Microcontrollers Laboratory

<div align="center">

![ESP32](https://img.shields.io/badge/ESP32-Espressif-red?style=for-the-badge&logo=espressif)
![AVR](https://img.shields.io/badge/AVR-Microchip-blue?style=for-the-badge&logo=arduino)
![C++](https://img.shields.io/badge/C%2B%2B-Arduino-00599C?style=for-the-badge&logo=cplusplus)
![Assembly](https://img.shields.io/badge/Assembly-AVR%20ASM-6E4C13?style=for-the-badge)
![IoT](https://img.shields.io/badge/IoT-Thinger.io-009688?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

<p align="center">
  <b>[ES]</b> Repositorio de proyectos y prácticas de laboratorio de sistemas embebidos y microcontroladores (ESP32 / AVR), abarcando desde control en ensamblador y periféricos básicos hasta IoT, servidores web y telemetría en tiempo real.<br>
  <b>[EN]</b> Embedded systems and microcontroller laboratory practices portfolio (ESP32 / AVR), ranging from low-level assembly control and basic peripherals to IoT, web servers, and real-time telemetry.
</p>

</div>

---

## 📋 Índice de Prácticas / Practice Index

| # | Directorio / Directory | Descripción [ES] | Description [EN] | Hardware & Protocolos |
|:---:|:---|:---|:---|:---|
| **01** | [`Practica_01_Semaforo_Ensamblador_ASM`](./Practica_01_Semaforo_Ensamblador_ASM/) | Semáforo vehicular y peatonal en lenguaje ensamblador AVR con retardos por software. | AVR Assembly vehicular and pedestrian traffic light with software delay loops. | Microchip AVR / ATmega, LEDs |
| **02** | [`Practica_02_Semaforo_OLED`](./Practica_02_Semaforo_OLED/) | Semáforo con pantalla OLED I2C y cuenta regresiva peatonal. | Traffic light system with I2C OLED display and pedestrian countdown. | ESP32, OLED SSD1306 (128x64), LEDs, Buzzer |
| **03** | [`Practica_03_Maquina_Estados_FSM_OLED`](./Practica_03_Maquina_Estados_FSM_OLED/) | Máquina de estados finitos (FSM) con menú interactivo y gráficos animados en OLED. | Finite State Machine (FSM) with interactive menu navigation and animated OLED graphics. | ESP32, OLED SSD1306, Pushbuttons |
| **04** | [`Practica_04_Encoder_OLED`](./Practica_04_Encoder_OLED/) | Lectura de encoder rotativo mediante interrupciones de hardware (ISR) y visualización en OLED. | Rotary encoder decoding via hardware interrupts (ISR) with OLED real-time visualization. | ESP32, Rotary Encoder (KY-040), OLED SSD1306 |
| **05** | [`Practica_05_Metronomo_Buzzer_OLED`](./Practica_05_Metronomo_Buzzer_OLED/) | Metrónomo digital programable por BPM con buzzer pasivo, OLED y control por botones. | Digital programmable BPM metronome with passive buzzer, OLED display, and button controls. | ESP32, Buzzer Pasivo, OLED SSD1306, Pushbuttons |
| **06** | [`Practica_06_Reloj_Digital_OLED`](./Practica_06_Reloj_Digital_OLED/) | Reloj digital con cronómetro, temporizador y alarma con formato 12h/24h. | Digital clock with stopwatch, countdown timer, and alarm supporting 12h/24h formats. | ESP32, OLED SSD1306, Pushbuttons, Buzzer |
| **07** | [`Practica_07_Sensores_Temp_LDR_Humedad_OLED`](./Practica_07_Sensores_Temp_LDR_Humedad_OLED/) | Estación meteorológica con sensor DHT11, fotorresistencia LDR y pantalla OLED. | Weather monitoring station using DHT11 sensor, LDR photoresistor, and OLED display. | ESP32, DHT11, LDR, OLED SSD1306 |
| **08** | [`Practica_08_Control_Motor_PWM_OLED`](./Practica_08_Control_Motor_PWM_OLED/) | Control de velocidad y sentido de giro de motor DC con puente H (L298N/L293D) y modulación PWM. | DC motor speed and direction control using H-Bridge driver with PWM modulation and OLED telemetry. | ESP32, Driver Puente H (L298N), Motor DC, OLED |
| **09** | [`Practica_09_Adquisicion_Datos_PLX_DAQ_Excel`](./Practica_09_Adquisicion_Datos_PLX_DAQ_Excel/) | Sistema de adquisición de datos (DAQ) en tiempo real exportando lecturas a Microsoft Excel vía PLX-DAQ. | Real-time Data Acquisition (DAQ) exporting sensor telemetry to Microsoft Excel via PLX-DAQ serial stream. | ESP32 / Arduino, Sensores analógicos, PLX-DAQ Excel |
| **09** | [`Practica_09_PLX_DAQ_ESP32_Alternativo`](./Practica_09_PLX_DAQ_ESP32_Alternativo/) | Variante de adquisición de datos DAQ con ESP32 para transmisión serie formateada a Excel. | Alternate ESP32 DAQ data acquisition variant for formatted serial stream to Excel. | ESP32, Sensores analógicos, PLX-DAQ |
| **10** | [`Practica_10_Control_Bluetooth_OLED`](./Practica_10_Control_Bluetooth_OLED/) | Control de actuadores y telemetría inalámbrica mediante Bluetooth Serial clásico (SPP). | Actuator remote control and telemetry over classic Bluetooth Serial (SPP). | ESP32 (Bluetooth Serial), OLED SSD1306, LEDs |
| **11** | [`Practica_11_Reloj_NTP_Alarma_WiFi_OLED`](./Practica_11_Reloj_NTP_Alarma_WiFi_OLED/) | Sincronización horaria por Internet mediante protocolo NTP (Network Time Protocol) con alarma y OLED. | Internet time synchronization via NTP (Network Time Protocol) with active alarm and OLED UI. | ESP32 (WiFi), NTP Server Pool, OLED SSD1306, Buzzer |
| **11** | [`Practica_11_Reloj_NTP_Alarma_v2`](./Practica_11_Reloj_NTP_Alarma_v2/) | Reloj y alarma sincronizados por NTP con control horario autónomo. | NTP synchronized clock and alarm with autonomous timekeeping routines. | ESP32 (WiFi), NTP Server Pool, Buzzer |
| **12** | [`Practica_12_Servidor_Web_WiFi_LEDs`](./Practica_12_Servidor_Web_WiFi_LEDs/) | Servidor web HTTP embebido para monitoreo y control de cargas digitales desde el navegador. | Embedded HTTP Web Server for browser-based actuator control and telemetry. | ESP32 (WiFi WebServer), LEDs |
| **12** | [`Practica_12_Servidor_Web_WiFi_LEDs_OLED`](./Practica_12_Servidor_Web_WiFi_LEDs_OLED/) | Servidor web HTTP con interfaz gráfica OLED para visualización de IP y estados. | HTTP web server with OLED graphical status and network IP visualization. | ESP32 (WiFi WebServer), OLED SSD1306, LEDs |
| **12** | [`Practica_12_Servidor_Web_WiFi_Basico`](./Practica_12_Servidor_Web_WiFi_Basico/) | Servidor web HTTP básico para control de actuadores en red local. | Basic HTTP web server for local network actuator control. | ESP32 (WiFi WebServer), LEDs |
| **13** | [`Practica_13_IoT_Thinger_IO_ESP32`](./Practica_13_IoT_Thinger_IO_ESP32/) | Integración con plataforma en la nube Thinger.io: control de 4 salidas y monitoreo de 4 pulsadores. | Cloud IoT integration using Thinger.io: 4 remote output channels & 4 digital input telemetry streams. | ESP32 (WiFi), Thinger.io Cloud Platform, LEDs, Pushbuttons |

---

## 🛠️ Requisitos de Software / Software Requirements

1. **Arduino IDE** (v2.0 o superior recomendado)
2. **Placas Compatibles / Board Packages:**
   - `esp32` by Espressif Systems
   - `Arduino AVR Boards`
3. **Librerías Requeridas / Required Libraries:**
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
   - `DHT sensor library`
   - `ThingerESP32`

---

## 🚀 Instrucciones de Uso / Getting Started

### [ES] Instrucciones
1. Abre la carpeta de la práctica deseada en el Arduino IDE (el archivo `.ino` coincide con el nombre de su carpeta contenedora).
2. Para las prácticas que usan WiFi o IoT (Prácticas 11, 12 y 13), actualiza las credenciales de red (`WIFI_SSID` y `WIFI_PASSWORD`) o las credenciales del servidor IoT (`arduino_secrets.h`).
3. Selecciona tu placa y el puerto COM correspondiente.
4. Compila y carga el código a la placa de desarrollo.

### [EN] Instructions
1. Open the desired practice sketch in Arduino IDE (the `.ino` file matches the name of its enclosing folder).
2. For practices requiring WiFi or Cloud connectivity (Practices 11, 12, and 13), update the network credentials (`WIFI_SSID` and `WIFI_PASSWORD`) or IoT platform keys (`arduino_secrets.h`).
3. Select your target board and COM port.
4. Compile and flash the firmware to your development board.
