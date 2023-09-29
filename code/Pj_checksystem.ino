#include <WiFi.h>
#include <HTTPClient.h>
int x=0;
const char* ssid     = "OPPO A31";      // SSID
const char* password = "tew123456";      // Password
const char* host = "192.168.43.173";  // IP serveur - Server IP
const int   port = 80;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis(); 
void tr(){
  //int x = random(1,100);
    //int t = random(1,100);     
    Serial.print(x);

    unsigned long currentMillis = millis();
    
  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;
  
    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/TutorialESP32/lol.php?hum=";
    url += x;
    
    // Enviamos petición al servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  
    // Leemos la respuesta del servidor
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }
  delay(800);
}
void setup(void)
{ 
  pinMode(33, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.begin(115200);
  Serial.println("Humedad y Temperatura\n\n");
  delay(700);

}
void loop() {   
    // put your main code here, to run repeatedly:
int s = digitalRead(33);
int r = digitalRead(25);
Serial.println(x);
if (r == LOW){
  x--;
  delay(500);
}
if (s == LOW){
  x++;
  delay(500);
}
if (x<0)x=0; 
    tr();
}
