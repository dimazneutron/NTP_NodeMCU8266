#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "INALIX";
const char *password = "inalixjaya";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP); //utc time

int hari,jam,menit,detik;
int local_time=7;

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());  //print utc time
  Serial.println("...........................................................................................");
  convertTime();

  delay(1000);
}

void convertTime(){ //converted to local time
  hari=timeClient.getDay();
  jam=timeClient.getHours() + (local_time);
  menit=timeClient.getMinutes();
  detik=timeClient.getSeconds();
  if(jam==24){
    jam=0;
  }
  if(jam > 24){
    hari = timeClient.getDay() + 1;
    jam = ((local_time) + timeClient.getHours()) - 24;
  }
  if(jam < 0){
    hari = timeClient.getDay() - 1;
    jam = ((local_time) + timeClient.getHours()) + 24;
  }
  
  
  Serial.print("Day     = ");Serial.println(hari);
  Serial.print("Hours   = ");Serial.println(jam);
  Serial.print("Minutes = ");Serial.println(menit);
  Serial.print("Seconds = ");Serial.println(detik);
}
