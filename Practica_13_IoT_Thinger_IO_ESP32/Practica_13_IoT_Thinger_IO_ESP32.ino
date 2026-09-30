/* ============================================================================
 * [ES] Practica 13: Plataforma IoT con ESP32 y Thinger.io
 *      Control bidireccional en la nube:
 *      - 4 Salidas digitales (LEDs) controladas remotamente desde el dashboard.
 *      - 4 Entradas digitales (Pulsadores con Pull-up) monitoreadas en tiempo real.
 * 
 * [EN] Practice 13: IoT Cloud Platform with ESP32 & Thinger.io
 *      Bidirectional cloud telemetry and control:
 *      - 4 Digital outputs (LEDs) remotely controlled from the web dashboard.
 *      - 4 Digital inputs (Pushbuttons with Pull-up) monitored in real time.
 * ============================================================================
 */

#include <ThingerESP32.h>

// ============================================================================
// [ES] Credenciales de la plataforma Thinger.io
// [EN] Thinger.io Cloud Platform Credentials
// ============================================================================
#define USERNAME          "YOUR_THINGER_USERNAME"
#define DEVICE_ID         "YOUR_DEVICE_ID"
#define DEVICE_CREDENTIAL "YOUR_DEVICE_CREDENTIAL"

// ============================================================================
// [ES] Credenciales de conexion de red WiFi
// [EN] WiFi Network Connection Credentials
// ============================================================================
#define WIFI_SSID         "YOUR_WIFI_SSID"
#define WIFI_PASSWORD     "YOUR_WIFI_PASSWORD"

// ============================================================================
// [ES] Asignacion de Pines GPIO (Salidas y Entradas)
// [EN] GPIO Pin Assignments (Outputs & Inputs)
// ============================================================================
#define LED_1 12    // [ES] LED 1 / [EN] LED 1
#define LED_2 14    // [ES] LED 2 / [EN] LED 2
#define LED_3 27    // [ES] LED 3 / [EN] LED 3
#define LED_4 13    // [ES] LED 4 / [EN] LED 4

#define BTN_1 32    // [ES] Boton 1 / [EN] Button 1
#define BTN_2 33    // [ES] Boton 2 / [EN] Button 2
#define BTN_3 25    // [ES] Boton 3 / [EN] Button 3
#define BTN_4 26    // [ES] Boton 4 / [EN] Button 4

// ============================================================================
// [ES] Variables de Estado de Salidas (LEDs)
// [EN] Output State Variables (LEDs)
// ============================================================================
bool state_led_1 = false;
bool state_led_2 = false;
bool state_led_3 = false;
bool state_led_4 = false;

// [ES] Instancia del cliente Thinger.io para ESP32
// [EN] Thinger.io client instance for ESP32
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // --------------------------------------------------------------------------
  // [ES] Configuracion de conexion WiFi en el cliente Thinger.io
  // [EN] Configure WiFi connection on the Thinger.io client
  // --------------------------------------------------------------------------
  thing.add_wifi(WIFI_SSID, WIFI_PASSWORD);

  // --------------------------------------------------------------------------
  // [ES] Configuracion de pines de salida (LEDs)
  // [EN] Configure output pins (LEDs)
  // --------------------------------------------------------------------------
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  // --------------------------------------------------------------------------
  // [ES] Configuracion de pines de entrada con resistencia Pull-up interna
  // [EN] Configure input pins with internal Pull-up resistors
  // --------------------------------------------------------------------------
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BTN_3, INPUT_PULLUP);
  pinMode(BTN_4, INPUT_PULLUP);

  // --------------------------------------------------------------------------
  // [ES] Registro de Recursos de Salida (Control de actuadores / Switches)
  // [EN] Output Resource Registration (Actuator / Switch control)
  // --------------------------------------------------------------------------
  
  // LED 1
  thing["led_1"] << [](pson& in) {
    if (in.is_empty()) {
      in = state_led_1; // [ES] Reporta estado actual / [EN] Report current state
    } else {
      state_led_1 = in;
      digitalWrite(LED_1, state_led_1 ? HIGH : LOW);
    }
  };

  // LED 2
  thing["led_2"] << [](pson& in) {
    if (in.is_empty()) {
      in = state_led_2; // [ES] Reporta estado actual / [EN] Report current state
    } else {
      state_led_2 = in;
      digitalWrite(LED_2, state_led_2 ? HIGH : LOW);
    }
  };

  // LED 3
  thing["led_3"] << [](pson& in) {
    if (in.is_empty()) {
      in = state_led_3; // [ES] Reporta estado actual / [EN] Report current state
    } else {
      state_led_3 = in;
      digitalWrite(LED_3, state_led_3 ? HIGH : LOW);
    }
  };

  // LED 4
  thing["led_4"] << [](pson& in) {
    if (in.is_empty()) {
      in = state_led_4; // [ES] Reporta estado actual / [EN] Report current state
    } else {
      state_led_4 = in;
      digitalWrite(LED_4, state_led_4 ? HIGH : LOW);
    }
  };

  // --------------------------------------------------------------------------
  // [ES] Registro de Recursos de Entrada (Telemetria de sensores / Botones)
  //      Lectura invertida por configuracion active-low (INPUT_PULLUP)
  // [EN] Input Resource Registration (Sensor / Button telemetry)
  //      Inverted read due to active-low configuration (INPUT_PULLUP)
  // --------------------------------------------------------------------------
  thing["boton_1"] >> [](pson& out) { out = !digitalRead(BTN_1); };
  thing["boton_2"] >> [](pson& out) { out = !digitalRead(BTN_2); };
  thing["boton_3"] >> [](pson& out) { out = !digitalRead(BTN_3); };
  thing["boton_4"] >> [](pson& out) { out = !digitalRead(BTN_4); };
}

void loop() {
  // [ES] Mantiene la comunicacion activa con los servidores de Thinger.io
  // [EN] Keeps communication active with Thinger.io cloud servers
  thing.handle();
}
