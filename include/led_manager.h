#pragma once
#include <Arduino.h>

const int LED_PIN = 2;

void iniciarLed() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED iniciado.");
}

void piscarLed() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
        delay(300);
    }
    Serial.println("LED acionado!");
}