#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
#define USE_SERIAL Serial
#define TRIGGER D1 //D1
#define ECHO    D2 //D2
#define led D7

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2c604b489fa84bc2813a2e869414c5f9";  // Put your Auth Token here. (see Step 3 above)
const char* ssid = "BmjK-bnlvaQ";
const char* password = "12341234";
long duration, distance;
void setup()
{
 
  USE_SERIAL.begin(115200);
 //lcd.begin();
  Blynk.begin(auth, ssid, password);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(led, OUTPUT);
  
 USE_SERIAL.println();

 for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
 }
 
 // Konek ke WiFi
 // WiFiMulti.addAP("SSID", "PASSWORD");
 WiFiMulti.addAP(ssid, password);

 // Jika terhubung
 while (!(WiFiMulti.run() == WL_CONNECTED)) {
   USE_SERIAL.println("Menghubungkan...");
   delay(1000);
 }

 delay(1000);

 // Cetak alamat IP
 Serial.print("Terhubung! IP address: ");
 Serial.println(WiFi.localIP());
}

void loop()
{
  digitalWrite(TRIGGER, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration *0.034/2;
  
  Serial.println(String("jaraknya : ")+distance);
  
  Blynk.virtualWrite(V5, distance);
  
  if (distance < 10) {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led,LOW);
      delay(100);
      Blynk.notify("Tong sampah penuh !!");
  }else{
    digitalWrite(led, LOW);
  }
  
  Blynk.run(); //When i comment this line, seems like the readHumidity and ReadTemperature works each time
  delay(5000);
}
