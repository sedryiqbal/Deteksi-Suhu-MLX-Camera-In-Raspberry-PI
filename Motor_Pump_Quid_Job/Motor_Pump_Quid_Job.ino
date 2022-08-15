#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#define RELAY1 D1
//#define RELAY2 D5
#define IR D5
#define triggerPin  D3
#define echoPin     D2


float pinBlynk = V10;
//
char auth[] = "Cp1M8OIDMWLav-XAfz9XmvR24yZE7SS-";
char ssid[] = "Wifi";
char pass[] = "minion123";
//char ssid[] = "12345";
//char pass[] = "namaakuu";

int jarakS;

BlynkTimer timer;


void setup() {

  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);
  pinMode(IR, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //  digitalWrite(RELAY1, LOW);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("Connected to ");
    Serial.println(ssid);
    delay(1000);
    timer.setInterval(100L, setDataToBlynk);
}

void setDataToBlynk() {
  Blynk.virtualWrite(pinBlynk, jarakS);
}

void loop() {
    Blynk.run();
    timer.run();
    long duration, jarak;
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    jarak = (duration / 2) / 29.1;
    jarakS = jarak;
    Serial.print("Jarak= ");
    Serial.println(jarakS);
  //  digitalWrite(RELAY1, LOW);

  int hasil = digitalRead(IR);
  //  hasil = LOW;

  //  Serial.println(hasil);
  if (hasil == LOW) //buzzer on
  {
    //    Serial.println("Hambatan Terdeteksi");
    digitalWrite(RELAY1, LOW);
  }
  if (hasil == HIGH ) //buzzer off
  {
    //      Serial.println ("Tidak Ada Hambatan");
    digitalWrite (RELAY1, HIGH);
  }
//    delay(200);
}
