#pragma once
#include <WiFi.h>

const char* WIFI_SSID = "SEU_WIFI"
const char* WIFI_PASSWORD = "SUA_SENHA"

void conectarWiFi() {
    Serial.println("Conectando-se à rede Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Tentando conectar...");
    }

    Serial.println("Conectado à rede Wi-Fi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}