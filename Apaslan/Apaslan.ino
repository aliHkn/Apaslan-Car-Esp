#include <BluetoothSerial.h>
#include <Arduino_JSON.h>

const int pin[] = {12, 14, 25, 26, 27};
BluetoothSerial SerialBT;
String password = "123456";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Apaslan Düt Düt");
  for (int i = 0; i < 5; i++) {
    pinMode(pin[i], OUTPUT);
  }
}

void loop() {
  if (SerialBT.available()) {
    String data = SerialBT.readStringUntil('\n');

    JSONVar doc = JSON.parse(data);

    if (JSON.typeof(doc) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }

    String receivedPassword = (const char*)doc["password"];
    if (receivedPassword == password) {
      int status = (int)doc["status"];
      double x = (double)doc["x"];
      double y = (double)doc["y"];
      if (status == 1) {
        digitalWrite(27, HIGH);
      } else {
        digitalWrite(27, LOW);
      }
      if (y < -0.3) {
        digitalWrite(12, HIGH);
        digitalWrite(14, LOW);
      } else if (y > 0.3) {
        digitalWrite(14, HIGH);
        digitalWrite(12, LOW);
      } else {
        digitalWrite(12, LOW);
        digitalWrite(14, LOW);
      }

      if (x < -0.3) {
        digitalWrite(25, HIGH);
        digitalWrite(26, LOW);
      } else if (x > 0.3) {
        digitalWrite(26, HIGH);
        digitalWrite(25, LOW);
      } else {
        digitalWrite(25, LOW);
        digitalWrite(26, LOW);
      }
    }
  }
}
