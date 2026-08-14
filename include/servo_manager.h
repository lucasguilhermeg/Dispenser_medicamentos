#pragma once
#include <ESP32Servo.h>
#include "display_manager.h"
#include "piezo_manager.h"

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

    // Exibe no display que está dispensando
    displayDispensando(nomeMed, compartimento);

    // Abre o servo
    servoDispenser.write(ANGULO_ABERTO);
    delay(TEMPO_ABERTO_MS);
    servoDispenser.write(ANGULO_FECHADO);
    Serial.println("Compartimento fechado.");

    // Aguarda confirmação da queda da pílula
    bool pilulaDetectada = aguardarPilula();

    if (pilulaDetectada) {
        displayPilulaConfirmada(nomeMed);
        Serial.println("Pilula confirmada!");
    } else {
        displayPilulaNaoDetectada();
        Serial.println("ALERTA: Pilula nao detectada!");
    }

    delay(3000); // mantém mensagem no display por 3 segundos
}