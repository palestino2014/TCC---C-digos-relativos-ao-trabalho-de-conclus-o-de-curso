#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
 
#define SERVO 6 // Porta Digital 6 PWM
Servo s; // Variável Servo
int pos; // Posição Servo
// variaveis para sensor de umidade do solo
int umidade;
int i;
unsigned long time;

// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa...
//de rede.  
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 200 }; // Define o endereço IP.

// Porta onde estará aberta para comunicação Internet e Arduino.
EthernetServer server(80);  
 
String readString;
int pin = 7; 
int pin2 = 8;

#define pino_trigger 4
#define pino_echo 5

//vaso 1
int umidade1; //inferior 
int umidade2; //superior

//vaso 2
int umidade3; //inferior 
int umidade4; //superior

//vaso 2
int umidade5; //inferior 
int umidade6; //superior
//int rele1 = 8;

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup(){
 
 Serial.begin(9600);
 pinMode(pin, OUTPUT);
 pinMode(pin2, OUTPUT);   // Define o Pino 10 como saída.
 digitalWrite(pin, HIGH); 
 digitalWrite(pin2,HIGH);   
  Ethernet.begin(mac, ip); // Chama o MAC e o endereço IP da placa Ethernet.
  //  Inicia o servidor que esta inserido junto a placa Ethernet.
  server.begin(); 

  s.attach(SERVO);
  s.write(90); // Inicia motor posição zero
  
  delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor
   
}
 
void loop(){

 time = millis();
    
 umidade1 = analogRead(A0);
 umidade2 = analogRead(A1);
 
 umidade3 = analogRead(A2);
 umidade4 = analogRead(A3);

 umidade5 = analogRead(A4);
 umidade6 = analogRead(A5); 

 int Porcento1 = map(umidade1, 1023, 382, 0, 100);
 int Porcento2 = map(umidade2, 1023, 327, 0, 100);

 int Porcento3 = map(umidade3, 1023, 285, 0, 100);
 int Porcento4 = map(umidade4, 1023, 15, 0, 100);

 int Porcento5 = map(umidade5, 1023, 240, 0, 100);
 int Porcento6 = map(umidade6, 1023, 230, 0, 100);

   //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);  

  float vol,H, Ab, deltaH;

  //volume
  H = 26.0;
  deltaH = (H-cmMsec);
  Ab = (3.14)*((4.55*4.55));

  if ( deltaH  > 0 ) {
  vol = deltaH*Ab;    }
  else { vol = 0; }

                  
      
   //programcao relativa ao servidor WEB
   EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       if (readString.length() < 100) {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
           // A partir daqui começa o código html.
    
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>TCC</H1>");

//192.168.0.103/tcc2/salvardados.php?umidade1=1020&umidade2=1019&umidade3=734&umidade4=607&umidade5=954&umidade6=1023 &cmMsec=5.38
//                String a = "GET /192.168.0.103/tcc2/salvardados.php?
                                             
                   client.print("http://192.168.0.103/tcc2/salvardados.php?");
                   client.print("umidade1=");
                   client.print(Porcento1);
                   client.print("&umidade2=");
                   client.print(Porcento2);
                   client.print("&umidade3=");
                   client.print(Porcento3);              
                   client.print("&umidade4=");
                   client.print(Porcento4);
                   client.print("&umidade5=");
                   client.print(Porcento5);
                   client.print("&umidade6=");
                   client.print(Porcento6); 
                   client.print("&cmMsec=");
                   client.println(cmMsec); 
                                
                  client.println("<br />");         
                  client.println("<a href=\"/facacomarduino/LedOn\"\">DESLIGAR BOMBA</a>");
                  client.println("<br />");
                  client.println("<hr />");
                  client.println("<a href=\"/facacomarduino/LedOff\"\">LIGAR BOMBA</a><br />");   
                  client.println("<hr />");
                  client.println("<br />");
                  client.println("<a href=\"/facacomarduino/On\"\">DESLIGAR VALVULA</a>");
                  client.println("<br />");
                  client.println("<hr />");
                  client.println("<a href=\"/facacomarduino/Off\"\">LIGAR VALVULA</a><br />");   
                  client.println("<hr />");
     
                  client.println("<a href=\"/facacomarduino/encher\"\">ENCHER RESERVATORIO</a><br />");   
                  client.println("<hr />");
                  
                  client.println("<br />");
                   
                  client.println("<a href=\"/facacomarduino/40\"\">40</a>");
                  client.println("<br />");
                  client.println("<hr />");
                  client.println("<a href=\"/facacomarduino/90\"\">90</a><br />");   
                  client.println("<hr />");
                  client.println("<br />");
                  client.println("<a href=\"/facacomarduino/130\"\">130</a>");
                  //client.print("<a name='vasos'>"); 
                  client.println("<br />");
                  client.println("<hr />");
                 
                  client.print("<a name='vasos'>"); 
                  client.print("vaso 1  superior  = "); 
                  client.print(Porcento2);
                  client.print("</a>");                  
                  
                  client.println("<br />");
                  client.print("vaso 1  inferior = "); 
                  client.print(Porcento1);
                  
                  client.print("<br>");
                  client.print("----------------------"); 
                  client.print("<br>");
                  client.print("vaso 2  superior = "); 
                  client.print(Porcento4);
                  
                  client.print("<br>");
                  client.print("vaso 2  inferior  = "); 
                  client.print(Porcento3);
                  
                  client.print("<br>");
                  client.print("----------------------"); 
                  client.print("<br>");
                  client.print("vaso 3  superior  = "); 
                  client.print(Porcento6);
                  
                  client.print("<br>");
                  client.print("vaso 3  inferior  = "); 
                  client.print(Porcento5); 
                   client.print("<br>");
                    client.print("<br>");
                     client.print("<br>");
                      client.print("<br>");                  
                  client.print("<br>");
                  client.print("<a name='V'>");
                  client.print("distancia fluido = "); 
                  client.print(cmMsec);  
                  client.print("<br>");                 
                  client.print("Volume do reservatorio (ML3) = "); 
                  client.print(vol); 
                  client.print("</a>");
                   
                  client.print("<br>");
                  
                  client.print("<meta http-equiv='refresh' content='5'>");
                               
                  client.println("</BODY>");
                  client.println("</HTML>");
                    
           delay(1000);
           client.stop();

          if(readString.indexOf("facacomarduino/encher") > 0)
          {
             // if (cmMsec >= 5)
             // digitalWrite(pin, HIGH);
             // else (digitalWrite(pin, LOW));                  
          }
          if(readString.indexOf("facacomarduino/LedOn") > 0)
          {
            digitalWrite(pin, HIGH);  // Liga          
          }
          if(readString.indexOf("facacomarduino/LedOff") > 0)
          {
            digitalWrite(pin, LOW);  // Desliga
          }
           if(readString.indexOf("facacomarduino/On") > 0)
          {
            digitalWrite(pin2, HIGH);  // Liga          
          }
          if(readString.indexOf("facacomarduino/Off") > 0)
          {
            digitalWrite(pin2, LOW);  // Desliga
          }  
          if(readString.indexOf("facacomarduino/40") > 0)
          {
            s.write(30);         
          }
          if(readString.indexOf("facacomarduino/90") > 0)
          {
            s.write(90);
          }         
          if(readString.indexOf("facacomarduino/130") > 0)
          {
            s.write(140);
          }            
          readString="";              
        }
      }
    }
  }
  
// Serial.print("vaso 1  inferior = "); 
// Serial.print(Porcento1);
// Serial.println(" %");
// Serial.print("vaso 1  superior  = "); 
// Serial.print(Porcento2);
// Serial.println(" %");
// Serial.println("---"); 
// Serial.print("vaso 2  inferior = "); 
// Serial.print(Porcento3);
// Serial.println(" %");
// Serial.print("vaso 2  superior  = "); 
// Serial.print(Porcento4);
// Serial.println(" %");
// Serial.println("---"); 
// Serial.print("vaso 3  inferior  = "); 
// Serial.print(Porcento5);
// Serial.println(" %");
// Serial.print("vaso 3  superior  = "); 
// Serial.print(Porcento6);
// Serial.println(" %");
//Serial.print("DeltaH ");
//Serial.print(deltaH);
//Serial.print(" AltCM ");
//Serial.print(cmMsec);
//Serial.println("cm ");
//Serial.print(" VolumeML "); 
//Serial.print(vol);  
//Serial.print(" - ");

Serial.print(" Sensor 1 ");
Serial.print(umidade1);
Serial.print(" Sensor 2 ");
Serial.print(umidade2);
Serial.print(" Sensor 3 ");
Serial.print(umidade1);
Serial.print(" Sensor 4 ");
Serial.print(umidade4);
Serial.print(" Sensor 5 ");
Serial.print(umidade5);
Serial.print(" Sensor 6 ");
Serial.print(umidade6);

Serial.print("TimeSegundo ");
Serial.println(time/1000);
Serial.println("---------------------"); 
 
delay(2000);   
  
}

