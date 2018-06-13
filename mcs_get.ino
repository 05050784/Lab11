#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "Sorami";
char _lwifi_pass[] = "1110rope1110";
MCSDevice mcs("D2FkhqHz", "zpNevvWwmu4IewaE");
MCSControllerOnOff led("0248");
MCSDisplayOnOff remote("1357");


void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }
  while(!mcs.connected())
  {
      Serial.println("MCS.connect()...");
      mcs.connect();
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  mcs.addChannel(led);
  mcs.addChannel(remote);

  pinMode(7, OUTPUT);

}


void loop()
{
  while(!led.valid())
  {
    Serial.println("read LED value from MCS...");
    led.value();   //取得MCS數值
  }
  Serial.print("done, LED value = ");
  Serial.println(led.value());  //顯示出來
  while (!mcs.connected()) {
    mcs.connect();
    digitalWrite(7,led.value()?HIGH:LOW);
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);

  if (led.value() == 1) {
    digitalWrite(7, HIGH);

  } else {
    digitalWrite(7, LOW);

  }
  if(!remote.set(led.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(remote.value());
    }
  delay(200);
}
