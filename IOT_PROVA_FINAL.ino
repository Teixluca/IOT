#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#include "dht.h"
#include <SPI.h>
#include <MFRC522.h>

#define OLED_RESET -1
#define SS_PIN 53
#define RST_PIN 9

Adafruit_SH1106 display(OLED_RESET);
const int sensorT = A0;
float temperatura;
dht DHT;
int const_temp = 0; // 0 = Celsius, 1 = Kelvin
int const_font = 0;
int LDR = 0;
int buzzer = 6;
int TOUCH = 9;
int botao1 = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN);
int acesso = 0;

void setup() {
    Serial.begin(9600);
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    pinMode(A1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
}

void loop() {
    // Verifica se o acesso está autorizado
    if (acesso == 0) {
        // Loop para autenticação via RFID
        Serial.println("Status do acesso: ");
        Serial.println(acesso);
        Serial.println("Status do Botão 1: ");
        Serial.println(digitalRead(2));
        Serial.println("Status do Botão 2: ");
        Serial.println(digitalRead(3));
        Serial.println("Status do Botão 3: ");
        Serial.println(digitalRead(4));
        Serial.println("Status do Botão 4: ");
        Serial.println(digitalRead(5));

        // Temperatura
        DHT.read11(sensorT);
        // Luminância
        LDR = analogRead(A1);

        if (LDR < 10) {
            display.clearDisplay();
            tone(buzzer, 300, 1000);
            delay(300);
            display.display();
        }

        // Configuração do Display
        display.clearDisplay();
        //display.print(const_font == 0 ? DHT.temperature : DHT.temperature + 273.15,0);
        display.setFont(const_font == 0 ? &FreeMonoOblique9pt7b : &FreeSansBoldOblique9pt7b);
        //display.setFont(&FreeMonoOblique9pt7b);
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.drawRect(0, 0, 128, 64, WHITE);
        display.setCursor(10, 13);
        display.print(const_temp == 0 ? DHT.temperature : DHT.temperature + 273.15,0);
        display.print(const_temp == 0 ? " Celsius" : " Kelvin");
        display.display();

        // Setup RFID
        SPI.begin();
        mfrc522.PCD_Init();

        if (!mfrc522.PICC_IsNewCardPresent()) return;
        if (!mfrc522.PICC_ReadCardSerial()) return;

        String content = "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }

        content.toUpperCase();
        if (content.substring(1) == "A0 79 C2 49") {
            display.clearDisplay();
            Serial.println("Acesso Autorizado");
            display.setCursor(30, 30);
            display.print("Acesso");
            display.setCursor(10, 45);
            display.print("Autorizado");
            display.display();
            delay(1500);
            acesso = 1;
        } else {
            display.clearDisplay();
            Serial.println("Acesso Negado");
            display.setCursor(30, 30);
            display.print("Acesso");
            display.setCursor(30, 45);
            display.print("Negado");
            display.display();
            delay(1000);
            acesso = 0;
        }
    } else {
        // Menu de configurações
        display.clearDisplay();
        display.drawRect(0, 0, 128, 64, WHITE);
        display.setCursor(0, 30);
        display.print("1. Config");
        display.setCursor(0, 45);
        display.print("2. Sair");
        display.display();

        // Botão 1
        if (digitalRead(2) == HIGH) {
            botao1 = 1;
        }
        if (digitalRead(3) == HIGH) {
            acesso = 0;
        }

        if (botao1 == 1) {
            do {
                display.clearDisplay();
                display.drawRect(0, 0, 128, 64, WHITE);
                display.setCursor(0, 15);
                display.print("2.Voltar");
                display.setCursor(0, 35);
                display.print("3. Fonte");
                display.setCursor(0, 55);
                display.print("4.Temp C/K");
                display.display();

                if (digitalRead(3) == HIGH) {
                    botao1 = 0;
                    break; // Volta ao menu principal
                }

                if (digitalRead(4) == HIGH) {
                  const_font = (const_font == 0) ? 1 : 0; // Troca entre fontes
                    display.clearDisplay();
                    display.setCursor(0, 15);
                    display.print("Fonte alterada");
                    display.display();
                    delay(1000); // Aguarda 1 segundo para mostrar a mensagem
                }

                if (digitalRead(5) == HIGH) {
                    const_temp = (const_temp == 0) ? 1 : 0; // Troca entre Celsius e Kelvin
                    display.clearDisplay();
                    display.setCursor(0, 15);
                    display.print("Medida alterada");
                    display.display();
                    delay(1000); // Aguarda 1 segundo para mostrar a mensagem
                }
            } while (true);
        }
    }
}
