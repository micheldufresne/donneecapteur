#include "donneescapteur.h"
#include "arduinoOTA.h"
#include "config.h"
const char *hostName = "essai";
TabLastData<uint16_t> mesures(10, 0); // Tableau de 10 float, rempli avec 0


void initOTA()
{
  ArduinoOTA.setHostname(hostName);
  ArduinoOTA.setPort(3232);
  ArduinoOTA.setPassword(passwordOTA);
}

void demandeOTA()
{
  ArduinoOTA.begin();
  ArduinoOTA.handle(); // test s'il y a une demande OTA
}

void testWifiOk()
{
  uint8_t nbEssais = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    nbEssais++;
    if (nbEssais > 5)
      ESP.restart();
  }
}

void setupwifi()
{
  WiFi.begin(ssid, password);

  // check wi-fi is connected to wi-fi network
  testWifiOk();
}

void setup()
{
  Serial.begin(115200);

  //mesures.remplir(2u);
  mesures.push(3);
  mesures.push(4);
  mesures.push(5);
  mesures.push(6);
  //mesures.remplir(2u);
/*   mesures.push(3u);
  mesures.push(4u);
  mesures.push(5u);
  mesures.push(6u); */

  Serial.print("Moyenne : ");
  Serial.println(mesures.moyenne(), 3);

  Serial.print("Ecart (max-min) : ");
  Serial.println(mesures.ecart(), 3);

  Serial.print("Ecart type : ");
  Serial.println(mesures.ecartType(), 3);
  setupwifi();
}

void loop() {

  testWifiOk(); // vérifie le wifi et redémarre si ça tarde

  demandeOTA();

  uint16_t v=analogRead(34);
  //Serial.println(v);
  mesures.push(v);
  float m = mesures.moyenne();
  Serial.printf("v=%u  \tmoyenne=%.2f  \tecart=%.2f  \tecartType=%.2f\n",
                              v, m, mesures.ecart(), mesures.ecartType());
  
  delay(500);
}
