#pragma once
#include <Arduino.h>

const int PIEZO_PIN         = 34;  // GPIO34 — pino de leitura analógica
const int PIEZO_THRESHOLD   = 500; // limiar de detecção de vibração
const int PIEZO_TIMEOUT_MS  = 5000; // tempo máximo aguardando a pílula cair

// Aguarda detecção de vibração por até PIEZO_TIMEOUT_MS milissegundos
// Retorna true se a pílula foi detectada, false se timeout
bool aguardarPilula() {
    Serial.println("Aguardando queda da pilula...");
    unsigned long inicio = millis();

    while (millis() - inicio < PIEZO_TIMEOUT_MS) {
        int leitura = analogRead(PIEZO_PIN);

        if (leitura > PIEZO_THRESHOLD) {
            Serial.printf("Vibração detectada! Leitura: %d\n", leitura);
            return true;
        }
        delay(10);
    }

    Serial.println("Timeout — pilula nao detectada.");
    return false;
}