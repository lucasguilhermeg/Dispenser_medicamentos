#pragma once
#include <WiFi.h>

const char* WIFI_SSID     = "DESKTOP-B7QME48 2032";
const char* WIFI_PASSWORD = "|x01938U";

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