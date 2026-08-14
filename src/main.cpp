#include <Arduino.h>
#include "display_manager.h"
#include "wifi_manager.h"
#include "ntp_manager.h"
#include "servo_manager.h"
#include "mqtt_manager.h"
#include "scheduler.h"

void setup() {
    Serial.begin(115200);

    iniciarDisplay();
    conectarWiFi();
    sincronizarNTP();
    iniciarServo();
    conectarMQTT();

    Serial.println("\n=== Dispenser pronto ===");
}

void loop() {
    mqttLoop();
    verificarAlarmes();

    // Atualiza horário no display a cada segundo
    int hora, minuto;
    getHoraAtual(hora, minuto);
    displayHorario(hora, minuto);

    delay(1000);
}