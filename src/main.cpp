#include "donneescapteur.h"

Queue<float> mesures(5, 0.0f); // File de 5 float, remplie avec 0.0

void setup()
{
  Serial.begin(115200);

  mesures.remplir(2.0f);
  mesures.push(3.0f);
  mesures.push(4.0f);
  mesures.push(5.0f);
  mesures.push(6.0f);

  Serial.print("Moyenne : ");
  Serial.println(mesures.moyenne(), 3);

  Serial.print("Ecart (max-min) : ");
  Serial.println(mesures.ecart(), 3);

  Serial.print("Ecart type : ");
  Serial.println(mesures.ecartType(), 3);
}

void loop() {}
