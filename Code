#include <Wire.h>
#include <RTClib.h> // Librería para el RTC DS3231
#include <LiquidCrystal_I2C.h> // Para la pantalla LCD (opcional)
#include <SoftwareSerial.h> // Para el Bluetooth HC-05

#define SOIL_PIN A0         // Pin del sensor de humedad del suelo
#define RELAY_PIN 8         // Pin para controlar el relé de la bomba
#define BUTTON_PIN 9        // Pin del botón para control manual
#define THRESHOLD 400       // Umbral de humedad para activar la bomba (ajustar según sea necesario)

// Inicializa el RTC y LCD (si lo estás usando)
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C de la pantalla LCD

// Inicializa el Bluetooth en pines 10 y 11 (cambiar si es necesario)
SoftwareSerial BT(10, 11); 

void setup() {
  Serial.begin(9600);
  BT.begin(9600);          // Configura el Bluetooth a 9600 baudios
  pinMode(SOIL_PIN, INPUT); // Configura el pin del sensor de humedad
  pinMode(RELAY_PIN, OUTPUT); // Configura el pin del relé
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura el botón con pull-up interno
 
 // Asegurar que la bomba esté apagada al inicio
  digitalWrite(RELAY_PIN, LOW); // Apaga el relé (bomba) al inicio

  // Inicializa la pantalla LCD (opcional)
  lcd.init();
  lcd.backlight();
  
  // Inicializa el RTC
  if (!rtc.begin()) {
    Serial.println("Error RTC");
    while (1);
  }

  // Verifica si el RTC perdió la configuración
  if (rtc.lostPower()) {
    Serial.println("RTC perdió la configuración, reajustando...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajusta la fecha/hora al tiempo de compilación
  }

  lcd.print("Sistema de Riego");  // Mostrar mensaje de inicio en la pantalla LCD
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer la humedad del suelo
  int soilMoisture = analogRead(SOIL_PIN);

  // Leer la hora actual del RTC
  DateTime now = rtc.now();

  // Mostrar hora en la LCD (opcional)
  lcd.setCursor(0, 0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  
  // Mostrar el estado de la humedad
  lcd.setCursor(0, 1);
  lcd.print("H: ");  //humedad
  lcd.print(soilMoisture);

  // Control de la bomba de agua según el nivel de humedad
  if (soilMoisture < THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH); // Activa la bomba
    lcd.setCursor(10, 1);
    lcd.print("RiegoE");
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Apaga la bomba
    lcd.setCursor(10, 1);
    lcd.print("RiegoA");
  }
  
  // Mostrar en el terminal serial
  Serial.print("Hora: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(" Humedad: ");
  Serial.print(soilMoisture);
  
  if (digitalRead(RELAY_PIN) == HIGH) {
    Serial.println(" -RiegoE");//encendido
  } else {
    Serial.println(" -RiegoA");//apagado
  }
  
  // Enviar datos al Bluetooth
  BT.print("Hora: ");
  BT.print(now.hour());
  BT.print(":");
  BT.print(now.minute());
  BT.print(" Humedad: ");
  BT.print(soilMoisture);
  
  if (digitalRead(RELAY_PIN) == HIGH) {
    BT.println(" -RiegoE");//encendido
  } else {
    BT.println(" -RiegoA");//apagado
  }
  
  // Control manual de la bomba mediante el botón
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(RELAY_PIN, HIGH); // Activa la bomba
    lcd.setCursor(10, 1);
    lcd.print("RiegoM");//ON (Manual)
    delay(5000);  // Mantiene la bomba encendida durante 5 segundos
    digitalWrite(RELAY_PIN, LOW);
  }

  // Control manual de la bomba mediante Bluetooth
  if (BT.available()) {
    char comando = BT.read();
    if (comando == '1') {
      digitalWrite(RELAY_PIN, HIGH); // Activa la bomba vía Bluetooth
      lcd.setCursor(10, 1);
      lcd.print("Riego ON (BT)");
    } else if (comando == '0') {
      digitalWrite(RELAY_PIN, LOW);  // Apaga la bomba vía Bluetooth
      lcd.setCursor(10, 1);
      lcd.print("Riego OFF (BT)");
    }
  }

  delay(1000); // Espera 1 segundo entre ciclos
}
