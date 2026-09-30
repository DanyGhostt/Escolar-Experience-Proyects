// ==============================================================================
// Practica 12: Servidor Web en ESP32 para Control de LEDs por WiFi
// Practice 12: ESP32 HTTP Web Server for Wireless LED Control
//
// Descripcion / Description:
// [ES] Servidor web HTTP local alojado en el ESP32 (puerto 80) que entrega una pagina
//      web interactiva HTML/CSS para encender y apagar 4 LEDs fisicos de forma remota.
// [EN] Local HTTP web server hosted on the ESP32 (port 80) serving a responsive
//      HTML/CSS dashboard to wirelessly turn on and off 4 physical LEDs.
//
// ==============================================================================

#include <WiFi.h>

// ------------------------------------------------------------------------------
// Credenciales de Red WiFi / WiFi Credentials
// ------------------------------------------------------------------------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Nombre de red del dispositivo / Device network name
String nom = "ESP32-WebServer";

// Inicializacion del servidor en puerto 80 / Web server on port 80
WiFiServer server(80);

// Variables de estado de los LEDs / LED State Variables
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";

// Control de tiempo y timeout / Timeout & timing variables
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

// ------------------------------------------------------------------------------
// Configuracion Inicial / System Setup
// ------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Definicion de pines de salida / Output Pin Configuration
  pinMode(13, OUTPUT); // [ES] LED Rojo       / [EN] Red LED (GPIO 13)
  pinMode(12, OUTPUT); // [ES] LED Verde      / [EN] Green LED (GPIO 12)
  pinMode(14, OUTPUT); // [ES] LED Amarillo   / [EN] Yellow LED (GPIO 14)
  pinMode(27, OUTPUT); // [ES] LED Azul       / [EN] Blue LED (GPIO 27)
  pinMode(26, OUTPUT); // [ES] LED Monitoreo  / [EN] Connection Activity LED (GPIO 26)

  delay(10);

  // Conexion a la red WiFi / WiFi Connection Routine
  Serial.println();
  Serial.println("CONECTANDO A / CONNECTING TO: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi CONECTADO / CONNECTED.");
  Serial.println("DIRECCION IP LOCAL / LOCAL IP: ");
  Serial.println(WiFi.localIP());

  // Iniciar servidor web / Start HTTP Server
  server.begin();
}

// ------------------------------------------------------------------------------
// Bucle Principal / Main Loop (Manejo de Clientes HTTP)
// ------------------------------------------------------------------------------
void loop() {
  WiFiClient client = server.available(); // Escuchar clientes entrantes / Listen for clients
  
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("NUEVO CLIENTE / NEW CLIENT CONNECTED");
    digitalWrite(26, HIGH); // LED de actividad / Activity LED ON

    String header = "";
    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();

      if (client.available()) {
        char c = client.read();
        Serial.write(c); 
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // [ES] Encabezado de respuesta HTTP / [EN] HTTP Response Header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // [ES] Decodificacion de solicitudes GET para conmutacion de LEDs
            // [EN] Decode GET requests to toggle physical LED outputs
            if (header.indexOf("GET /1/on") >= 0) {
              output1State = "on";
              digitalWrite(13, HIGH);  
            } else if (header.indexOf("GET /1/off") >= 0) {
              output1State = "off";
              digitalWrite(13, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              output2State = "on";
              digitalWrite(12, HIGH);  
            } else if (header.indexOf("GET /2/off") >= 0) {
              output2State = "off";
              digitalWrite(12, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              output3State = "on";
              digitalWrite(14, HIGH);  
            } else if (header.indexOf("GET /3/off") >= 0) {
              output3State = "off";
              digitalWrite(14, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              output4State = "on";
              digitalWrite(27, HIGH);  
            } else if (header.indexOf("GET /4/off") >= 0) {
              output4State = "off";
              digitalWrite(27, LOW);
            }

            // [ES] Generacion de interfaz web HTML/CSS
            // [EN] HTML/CSS Web Dashboard Generation
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"es\">");
            client.println("<head>");
            client.println("    <meta charset=\"UTF-8\">");
            client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("    <title>ESP32 Control de LEDs / LED Control</title>");
            client.println("    <style>");
            client.println("        body {");
            client.println("            margin: 0;");
            client.println("            padding: 0;");
            client.println("            height: 100vh;");
            client.println("            background: url('https://viveloensaltillo.com/wp-content/uploads/2018/08/1254x851tecsaltillo1-768x521.jpg') no-repeat center center;");
            client.println("            background-size: cover;");
            client.println("            color: white;");
            client.println("            font-family: Arial, sans-serif;");
            client.println("        }");
            client.println("        .top-left {");
            client.println("            position: absolute;");
            client.println("            top: 10px;");
            client.println("            left: 15px;");
            client.println("            color: maroon;");
            client.println("            font-size: 24px;");
            client.println("            font-weight: bold;");
            client.println("        }");
            client.println("        .department {");
            client.println("            position: absolute;");
            client.println("            top: 12%;");
            client.println("            left: 50%;");
            client.println("            transform: translate(-50%, -50%);");
            client.println("            color: white;");
            client.println("            font-size: 24px;");
            client.println("            font-weight: bold;");
            client.println("            text-transform: uppercase;");
            client.println("        }");
            client.println("        .center-top {");
            client.println("            position: absolute;");
            client.println("            top: 18%;");
            client.println("            left: 50%;");
            client.println("            transform: translate(-50%, -50%);");
            client.println("            color: white;");
            client.println("            font-size: 28px;");
            client.println("            font-weight: bold;");
            client.println("        }");
            client.println("        .below-center-top {");
            client.println("            position: absolute;");
            client.println("            top: 22%;");
            client.println("            left: 50%;");
            client.println("            transform: translate(-50%, -50%);");
            client.println("            color: green;");
            client.println("            font-size: 20px;");
            client.println("            font-weight: bold;");
            client.println("        }");
            client.println("        .bottom-right {");
            client.println("            position: absolute;");
            client.println("            bottom: 10px;");
            client.println("            right: 15px;");
            client.println("            text-align: right;");
            client.println("            color: white;");
            client.println("            font-size: 16px;");
            client.println("        }");
            client.println("        .top-right {");
            client.println("            position: absolute;");
            client.println("            top: 10px;");
            client.println("            right: 15px;");
            client.println("            color: blue;");
            client.println("            font-size: 18px;");
            client.println("            font-weight: bold;");
            client.println("            text-align: right;");
            client.println("        }");
            client.println("        .led-status {");
            client.println("            position: absolute;");
            client.println("            top: 25%;");
            client.println("            left: 50%;");
            client.println("            transform: translate(-50%, -50%);");
            client.println("            color: white;");
            client.println("            font-size: 20px;");
            client.println("            font-weight: bold;");
            client.println("        }");
            client.println("        .led-buttons {");
            client.println("            position: absolute;");
            client.println("            top: 50%;");
            client.println("            left: 50%;");
            client.println("            transform: translate(-50%, -50%);");
            client.println("            width: 100%;");
            client.println("            display: flex;");
            client.println("            flex-direction: column;");
            client.println("            align-items: center;");
            client.println("        }");
            client.println("        .led-button {");
            client.println("            padding: 10px 20px;");
            client.println("            font-size: 16px;");
            client.println("            background-color: #9E1B32;");
            client.println("            color: white;");
            client.println("            border: none;");
            client.println("            cursor: pointer;");
            client.println("            border-radius: 5px;");
            client.println("            transition: background-color 0.3s;");
            client.println("            margin: 5px;");
            client.println("        }");
            client.println("        .led-button:hover {");
            client.println("            background-color: darkgray;");
            client.println("        }");
            client.println("        .button-row {");
            client.println("            display: flex;");
            client.println("            justify-content: center;");
            client.println("            margin-bottom: 10px;");
            client.println("        }");
            client.println("    </style>");
            client.println("</head>");
            client.println("<body>");
            client.println("    <div class=\"top-left\">Instituto Tecnologico de Saltillo</div>");
            client.println("    <div class=\"department\">Departamento de Electrónica</div>");
            client.println("    <div class=\"center-top\">Microcontroladores</div>");
            client.println("    <div class=\"below-center-top\">Nombre del Maestro: Ing. Huitzilihuitl Saldaña Mora</div>");
            client.println("    <div class=\"bottom-right\">Microcontroladores - ESP32</div>");
            client.println("    <div class=\"top-right\">Practica 12: ESP32 Servidor Web</div>");
            client.println("    <div class=\"led-status\">LED 1: " + output1State + " | LED 2: " + output2State + " | LED 3: " + output3State + " | LED 4: " + output4State + "</div>");

            client.println("    <div class=\"led-buttons\">");
            
            // Botones LED 1 (Rojo)
            client.println("        <div class=\"button-row\">");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/1/on'\">Encender LED 1 (On)</button>");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/1/off'\">Apagar LED 1 (Off)</button>");
            client.println("        </div>");
            
            // Botones LED 2 (Verde)
            client.println("        <div class=\"button-row\">");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/2/on'\">Encender LED 2 (On)</button>");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/2/off'\">Apagar LED 2 (Off)</button>");
            client.println("        </div>");

            // Botones LED 3 (Amarillo)
            client.println("        <div class=\"button-row\">");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/3/on'\">Encender LED 3 (On)</button>");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/3/off'\">Apagar LED 3 (Off)</button>");
            client.println("        </div>");

            // Botones LED 4 (Azul)
            client.println("        <div class=\"button-row\">");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/4/on'\">Encender LED 4 (On)</button>");
            client.println("            <button class=\"led-button\" onclick=\"location.href='/4/off'\">Apagar LED 4 (Off)</button>");
            client.println("        </div>");

            client.println("    </div>");
            client.println("</body>");
            client.println("</html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    digitalWrite(26, LOW); // Apagar LED indicador / Activity LED OFF
    Serial.println("Cliente desconectado / Client disconnected");
  }
}
