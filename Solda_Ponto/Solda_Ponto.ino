#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define pin_Potenciometro A0
#define pin_Trigger 12
#define pin_Triac 8

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

#define min_Power_ms 3
#define max_Power_ms 120

byte aux2 = 0;
uint16_t time_ms = 0;

void setup(){
  Serial.begin(115200);
  
  pinMode(pin_Triac, OUTPUT);
  pinMode(pin_Trigger, INPUT_PULLUP);

  if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(F("Solda ponto"));
  display.setCursor(0, 20);
  display.print(F("Adrian.piveta"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop(){
  trigger();
  screenOne();
}

void trigger(){
  if (!digitalRead(pin_Trigger)){
    aux2 = 1;
  }

  if (digitalRead(pin_Trigger) && aux2 == 1){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Soldando!");
    display.display();
    digitalWrite(pin_Triac, HIGH);
    delay(time_ms);
    digitalWrite(pin_Triac, LOW);
    delay(time_ms);
    aux2 = 0;
  }
}

void screenOne(){
  display.clearDisplay();
  //Posição Largura/Altura
  display.setCursor(0, 0);
  display.print("pot: ");
  display.display();
  display.setCursor(54, 0);

  int potValue = analogRead(pin_Potenciometro);
  int valorEnergia = map(potValue, 0, 1023, 1, 100);

  display.setTextSize(2);
  display.print(valorEnergia);

  time_ms = map(valorEnergia, 1, 100, min_Power_ms, max_Power_ms);
  Serial.println(time_ms);
  display.display();
}