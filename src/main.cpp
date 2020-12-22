#include <Arduino.h>
#include <M5Atom.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  M5.begin(true, false, true);
  delay(50);
  M5.dis.drawpix(0, CRGB(0xff, 0, 0));
  bleKeyboard.begin();
}

int seq = -1;

void loop() {
  delay(100);
  M5.update();
  if (bleKeyboard.isConnected()) {
    M5.dis.drawpix(1, CRGB(0, 0, 0xff));
    if (M5.Btn.isPressed() && seq < 0) {
      seq = 0;
      M5.dis.drawpix(2, CRGB(0, 0xff, 0));
    }
    if (seq >= 0 && seq < 4) {
      switch (seq) {
        case 0: bleKeyboard.press(13); break;
        case 1: bleKeyboard.release(13); break;
        case 2: bleKeyboard.press(KEY_MEDIA_VOLUME_UP); break;
        case 3: bleKeyboard.release(KEY_MEDIA_VOLUME_UP); break;
      }
      seq++;
    } else if (seq == 4) {
      M5.dis.drawpix(2, CRGB(0, 0, 0));
      seq = -1;
    }
  } else {
    M5.dis.drawpix(1, CRGB(0, 0, 0));
  }
}
