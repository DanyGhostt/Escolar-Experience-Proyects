// ==============================================================================
// Practica 11: Reloj Despertador NTP con WiFi y Alarma (Version 2 / Borrador)
// Practice 11: NTP Internet Alarm Clock with WiFi & Buzzer (Version 2 / Draft)
//
// Descripcion / Description:
// [ES] Implementacion compacta de reloj digital con sincronizacion horaria por Internet
//      via protocolo NTP, ajuste de alarma con 4 botones mediante interrupciones y buzzer.
// [EN] Compact implementation of Internet-synchronized digital clock via NTP over WiFi,
//      alarm time adjustment with 4 interrupt-driven buttons, and piezo buzzer alarm.
//
// ==============================================================================

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "time.h"

// ------------------------------------------------------------------------------
// Configuracion de Pantalla OLED / OLED Display Configuration
// ------------------------------------------------------------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ------------------------------------------------------------------------------
// Parametros de Red WiFi y Servidor NTP / WiFi & NTP Parameters
// ------------------------------------------------------------------------------
const char* ssid = "YOUR_WIFI_SSID";          // [ES] Nombre de red WiFi   / [EN] WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD";       // [ES] Contrasena WiFi      / [EN] WiFi Password
const char* ntpServer = "time.google.com"; // [ES] Servidor NTP         / [EN] NTP Time Server
const long gmtOffset_sec = -21600;         // [ES] Zona horaria GMT-6   / [EN] Timezone offset (GMT-6)
const int daylightOffset_sec = 0;          // [ES] Sin horario de verano/ [EN] Daylight savings offset

// ------------------------------------------------------------------------------
// Definicion de Pines / Pin Definitions
// ------------------------------------------------------------------------------
#define BUTTON_HOUR_UP 33     // [ES] +Horas   / [EN] Hours + (GPIO 33)
#define BUTTON_HOUR_DOWN 36   // [ES] -Horas   / [EN] Hours - (GPIO 36)
#define BUTTON_MINUTE_UP 34   // [ES] +Minutos / [EN] Minutes + (GPIO 34)
#define BUTTON_MINUTE_DOWN 35 // [ES] -Minutos / [EN] Minutes - (GPIO 35)
#define BUZZER_PIN 13         // [ES] Buzzer   / [EN] Buzzer Pin (GPIO 13)

// ------------------------------------------------------------------------------
// Frecuencias de Notas Musicales (Hz) / Note Frequencies (Hz)
// ------------------------------------------------------------------------------
#define Fa   1431
#define Sol  1275
#define La   1136
#define LaS  1072

// Melodia de la alarma / Alarm melody
int melody[] = {La, LaS, La, La, Fa, Sol, La, LaS};
int durations[] = {500, 500, 500, 500, 500, 500, 500, 500};

// Variables para la hora y la alarma / Time & Alarm variables
volatile int alarmHour = 0;
volatile int alarmMinute = 0;
char timeHour[3], timeMinute[3], timeSecond[3];

// Debouncing de botones / Button debounce variables
unsigned long lastPressHourUp = 0, lastPressHourDown = 0;
unsigned long lastPressMinuteUp = 0, lastPressMinuteDown = 0;
const unsigned long debounceDelay = 200; // 200 ms debounce filter

// ------------------------------------------------------------------------------
// Rutinas de Interrupcion (ISR) / Alarm Adjustment ISRs
// ------------------------------------------------------------------------------
void IRAM_ATTR handleHourUp() {
    if (millis() - lastPressHourUp > debounceDelay) {
        alarmHour = (alarmHour + 1) % 24;
        lastPressHourUp = millis();
    }
}

void IRAM_ATTR handleHourDown() {
    if (millis() - lastPressHourDown > debounceDelay) {
        alarmHour = (alarmHour - 1 + 24) % 24;
        lastPressHourDown = millis();
    }
}

void IRAM_ATTR handleMinuteUp() {
    if (millis() - lastPressMinuteUp > debounceDelay) {
        alarmMinute = (alarmMinute + 1) % 60;
        lastPressMinuteUp = millis();
    }
}

void IRAM_ATTR handleMinuteDown() {
    if (millis() - lastPressMinuteDown > debounceDelay) {
        alarmMinute = (alarmMinute - 1 + 60) % 60;
        lastPressMinuteDown = millis();
    }
}

// ------------------------------------------------------------------------------
// Configuracion Inicial / System Setup
// ------------------------------------------------------------------------------
void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print("Conectando WiFi / Connecting...");
    display.display();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    pinMode(BUTTON_HOUR_UP, INPUT_PULLUP);
    pinMode(BUTTON_HOUR_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_MINUTE_UP, INPUT_PULLUP);
    pinMode(BUTTON_MINUTE_DOWN, INPUT_PULLUP);
    attachInterrupt(BUTTON_HOUR_UP, handleHourUp, FALLING);
    attachInterrupt(BUTTON_HOUR_DOWN, handleHourDown, FALLING);
    attachInterrupt(BUTTON_MINUTE_UP, handleMinuteUp, FALLING);
    attachInterrupt(BUTTON_MINUTE_DOWN, handleMinuteDown, FALLING);

    pinMode(BUZZER_PIN, OUTPUT);
}

// ------------------------------------------------------------------------------
// Bucle Principal / Main Loop
// ------------------------------------------------------------------------------
void loop() {
    display.clearDisplay();
    printLocalTime();
    displayAlarmTime();
    verificarAlarma();
}

// ------------------------------------------------------------------------------
// Visualizacion de Hora NTP / NTP Time Display
// ------------------------------------------------------------------------------
void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        display.setCursor(0, 0);
        display.print("Error hora / Time error");
        display.display();
        return;
    }

    strftime(timeHour, 3, "%H", &timeinfo);
    strftime(timeMinute, 3, "%M", &timeinfo);
    strftime(timeSecond, 3, "%S", &timeinfo);

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(timeHour);
    display.print(":");
    display.print(timeMinute);
    display.print(":");
    display.print(timeSecond);
    display.display();
}

// ------------------------------------------------------------------------------
// Visualizacion de Alarma / Alarm Display
// ------------------------------------------------------------------------------
void displayAlarmTime() {
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("Alarma / Alarm: ");
    if (alarmHour < 10) display.print('0');
    display.print(alarmHour);
    display.print(":");
    if (alarmMinute < 10) display.print('0');
    display.print(alarmMinute);
    display.display();
}

// ------------------------------------------------------------------------------
// Verificacion y Disparo de Alarma / Alarm Check & Play
// ------------------------------------------------------------------------------
void verificarAlarma() {
    int horaActual = atoi(timeHour);
    int minutoActual = atoi(timeMinute);

    if (horaActual == alarmHour && minutoActual == alarmMinute) {
        sonarAlarma();
    }
}

void sonarAlarma() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.print("ALARMA!");
    display.display();

    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        tone(BUZZER_PIN, melody[i], durations[i]);
        delay(durations[i] * 1.3);
        noTone(BUZZER_PIN);
    }
}
