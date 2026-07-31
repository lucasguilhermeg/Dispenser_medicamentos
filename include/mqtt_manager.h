#pragma once
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "rotina.h"
#include "servo_manager.h"

const char* MQTT_BROKER         = "broker.hivemq.com";
const int   MQTT_PORT           = 1883;
const char* MQTT_TOPICO_ROTINA  = "dispenser/rotina";
const char* MQTT_TOPICO_COMANDO = "dispenser/comando";

WiFiClient   espClient;
PubSubClient mqttClient(espClient);

void parsearRotina(const String& payload) {
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, payload);

    if (erro) {
        Serial.print("Erro ao parsear JSON: ");
        Serial.println(erro.c_str());
        return;
    }

    JsonArray meds = doc["medicamentos"];
    rotinaAtual.totalMedicamentos = 0;

    for (JsonObject med : meds) {
        int i = rotinaAtual.totalMedicamentos;

        rotinaAtual.medicamentos[i].nome          = med["nome"].as<String>();
        rotinaAtual.medicamentos[i].compartimento = med["compartimento"];
        rotinaAtual.medicamentos[i].totalHorarios = 0;

        for (const char* h : med["horarios"].as<JsonArray>()) {
            int j = rotinaAtual.medicamentos[i].totalHorarios;
            sscanf(h, "%d:%d",
                &rotinaAtual.medicamentos[i].horarios[j].hora,
                &rotinaAtual.medicamentos[i].horarios[j].minuto);
            rotinaAtual.medicamentos[i].totalHorarios++;
        }

        rotinaAtual.totalMedicamentos++;
        Serial.printf("Medicamento carregado: %s\n",
            rotinaAtual.medicamentos[i].nome.c_str());
    }
}

void processarComando(const String& payload) {
    JsonDocument doc;
    DeserializationError erro = deserializeJson(doc, payload);

    if (erro) {
        Serial.print("Erro ao parsear comando: ");
        Serial.println(erro.c_str());
        return;
    }

    const char* acao = doc["acao"];
    int compartimento = doc["compartimento"] | 1;

    if (strcmp(acao, "dispensar") == 0) {
        Serial.printf("Comando manual: dispensar compartimento %d\n", compartimento);
        dispensar(compartimento);
    } else {
        Serial.printf("Comando desconhecido: %s\n", acao);
    }
}

void mqttCallback(char* topico, byte* payload, unsigned int tamanho) {
    String mensagem;
    for (unsigned int i = 0; i < tamanho; i++) {
        mensagem += (char)payload[i];
    }

    Serial.printf("Mensagem recebida no tópico: %s\n", topico);

    if (String(topico) == MQTT_TOPICO_ROTINA) {
        parsearRotina(mensagem);
    } else if (String(topico) == MQTT_TOPICO_COMANDO) {
        processarComando(mensagem);
    }
}

void conectarMQTT() {
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    mqttClient.setCallback(mqttCallback);

    while (!mqttClient.connected()) {
        Serial.print("Conectando ao broker MQTT...");
        String clientId = "ESP32-" + String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str())) {
            Serial.println(" conectado!");
            mqttClient.subscribe(MQTT_TOPICO_ROTINA);
            mqttClient.subscribe(MQTT_TOPICO_COMANDO);
        } else {
            Serial.printf(" falhou (rc=%d), tentando em 3s\n",
                mqttClient.state());
            delay(3000);
        }
    }
}

void mqttLoop() {
    if (!mqttClient.connected()) conectarMQTT();
    mqttClient.loop();
}