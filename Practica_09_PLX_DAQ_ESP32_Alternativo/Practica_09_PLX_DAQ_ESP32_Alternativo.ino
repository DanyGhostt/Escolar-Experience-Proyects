// ==============================================================================
// Practica 09: Adquisicion de Datos PLX-DAQ ESP32 (Variante Alternativo)
// Practice 09: Real-Time DAQ with PLX-DAQ v2 and ESP32 (Alternativo Variant)
//
// Descripcion / Description:
// [ES] Adquisicion de 3 canales analogicos (Sensor 1 en GPIO 34, Infrarrojo en GPIO 35,
//      Sensor 2 en GPIO 15) para registro automatizado en Microsoft Excel via PLX-DAQ.
// [EN] 3-channel analog data acquisition (Sensor 1 on GPIO 34, IR on GPIO 35,
//      Sensor 2 on GPIO 15) for automated Excel spreadsheet logging via PLX-DAQ.
//
// ==============================================================================

// ------------------------------------------------------------------------------
// Parametros ADC / ADC Parameters
// ------------------------------------------------------------------------------
#define ADC_VREF_mV    3300.0 // [ES] Voltaje de referencia en mV / [EN] Reference voltage (mV)
#define ADC_RESOLUTION 4096.0 // [ES] Resolucion ADC 12-bit        / [EN] 12-bit ADC resolution

int contadorMuestras = 0; // [ES] Indice de muestra / [EN] Sample index counter

// ------------------------------------------------------------------------------
// Configuracion Inicial / System Setup
// ------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Comandos de inicializacion PLX-DAQ / PLX-DAQ Macro Commands
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Sensor1,Infrarojo,Sensor2,Muestra");
}

// ------------------------------------------------------------------------------
// Bucle Principal / Main Loop
// ------------------------------------------------------------------------------
void loop() {
  Serial.print("DATA,TIME,");
  delay(300);

  // [ES] Lectura de entradas analogicas / [EN] Read analog input pins
  Serial.print(analogRead(34)); // Sensor 1
  Serial.print(",");
  
  Serial.print(analogRead(35)); // Sensor Infrarrojo / IR Sensor
  Serial.print(",");
  
  Serial.print(analogRead(15)); // Sensor 2
  Serial.print(",");
  
  Serial.println(contadorMuestras++); // Contador y salto de linea / Sample counter

  delay(500);
}
