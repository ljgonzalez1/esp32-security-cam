#include "esp_camera.h"
#include <Arduino.h>
#include <time.h>

#include "FS.h"       // SD Card ESP32
#include "SD_MMC.h"   // SD Card ESP32

#include "WiFiClient.h"
#include "clock.h"

#include "GlobalConstants.h"

WiFiClientManagerDHCP wifiManager;

void loop0();
void loop1();

[[noreturn]] void loop_thread_0(void *parameter) { for (;;) { loop0(); } };
[[noreturn]] void loop_thread_1(void *parameter) { for (;;) { loop1(); } };

void connect_wifi() {
  wifiManager.configureWiFi(WIFI_SSID, WIFI_PASSWD);

  // Intentar conectar a WiFi
  while (!wifiManager.isConnected()) {
    if (wifiManager.connect()) {
      Serial.println("WiFi connected.");

    } else {
      Serial.println("WiFi connection failed. Retrying...");
      delay(1000);
    }
  }

  // Mostrar detalles de la conexión WiFi
  wifiManager.showDetails();
}

void setup_cores() {
  // Crear tareas en los núcleos
  xTaskCreatePinnedToCore(loop_thread_0, "LoopThread0", 10000, nullptr, 1, nullptr, 0);
  xTaskCreatePinnedToCore(loop_thread_1, "LoopThread1", 10000, nullptr, 1, nullptr, 1);
}

bool write_datetime_to_file() {
  char filename[64];
  char datetime[64];

  // Obtener la fecha y hora actual
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return false;
  }

  // Formatear la fecha y hora en el nombre del archivo y el contenido
  strftime(filename, sizeof(filename), "/%Y-%m-%d_%H.%M.%S.txt", &timeinfo);
  strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", &timeinfo);

  // Abrir el archivo en la tarjeta SD para escritura
  File file = SD_MMC.open(filename, FILE_WRITE);
  if (!file) {
    Serial.printf("Failed to open file %s for writing\n", filename);
    return false;
  }

  // Escribir la fecha y hora en el archivo
  file.println(datetime);
  file.close();

  Serial.printf("Wrote to file: %s\n", filename);
  return true;
}

void setup() {
  Serial.begin(115200);

  connect_wifi();

  ClockManager::setupClock(TZ_AMERICA_SANTIAGO);
  ClockManager::syncClock();

  // ---

  // Inicializar la tarjeta SD
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("SD card initialization failed");
    return;
  }
  Serial.println("SD card initialized successfully");

  // Listar archivos en la tarjeta SD para verificar la inicialización
  File root = SD_MMC.open("/");
  if (!root) {
    Serial.println("Failed to open root directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Root is not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    Serial.print("FILE: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }

  // ---

  setup_cores();

  Serial.println("Setup completed.");
}

void loop() {
  delay(1000);
}

void loop0() {
  if (!wifiManager.isConnected()) {
    Serial.println("Conexión perdida. Reconectando...");
    wifiManager.connect();
  }

  delay(1000);
}

void loop1() {
  ClockManager::waitUntilNext10Seconds();

  if (write_datetime_to_file()) {
    Serial.println("Datetime written to file successfully.");
  } else {
    Serial.println("Failed to write datetime to file.");
  }

  delay(1000);
}

