#pragma once
#include <ESP32Servo.h>
#include "piezo_manager.h"
#include "display_manager.h"

const int SERVO_PIN       = 13;
const int ANGULO_FECHADO  = 0;
const int ANGULO_ABERTO   = 90;
const int TEMPO_ABERTO_MS = 3000;

Servo servoDispenser;

void iniciarServo() {
    servoDispenser.attach(SERVO_PIN);
    servoDispenser.write(ANGULO_FECHADO);
    Serial.println("Servo iniciado na posição fechada.");
}

void dispensar(int compartimento, String nomeMed = "Medicamento") {
    Serial.printf("Dispensando compartimento %d...\n", compartimento);

    displayDispensando(nomeMed, compartimento);

    servoDispenser.write(ANGULO_ABERTO);
    Serial.println("Servo aberto — aguardando queda da pilula...");

    unsigned long inicio = millis();
    bool pilulaDetectada = false;

    while (millis() - inicio < PIEZO_TIMEOUT_MS) {
        int leitura = analogRead(PIEZO_PIN);

        if (leitura > PIEZO_THRESHOLD) {
            pilulaDetectada = true;
            Serial.printf("Vibração detectada! Leitura: %d\n", leitura);
            break;
        }
        delay(10);
    }

    servoDispenser.write(ANGULO_FECHADO);
    Serial.println("Servo fechado.");

    if (pilulaDetectada) {
        displayPilulaConfirmada(nomeMed);
        Serial.println("Pilula confirmada!");
    } else {
        displayPilulaNaoDetectada();
        Serial.println("ALERTA: Pilula nao detectada!");
    }

    delay(3000);
}