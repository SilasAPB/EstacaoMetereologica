#include <Adafruit_Sensor.h> //INCLUSAO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSAO DE BIBLIOTECA
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


DHT dht(3, DHT22);

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

float pressao,alt; //pressao
float umid;//umidade
int adc;//temperatura
float tensao,temp;//temperatura
int bin;//luminosidade
float Vout, RLDR, lum;//luminosidade

LiquidCrystal_I2C lcd(0x27,16,2);

byte degreeSymbol[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bmp.begin(0x76); // Inicia o BMP no endereco 0x76
  lcd.init(); // inicializa o lcd
  lcd.backlight(); // liga o backlight
  dht.begin();
  analogReference(INTERNAL); // Conversao A/D com fundo de escala de 1.1V
  // lcd.setCursor(coluna,linha);

  lcd.setCursor(0, 0);
  lcd.print("Instrumentacao");
  lcd.setCursor(0,1);
  lcd.print("e Medicao");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Instrumestres");
  lcd.setCursor(0,1);
  lcd.print("Lara,Yondu,Silas");
  delay(3000);
  
  lcd.createChar(0, degreeSymbol);
}

void loop() {
  // put your main code here, to run repeatedly:

    adc = analogRead(A0);       //Le a entrada analogica A0
    tensao = adc*(1.1/1024);    // converte em tensao
    temp = tensao*100;// converte em temperatura (oC)

    pressao=bmp.readPressure(); // retorna a pressao em Pascal (Pa)
    alt= bmp.readAltitude(1013.25); // retorna a altitude em metros
                                    // 1 atm = 1013,25 hPa (hectopascal)

    umid = dht.readHumidity();
    //IMPRIME NO MONITOR SERIAL

    bin = analogRead(A3);
    Vout = bin*1.1/1024.0;
    RLDR = Vout/(3.3 - Vout)*50000;
    lum = pow(10,-1.03*log10(RLDR) + 6.05);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperatura(");
    lcd.setCursor(12,0);
    lcd.write(lcd.write(byte(0)));
    lcd.setCursor(13,0);
    lcd.print("C): ");
    lcd.setCursor(0,1);
    temp = 1.0043 * temp - 1.3262; //temperatura calibrada
    lcd.print(temp,2);
    delay(2000);


    Serial.println(pressao);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pressao (Pa): "); 
    lcd.setCursor(0,1);
    lcd.print(pressao);
    delay(2000);

    Serial.println(umid);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade (%): ");
    lcd.setCursor(0,1);
    umid = 1.0516 * umid - 2.6550; //calibração da umidade
    lcd.print(umid); 
    delay(2000);


    Serial.println(alt);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Altitude (m): "); 
    lcd.setCursor(0,1);
    lcd.print(alt); 
    delay(2000);

    
    Serial.println(lum);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ilumin. (lx): "); 
    lcd.setCursor(0,1);
    lcd.print(lum); 
    delay(2000);
}
