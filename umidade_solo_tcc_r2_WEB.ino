
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 199);
EthernetServer server(80);
EthernetClient cliente;

String readString; //parametro de leitura da pag HTML
int Pin = 7;  //Pino digital onde será ligado e desligado o dispositivo 1.
int Pin1 = 4; //Pino digital onde será ligado e desligado o dispositivo 2.
int Pin2 = 8; //Pino digital onde será ligado e desligado o dispositivo 3.
int Pin3 = 10; //Pino digital onde será ligado e desligado o dispositivo 4.



//Define os pinos para o trigger e echo
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
  
void setup()
{
 Serial.begin(9600);
 pinMode(13, OUTPUT);
 pinMode(Pin, OUTPUT);   // Define o Pino 7 como saída.
 pinMode(Pin1, OUTPUT);  // Define o Pino 4 como saída.
 pinMode(Pin2, OUTPUT);  // Define o Pino 8 como saída.
 pinMode(Pin3, OUTPUT);  // Define o Pino 8 como saída.
 
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

 

void loop()
{
  
 umidade1 = analogRead(A0);
 umidade2 = analogRead(A1);
 
 umidade3 = analogRead(A2);
 umidade4 = analogRead(A3);

 umidade5 = analogRead(A4);
 umidade6 = analogRead(A5);
 

 int Porcento1 = map(umidade1, 1023, 0, 0, 100);
 int Porcento2 = map(umidade2, 1023, 0, 0, 100);

 int Porcento3 = map(umidade3, 1023, 0, 0, 100);
 int Porcento4 = map(umidade4, 1023, 0, 0, 100);

 int Porcento5 = map(umidade5, 1023, 0, 0, 100);
 int Porcento6 = map(umidade6, 1023, 0, 0, 100);

  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
         if (readString.length() < 100) {
           readString += c;
         }
        
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

            client.print("vaso 1  inferior = "); 
            client.print(Porcento1);
            client.print("<br>"); 
            client.print("vaso 1  superior  = "); 
            client.print(Porcento2);
            client.print("<br>");
            client.print("----------------------"); 
            client.print("<br>");
            client.print("vaso 2  inferior = "); 
            client.print(Porcento3);
            client.print("<br>");
            client.print("vaso 2  superior  = "); 
            client.print(Porcento4);
            client.print("<br>");
            client.print("----------------------"); 
            client.print("<br>");
            client.print("vaso 3  inferior  = "); 
            client.print(Porcento5);
            client.print("<br>");
            client.print("vaso 3  superior  = "); 
            client.print(Porcento6);   

            client.print("<meta http-equiv='refresh' content='5'>"); 
            
          // output the value of each analog input pin
//          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
//            int sensorReading = analogRead(analogChannel);
//            client.print("analog input ");
//            client.print(analogChannel);
//            client.print(" is ");
//            client.print(sensorReading);
//            client.println("<br />");
//          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");

      if(readString.indexOf("android/Abre") > 0)
           {
            
             digitalWrite(Pin1, HIGH);
             
           }
    Serial.println("client disconnected");

    
    
  }

 Serial.print("vaso 1  inferior = "); 
 Serial.print(Porcento1);
 Serial.println(" %");
 Serial.print("vaso 1  superior  = "); 
 Serial.print(Porcento2);
 Serial.println(" %");
 Serial.println("---"); 
 Serial.print("vaso 2  inferior = "); 
 Serial.print(Porcento3);
 Serial.println(" %");
 Serial.print("vaso 2  superior  = "); 
 Serial.print(Porcento4);
 Serial.println(" %");
 Serial.println("---"); 
 Serial.print("vaso 3  inferior  = "); 
 Serial.print(Porcento5);
 Serial.println(" %");
 Serial.print("vaso 3  superior  = "); 
 Serial.print(Porcento6);
 Serial.println(" %");

 
 Serial.println("###################");
 delay(5000);



  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  Serial.print(" - Distancia em polegadas: ");
  Serial.println(inMsec);
  delay(1000);  
}

