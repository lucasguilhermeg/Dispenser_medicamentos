#pragma once
#include <WiFi.h>

const char* WIFI_SSID     = "";
const char* WIFI_PASSWORD = "";

void conectarWiFi() {
    Serial.println("\nConectando ao Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}