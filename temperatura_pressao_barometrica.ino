#include <SFE_BMP180.h>
#include <Wire.h>
#include <dht.h>

#define dht_dpin A1 //Pino DATA do Sensor ligado na porta Analogica A1
 //Pino DATA do Sensor ligado na porta Analogica A1

dht DHT; //Inicializa o sensor
SFE_BMP180 pressure;
#define ALTITUDE 588


int luminosidade;
int valoruv;

void setup()
{
  Serial.begin(9600);
  valoruv=0;  
  delay(2000);   
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }  
  delay(2000);//Aguarda 2 seg antes de acessar as informações do sensor
}

void loop()
{
  luminosidade = analogRead(A3);
  char status;
  double T,P,p0,a;  
  valoruv = analogRead(A0);
    
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");
  Serial.println("----------------------------------------");  

  DHT.read11(dht_dpin); //Lê as informações do sensor
  Serial.println("Sensor 1");
  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura = ");
  Serial.print(DHT.temperature); 
  Serial.println(" Celsius  ");
  Serial.println("----------------------------------------"); 
  Serial.println("Luminosidade  ");
  Serial.println(luminosidade);
  Serial.println("----------------------------------------"); 
  Serial.println("UV ");
  Serial.println(valoruv);
       
  Serial.println("----------------------------------------");   
  
 
  delay(2000);
   status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");

          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");    
     delay(6000);    
     Serial.println("########################################"); 
}

