#include <VirtualWire.h>

char message[] = " ";

void setup() {
  Serial.begin(9600);

  vw_set_ptt_inverted(true);
  vw_set_rx_pin(2);
  vw_setup(4000);
  vw_rx_start();  // Alıcıyı başlat

  pinMode(9, OUTPUT);  // L298N'in IN4 Girişi
  pinMode(6, OUTPUT);  // L298N'in IN3 Girişi
  pinMode(3, OUTPUT);  // L298N'in IN2 Girişi
  pinMode(5, OUTPUT);  // L298N'in IN1 Girişi
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Mesaj alındığında işleme başla
  if (vw_get_message(buf, &buflen)) {
    message[0] = (char)buf[0];

    if (message[0] == '0') {
      motorDur();
    } else if (message[0] == '1') {
      ileri();
      delay(1000);
      motorDur();
    } else if (message[0] == '2') {
      geri();
      delay(1000);
      motorDur();
    } else if (message[0] == '3') {
      sag();
      delay(1000);
      motorDur();
    } else if (message[0] == '4') {
      sol();
      delay(1000);
      motorDur();
    }
  }
}

void ileri() {
  digitalWrite(6, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
}

void geri() {
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
}

void sag() {
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
}

void sol() {
  digitalWrite(6, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
}

void motorDur() {
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
}
