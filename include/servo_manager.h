#pragma once
#include <Arduino.h>
#include "time.h"

const char* NTP_SERVER = "pool.ntp.org";
const long  GMT_OFFSET = -3 * 3600;
const int   DST_OFFSET = 0;

void sincronizarNTP() {
    configTime(GMT_OFFSET, DST_OFFSET, NTP_SERVER);
    Serial.print("Sincronizando horário NTP");

    struct tm timeInfo;
    while (!getLocalTime(&timeInfo)) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nHorário sincronizado!");
    Serial.printf("Hora atual: %02d:%02d:%02d\n",
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec);
}

void getHoraAtual(int &hora, int &minuto) {
    struct tm timeInfo;
    getLocalTime(&timeInfo);
    hora   = timeInfo.tm_hour;
    minuto = timeInfo.tm_min;
}