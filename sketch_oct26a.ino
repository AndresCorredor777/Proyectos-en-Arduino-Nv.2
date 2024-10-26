#define BLYNK_TEMPLATE_ID "TuTemplateID"// Coloca aquí tu Template ID
#define BLYNK_TEMPLATE_NAME "TuTemplateName"// Coloca aquí tu Template Name

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Credenciales de Blynk
char auth[] = "TuAuthToken";// Token de autenticación de Blynk
char ssid[] = "TuSSID"; // Nombre de la red WiFi
char pass[] = "TuPassword";// Contraseña de la red WiFi

#define pirPin 5 // GPIO 5 (D1 en NodeMCU) para el sensor PIR
#define sirenaPin 4 // GPIO 4 (D2 en NodeMCU) para la sirena

void setup() {
  // Configuración de la conexión serial y Blynk
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);// Conectar a Blynk

  // Configuración de pines
  pinMode(pirPin, INPUT); // Configura el pin del PIR como entrada
  pinMode(sirenaPin, OUTPUT);// Configura el pin de la sirena como salida
  digitalWrite(sirenaPin, LOW); // Asegúrate de que la sirena esté apagada al inicio

  Serial.println("Sistema de alarma listo.");
}

void loop() {
  Blynk.run(); // Mantiene la conexión con Blynk

  // Leer el estado del sensor PIR
  int pirValue = digitalRead(pirPin);

  if (pirValue == HIGH) { // Si detecta movimiento
    Serial.println("¡Movimiento detectado!");

    // Activar la sirena
    digitalWrite(sirenaPin, HIGH);

    // Mantener la sirena encendida por 5 segundos
    delay(5000);

    // Apagar la sirena
    digitalWrite(sirenaPin, LOW);
  }
}
