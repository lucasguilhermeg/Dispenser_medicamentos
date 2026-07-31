#pragma once
#include <Arduino.h>

#define MAX_HORARIOS     5
#define MAX_MEDICAMENTOS 4

struct Horario {
    int hora;
    int minuto;
};

struct Medicamento {
    String nome;
    int compartimento;
    Horario horarios[MAX_HORARIOS];
    int totalHorarios;
};

struct Rotina {
    Medicamento medicamentos[MAX_MEDICAMENTOS];
    int totalMedicamentos;
};

Rotina rotinaAtual;