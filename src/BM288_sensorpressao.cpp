#include <Adafruit_Sensor.h> //INCLUSAO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSAO DE BIBLIOTECA

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)
float pressao,temp,alt; // declaracao de variaveis

void setup(){
  Serial.begin(9600);
  bmp.begin(0x76); // Inicia o BMP no endereco 0x76
  // Esse 0x76 se refere ao endereço dele, podem ser alterados 
}

void loop(){
    pressao=bmp.readPressure(); // retorna a pressao em Pascal (Pa)
    temp=bmp.readTemperature(); // retorna a temperatura em grau celsius
    alt= bmp.readAltitude(1013.25); // retorna a altitude em metros
                                    // 1 atm = 1013,25 hPa (hectopascal)
  
    //IMPRIME NO MONITOR SERIAL
    Serial.print("Pressão: "); 
    Serial.print(pressao); 
    Serial.println(" Pa");

    Serial.print("Temperatura: ");
    Serial.print(temp); 
    Serial.println(" °C");

    Serial.print("Altitude aprox.: "); 
    Serial.print(alt); 
    Serial.println(" m");
    
    Serial.println("-----------------------------------"); 
    delay(2000); //INTERVALO DE 2 SEGUNDO
}
