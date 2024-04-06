#include <VirtualWire.h>
#include "U8glib.h"

#define x A0
#define y A1

char message; // Karakter değişkeni olarak tanımlayın
int x_deger;
int y_deger;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
char bufferX [20];
char bufferY [20];
char bufferZ [20];

void setup() {
  Serial.begin(9600);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(3);
  vw_setup(4000);
  vw_rx_start(); // Alıcıyı başlat

  sprintf(bufferX, "    Roboboard");
  sprintf(bufferY, "    M1 Proje");
  sprintf(bufferZ, "    Seti");

  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  delay(10);
}

void loop() {
  x_deger = analogRead(x);
  y_deger = analogRead(y);
char message;
  // Düğmelerin değerlerine göre mesajları oluşturun
  if (x_deger > 600) {
    message = '4'; // Sağ
  } else if (x_deger < 200) {
    message = '3'; // Sol
  } else if (y_deger > 600) {
    message = '1'; // İleri
  } else if (y_deger < 200) {
    message = '2'; // Geri
  } else {
    message = '0'; // Dur
  }

  Serial.println(message);
  vw_send((uint8_t *)&message, 1); // Tek bir karakter gönder
  vw_wait_tx();
  delay(100);
}

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, bufferX);
  u8g.drawStr( 0, 40, bufferY);
  u8g.drawStr( 0, 60, bufferZ);
}
