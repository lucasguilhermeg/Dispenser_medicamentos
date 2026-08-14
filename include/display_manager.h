#pragma once
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void iniciarDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Display OLED não encontrado!");
        return;
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Dispenser pronto!");
    display.display();
    Serial.println("Display iniciado!");
}

void displayHorario(int hora, int minuto) {
    char horario[6];
    sprintf(horario, "%02d:%02d", hora, minuto);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(28, 10);
    display.println(horario);

    display.setTextSize(1);
    display.setCursor(0, 50);
    display.println("Dispenser ativo");
    display.display();
}

void displayDispensando(String nomeMed, int compartimento) {
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("Dispensando:");

    display.setCursor(0, 16);
    display.println(nomeMed);

    display.setCursor(0, 32);
    display.print("Compartimento: ");
    display.println(compartimento);

    display.setCursor(0, 50);
    display.println("Retire o medicamento");
    display.display();
}

void displayPilulaConfirmada(String nomeMed) {
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("Pilula detectada!");

    display.setCursor(0, 20);
    display.println(nomeMed);

    display.setCursor(0, 40);
    display.println("Tome o medicamento");
    display.display();
}

void displayPilulaNaoDetectada() {
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("ATENCAO!");

    display.setCursor(0, 20);
    display.println("Pilula nao");
    display.println("detectada!");

    display.setCursor(0, 50);
    display.println("Verifique o dispenser");
    display.display();
}