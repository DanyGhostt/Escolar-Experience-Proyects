// ==============================================================================
// Practica 09: Adquisicion de Datos en Tiempo Real con PLX-DAQ y Excel
// Practice 09: Real-Time Data Acquisition (DAQ) with PLX-DAQ v2 and Excel
//
// Descripcion / Description:
// [ES] Adquisicion de sensores analogicos (LDR / fotorresistencia en GPIO 34,
//      sensor infrarrojo en GPIO 35 y sensor de humedad en GPIO 15) y transmision
//      continua formateada para registro y graficacion automatica en Microsoft Excel.
// [EN] Analog sensor data acquisition (LDR light sensor on GPIO 34, IR sensor on
//      GPIO 35, and soil/water humidity sensor on GPIO 15) streamed with PLX-DAQ v2
//      formatting for live logging and plotting in Microsoft Excel.


// ------------------------------------------------------------------------------
// Parametros de Conversion Analogico-Digital / ADC Reference Parameters
// ------------------------------------------------------------------------------
#define ADC_VREF_mV    3300.0 // [ES] Voltaje de referencia en mV / [EN] Reference voltage in mV
#define ADC_RESOLUTION 4096.0 // [ES] Resolucion ADC ESP32 (12-bit) / [EN] ESP32 12-bit ADC resolution

int contadorMuestras = 0; // [ES] Contador incremental / [EN] Sample index counter

// ------------------------------------------------------------------------------
// Configuracion Inicial / System Setup
// ------------------------------------------------------------------------------
void setup() {
  // Iniciar comunicacion serial a 9600 baudios / Start serial communication at 9600 baud
  Serial.begin(9600);

  // Comandos de configuracion de PLX-DAQ / PLX-DAQ Macro Commands
  Serial.println("CLEARDATA"); // [ES] Limpiar hoja de calculo previa / [EN] Clear old spreadsheet data
  Serial.println("LABEL,Time,fotorresistencia,Infrarojo,humedad,Muestra"); // [ES] Encabezados / [EN] Column labels
}

// ------------------------------------------------------------------------------
// Bucle Principal / Main Loop (Muestreo y Transmision de Datos)
// ------------------------------------------------------------------------------
void loop() {
  // [ES] Enviar comando de registro temporal a PLX-DAQ
  // [EN] Send timestamp command to PLX-DAQ
  Serial.print("DATA,TIME,");
  delay(300);

  // [ES] Lecturas de los sensores analogicos
  // [EN] Analog sensor readings
  Serial.print(analogRead(34)); // Canal 1: Fotorresistencia (LDR) / Ch 1: Photoresistor
  Serial.print(",");
  
  Serial.print(analogRead(35)); // Canal 2: Infrarrojo (IR)        / Ch 2: Infrared sensor
  Serial.print(",");
  
  Serial.print(analogRead(15)); // Canal 3: Humedad               / Ch 3: Humidity sensor
  Serial.print(",");
  
  Serial.println(contadorMuestras++); // Contador de muestra y salto de linea / Sample count

  delay(500); // Periodo de muestreo / Sampling interval (500 ms)
}
