#include <LiquidCrystal.h>

LiquidCrystal lcd(15, 14, 13, 12, 11, 10, 9);

// Khai báo LED
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;
// Khai báo chân kích hoạt
const int P12 = 6;
const int P13 = 17;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();

  Serial.begin(9600);

  digitalWrite(P12, HIGH);
  digitalWrite(P13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Đọc giá trị ADC tại chân PC2 (P25) (Dien ap pin) và tính toán
  int adcValue1 = analogRead(A2);
  float voltage1 = (float)adcValue1 * 5 * 2.68 / 1023; // 5 là điện áp Vref, số sau là hệ số nhân

  // Đọc giá trị ADC tại chân PC3 (P26) (Dong dien vao) và tính toán
  int adcValue2 = analogRead(A3);
  float voltage2 = (float)adcValue2 * 5 * 45.95 / 1023;

  // Đọc giá trị ADC tại chân PC4 (P27) (Dong dien ra) và tính toán
  int adcValue3 = analogRead(A4);
  float voltage3 = (float)adcValue3 * 5 * 45.95 / 1023;


  // Đọc giá trị ADC tại chân PC5 (P28) (Nhiet do) và tính toán
  int adcValue4 = analogRead(A5); 
  int voltage4 = adcValue4 * 5 / 1023;

  // Quản lý điện áp
  if(voltage1 < 10.3)
  {
    digitalWrite(P12, LOW);
    digitalWrite(P13, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dien ap thap");
  }

  if(voltage1 > 14.6)
  {
    digitalWrite(P12, LOW);
    digitalWrite(P13, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dien ap cao");
  }

  if(voltage1 >= 10.3 && voltage1 <= 14.6)  // Hiển thị điện áp
  {
    lcd.setCursor(1,0);
    lcd.print(voltage1);
    lcd.setCursor(5,0);
    lcd.print("V");
  }
  
  // Quản lý dòng điện vào
  if (voltage2 < -0.1  || voltage2 >= 20)
  {
    digitalWrite(P12, LOW);
    digitalWrite(P13, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("I vao loi");
  }

  if (voltage2 >= 0 && voltage2 < 20 )
  {
  lcd.setCursor(8,0);
  lcd.print("IN    A");
  lcd.setCursor(11,0);
  lcd.print(voltage2);
  lcd.setCursor(14,0);
  lcd.print("A");
  }

  // Quản lý dòng điện ra
  if (voltage3 < -0.5  || voltage3 >= 20)
  {
    digitalWrite(P12, LOW);
    digitalWrite(P13, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("I ra loi");
  }

  if (voltage3 >= 0 && voltage3 < 20 )
  {
  lcd.setCursor(7,1);
  lcd.print("OUT");
  lcd.setCursor(11,1);
  lcd.print(voltage3);
  lcd.setCursor(14,1);
  lcd.print("A");
  delay(150);
  }
 
  // Quản lý nhiệt độ
  lcd.setCursor(1,1);
  lcd.print(voltage4);
  lcd.setCursor(3,1);
  lcd.print("'C");
  delay(150);
}