#include <LiquidCrystal.h>

LiquidCrystal lcd(15, 14, 13, 12, 11, 10, 9);
               // rs, rw, e , d4, d5, d6, d7

// Khai báo LED
const int LED1 = 3; // charging
const int LED2 = 4; // discharging
const int LED3 = 5; // erro
//pin 5 = charing
//pin 6 = discharge
//pin 11 = error
// Khai báo chân kích hoạt
const int P12 = 6;
const int P13 =  7;

void delay1(){
  
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();

  // Đọc giá trị ADC tại chân PC2 (P25) (Dien ap pin) và tính toán
  //int adcValue1 = analogRead(A2);
  //float voltage1 = (float)adcValue1 * 5 * 5.62  / 1023; // 5 là điện áp Vref, số sau là hệ số nhân
 
  delay(100);
  
  Serial.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:
  // ***************** Dien ap vao *********************************************************************************/
  // Đọc giá trị ADC tại chân PC2 (P25) (Dien ap pin) và tính toán
  int adcValue1 = analogRead(A2);
  float voltage1 = (float)adcValue1 * 5 * 5.62  / 1023; // 5 là điện áp Vref, số sau là hệ số nhân
  // ****************************************************************************************************************/

  //******** Đọc giá trị ADC tại chân PC3 (P26) (Dong dien vao) và tính toán ***************************************/
  float voltages2 = 0;
  for(int j = 0; j < 50; j++)
  {
    int adcValue2 = analogRead(A3);
    if( adcValue2 > 1)
    {
      float voltage2b = adcValue2 * 0.0336 + 1.8457;
      voltages2 = voltages2 + voltage2b; 
      delay(50);
    }
  }
  float voltage2 = voltages2/50;

  //*********** Đọc giá trị ADC tại chân PC4 (P27) (Dong dien ra) và tính toán *****************************************/
  float voltages3 = 0;
  for (int k = 0; k < 50; k++)
  {
    int adcValue3 = analogRead(A4);
    if(adcValue3 > 1)
    {
      float voltage3b = adcValue3 * 0.1088 + 1.892;
      voltages3 = voltages3 + voltage3b; 
      delay(50);
    }
  }
  float voltage3 = voltages3/50;
  
  //****************** Đọc giá trị ADC tại chân PC5 (P28) (Nhiet do) và tính toán *************************************/
  int adcValue4 = analogRead(A5);
  adcValue4 = 1023 - adcValue4; 
  int voltage4 = round((float)adcValue4 * 5 * 11.7    / 1023);
  //voltage4 = voltage4/2;
  
//****************************************/
// Quản lý điện áp // 
  
  if(voltage1 < 10.4) // ngắt dòng ra
  {
    digitalWrite(P12, HIGH);  
    digitalWrite(P13, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dien ap thap");
    delay(1000);
    digitalWrite(LED3, HIGH);
    delay(1000);
    digitalWrite(LED3, LOW);
    delay(1000);
    lcd.clear();
  }

  if(voltage1 > 14.6)  // ngắt dòng vào
  {
    digitalWrite(P12, HIGH); 
    digitalWrite(P13, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dien ap cao");
    delay(1000);
     digitalWrite(LED3, HIGH);
    delay(1000);
    digitalWrite(LED3, LOW);
    delay(1000);
    lcd.clear();
  }

  if(voltage1 >= 10.4 && voltage1 <= 14.6)  // Hiển thị điện áp
  {

    lcd.setCursor(1,0);
    lcd.print(voltage1);
    lcd.setCursor(5,0);
    lcd.print("V");
  }
//************************************************************/
// Quan ly dong dien vao
  if (voltage2 >= 15)
  {
    digitalWrite(P12, HIGH);  
    digitalWrite(P13, HIGH);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Qua dong");
    delay(1000);
    digitalWrite(LED3, HIGH);
    delay(1000);
    digitalWrite(LED3, LOW);
    delay(1000);
    lcd.clear();
  }
  if (voltage2 < 15)
  {
    lcd.setCursor(8,0);
    lcd.print("IN");
    lcd.setCursor(11,0);
    lcd.print(voltage2);
    lcd.setCursor(14,0);
    lcd.print("A ");
    if (voltage2 > 0.1)
    {
      digitalWrite(LED1, HIGH);
      delay(1000);
      digitalWrite(LED1, LOW);
      delay(1000);
    }
  }
//***********************************************************/
// Quan ly dong dien ra
  if(voltage3 >= 20)
  {
    digitalWrite(P12, HIGH);  
    digitalWrite(P13, HIGH);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Qua dong");
    delay(1000);
    digitalWrite(LED3, HIGH);
    delay(1000);
    digitalWrite(LED3, LOW);
    delay(1000);
    lcd.clear();
  }
  if(voltage3 < 20)
  {
    lcd.setCursor(7,1);
    lcd.print("OUT");
    lcd.setCursor(11 ,1);
    lcd.print(voltage3);
    lcd.setCursor(14,1);
    lcd.print("A ");
    if (voltage3 > 0.1)
    {
      digitalWrite(LED2, HIGH);
      delay(1000);
      digitalWrite(LED2, LOW);
      delay(1000);
    }
  }
  //Serial.print("Dong dien ra");
  //Serial.println(voltage3, 1);
//**********************************************************/  
// Quản lý nhiệt độ

 if (voltage4 > 60)
 {
   digitalWrite(P12, HIGH);  
   digitalWrite(P13, HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Nhiet do cao ");
   delay(1000);
   digitalWrite(LED3, HIGH);
   delay(1000);
   digitalWrite(LED3, LOW);
   delay(1000);
   lcd.clear();
 }

 if (voltage4 <= 60)
 {

  lcd.setCursor(1,1);
  lcd.print(voltage4);
  lcd.setCursor(3,1);
  lcd.print("'C ");
  } 
} 
