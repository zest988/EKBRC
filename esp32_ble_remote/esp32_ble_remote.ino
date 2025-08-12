#include <BleKeyboard.h>
#include <ezButton.h>

BleKeyboard bleKeyboard("KOReader-Remote", "Kobo", 100);

#define BUTTON_NEXT 21  // GPIO21 for NEXT page
#define BUTTON_PREV 22  // GPIO22 for PREV page

ezButton buttonNext(BUTTON_NEXT);
ezButton buttonPrev(BUTTON_PREV);

void setup() {
  Serial.begin(115200);
  buttonNext.setDebounceTime(50);
  buttonPrev.setDebounceTime(50);
  
  pinMode(BUTTON_NEXT, INPUT_PULLUP);
  pinMode(BUTTON_PREV, INPUT_PULLUP);
  
  bleKeyboard.begin();
  esp_ble_gap_set_scan_mode(ESP_BLE_CONNECTABLE, ESP_BLE_GEN_DISC_FLAG);
}

void loop() {
  buttonNext.loop();
  buttonPrev.loop();
  
  if (!bleKeyboard.isConnected()) {
    delay(1000);
    return;
  }

  if (buttonNext.isPressed()) {
    Serial.println("NEXT page triggered");
    bleKeyboard.write(KEY_RIGHT_ARROW);
  }

  if (buttonPrev.isPressed()) {
    Serial.println("PREV page triggered");
    bleKeyboard.write(KEY_LEFT_ARROW);
  }
  
  delay(10);
}
