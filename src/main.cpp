#include <Arduino.h>
#include "wifi_manager.h"
#include "ntp_manager.h"
#include "mqtt_manager.h"
#include "servo_manager.h"
#include "scheduler.h"

void setup() {
    Serial.begin(115200);

    conectarWiFi();
    sincronizarNTP();
    iniciarServo();
    conectarMQTT();

    Serial.println("\n=== Dispenser pronto ===");
}

void loop() {
    mqttLoop();
    verificarAlarmes();
    delay(1000);
}