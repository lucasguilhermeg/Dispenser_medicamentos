#pragma once
#include <ESP32Servo.h>

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

void dispensar(int compartimento) {
    Serial.printf("Dispensando compartimento %d...\n", compartimento);
    servoDispenser.write(ANGULO_ABERTO);
    delay(TEMPO_ABERTO_MS);
    servoDispenser.write(ANGULO_FECHADO);
    Serial.println("Compartimento fechado.");
}