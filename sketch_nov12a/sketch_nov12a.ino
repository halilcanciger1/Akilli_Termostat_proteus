#include <LiquidCrystal.h>

const int rs=2 , en = 3, d4 = 4, d5 = 5, d6 = 6 , d7 = 7;
// LCD pin tanımları (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(rs , en, d4, d5, d6, d7);


float temp;
const int relayPin = 8; // Röle bağlantısı

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  lcd.begin(16, 2);  // LCD başlat
  pinMode(relayPin, OUTPUT); // Röle çıkış olarak ayarlanır
  digitalWrite(relayPin, LOW); // Röle başlangıçta kapalı
}

void loop() {
  temp= analogRead(A0); // Sıcaklık sensörü verisi // Sıcaklık sensörü verisi
  temp = temp * 1100 / (1024 * 10); // Sensörden gelen voltaj değeri
   // LM35'in sıcaklık değeri (mV/C)

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1); // Ondalık hassasiyet
  lcd.print(" C  "); // Boşluklar ile önceki karakterleri siler

  if (temp < 20) { // 20°C'nin altında ısıtıcıyı aç
    digitalWrite(relayPin, HIGH); // Röle aktif
    lcd.setCursor(0, 1);
    lcd.print("Heater ON     ");
  } else if (temp > 25) { // 25°C'nin üstünde soğutucuyu aç
    digitalWrite(relayPin, LOW); // Röle pasif
    lcd.setCursor(0, 1);
    lcd.print("Cooler ON     ");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("System Idle   ");
    digitalWrite(relayPin, LOW); // Röle kapalı
  }

  delay(1000); // 1 saniye bekle
  lcd.clear();
}
