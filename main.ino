#include <PololuLedStrip.h>
#include <EEPROM.h>

PololuLedStrip<6> ledStrip;
 
#define LED_COUNT 1 //Количество светодиодов
#define ID_1 29 // id первого светодиода
#define ID_2 0 // id второго светодиода
#define ID_3 0 // id третьего светодиода

int id = 0;
const int ids[] = {ID_1, ID_2, ID_3};

rgb_color colors[LED_COUNT];

void setup() {
  Serial.begin(19200);
    rgb_color color;
    color.red = EEPROM.read(1);
    color.green = EEPROM.read(2);
    color.blue = EEPROM.read(3);
    for(uint16_t i = 0; i < LED_COUNT; i++){
      colors[i] = color;
    }
    ledStrip.write(colors, LED_COUNT);
}

void loop() {
  rgb_color color;
    if (Serial.available()) {
      char c = Serial.peek();
      if (!(c >= '0' && c <= '9')) {
        Serial.read();
      } else {
        id = Serial.parseInt();
        color.red = Serial.parseInt();
        color.green = Serial.parseInt();
        color.blue = Serial.parseInt();
        for(uint16_t i = 0; i < LED_COUNT; i++){
           if (id == ids[i]){
              colors[i] = color;
              ledStrip.write(colors, LED_COUNT);
            }
            if (id == 99){
                for(uint16_t i = 0; i < LED_COUNT; i++){
                  colors[i] = color;
                }
                ledStrip.write(colors, LED_COUNT);
            }
            if (id == 88){
                EEPROM.write(1, byte(color.red));
                EEPROM.write(2, byte(color.green));
                EEPROM.write(3, byte(color.blue));
                for(uint16_t i = 0; i < LED_COUNT; i++){
                  colors[i] = color;
                }
                ledStrip.write(colors, LED_COUNT);
            }
        }
      }
    }
}
