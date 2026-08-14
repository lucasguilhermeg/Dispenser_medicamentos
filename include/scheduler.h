#pragma once
#include "rotina.h"
#include "ntp_manager.h"
#include "servo_manager.h"

bool disparadoNesteMinuto   = false;
int  ultimoMinutoVerificado = -1;

void verificarAlarmes() {
    int horaAtual, minutoAtual;
    getHoraAtual(horaAtual, minutoAtual);

    if (minutoAtual != ultimoMinutoVerificado) {
        disparadoNesteMinuto   = false;
        ultimoMinutoVerificado = minutoAtual;
    }

    if (disparadoNesteMinuto) return;

    for (int i = 0; i < rotinaAtual.totalMedicamentos; i++) {
        Medicamento& med = rotinaAtual.medicamentos[i];
        for (int j = 0; j < med.totalHorarios; j++) {
            if (med.horarios[j].hora   == horaAtual &&
                med.horarios[j].minuto == minutoAtual) {

                Serial.printf("ALARME: %s às %02d:%02d\n",
                    med.nome.c_str(), horaAtual, minutoAtual);

                dispensar(med.compartimento);
                disparadoNesteMinuto = true;
            }
        }
    }
}