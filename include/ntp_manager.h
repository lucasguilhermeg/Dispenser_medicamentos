#pragma once 
#include <Arduino.h>
#include "time.h"

const char* NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET = -3 * 3600; // Offset para o fuso horário de Brasília (UTC-3)
const int DST_OFFSET = 0;

void sincronizarNTP()