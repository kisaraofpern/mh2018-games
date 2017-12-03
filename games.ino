#include <HX711.h>

// This is also the order of the scales from left to right.
HX711 scaleBes;
HX711 scalePtah;
HX711 scaleSeshat;
HX711 scaleThoth;

void setup() {
  HX711 scales [4] = {scaleBes, scalePtah, scaleSeshat, scaleThoth};
  
  Serial.begin(38400);
  
  Serial.println("Initializing the scales...");

  // Parameter 'gain' omitted from the invocations;
  // default value 128 is used by the HX711 library.

  // Pins for scaleBes:
  // HX711.DOUT  - pin #A0
  // HX711.PD_SK - pin #A1
  scaleBes.begin(A0, A1)

  // Pins for scalePtah:
  // HX711.DOUT  - pin #A3
  // HX711.PD_SK - pin #A4
  scalePtah.begin(A3, A4)

  // Pins for scaleSeshat:
  // HX711.DOUT  - pin #A6
  // HX711.PD_SK - pin #A7
  scaleSeshat.begin(A6, A7)

  // Pins for scaleThoth:
  // HX711.DOUT  - pin #A9
  // HX711.PD_SK - pin #A10
  scaleThoth.begin(A

  // Set up scaleBes only.
  // After this functionality has been confirmed, we can
  // create a loop to iterate through all of the scales.

  

}

void loop() {
  // put your main code here, to run repeatedly:

}
