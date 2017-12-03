#include <HX711.h>

// This is the order of the scales from left to right.
HX711 scaleBes;
HX711 scalePtah;
HX711 scaleSeshat;
HX711 scaleThoth;

float weightBes;
float weightPtah;
float weightSeshat;
float weightThoth;
const float weightThreshold = 0.01;

float scaleGainBes;
float scaleGainPtah;
float scaleGainSeshat;
float scaleGainThoth;

// Pin assignments
const int weighButtonPin = 2;
const int maglockPin     = 4;
const int redLED         = 10;
const int greenLED       = 12;
const int blueLED        = 14;

// TODO: Delete this assignment when no longer testing.
const int ledPin         = 13;

int weighButtonState = 0;

// Function definitions
// Check if the weights have been correctly placed.
bool isCorrectlyPlaced() {
  if( (weightBes < weightThreshold)    ||
      (weightSeshat < weightThreshold) ||
      (weightPtah < weightThreshold)   ||
      (weightThoth < weightThreshold)) {
    return false;
  }
  return weightBes < weightSeshat && weightSeshat < weightPtah && weightPtah < weightThoth;
}

// Get the weights from the scales.
void weigh() {
  weightBes    = scaleBes.get_units(5);
  weightPtah   = scalePtah.get_units(5);
  weightSeshat = scaleSeshat.get_units(5);
  weightThoth  = scaleThoth.get_units(5);
}

void setup() {
  HX711 scales [4] = {scaleBes, scalePtah, scaleSeshat, scaleThoth};

  Serial.begin(38400);

  Serial.print("Initializing the buttons and lights...");
  pinMode(weighButtonPin, INPUT_PULLUP);
  pinMode(maglockPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  //TO DO: Delete this initializiation when no longer testing.
  pinMode(ledPin, OUTPUT);

  Serial.print("Initializing the scales...");
  // Parameter 'gain' omitted from the invocations;
  // default value 128 is used by the HX711 library.

  // Pins for scaleBes:
  // HX711.DOUT  - pin #A0
  // HX711.PD_SK - pin #A1
  scaleBes.begin(A0, A1);

  // Pins for scalePtah:
  // HX711.DOUT  - pin #A3
  // HX711.PD_SK - pin #A4
  scalePtah.begin(A3, A4);

  // Pins for scaleSeshat:
  // HX711.DOUT  - pin #A6
  // HX711.PD_SK - pin #A7
  scaleSeshat.begin(A6, A7);

  // Pins for scaleThoth:
  // HX711.DOUT  - pin #A9
  // HX711.PD_SK - pin #A10
  scaleThoth.begin(A9, A10);

  // Calibrate scaleBes only.
  // After the gain has been confirmed, we can calibrate the other scales.
  // Because the game requires relative weights only,
  // we only need to calibrate the scales once.
  // TODO: Replace the rest of setup() with --
  //    scaleBes.set_scale(gain.f);
  //    scaleBes.tare();
  //    scalePtah.set_scale(gain.f);
  //    scalePtah.tare();
  //    scaleSeshat.set_scale(gain.f);
  //    scaleSeshat.tare();
  //    scaleThoth.set_scale(gain.f);
  //    scaleThoth.tare();

  Serial.print("Setting up scaleBes...");
  Serial.print("read: \t\t");
  Serial.println(scaleBes.read());             // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scaleBes.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scaleBes.get_value(5));       // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scaleBes.get_units(5), 1);    // print the average of 5 readings from the ADC minus tare weight (not set) divided
                                               // by the SCALE parameter (not set yet)

  scaleBes.set_scale(2280.f);                  // this value is obtained by calibrating the scale with known weights; see the README for details
                                               // The value that is passed into `set_scale` will define the units for the output.
  scaleBes.tare();                             // reset the scale to 0

  Serial.println("Confirming setup of scaleBes:");

  Serial.print("read: \t\t");
  Serial.println(scaleBes.read());              // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scaleBes.read_average(20));    // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scaleBes.get_value(5));        // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scaleBes.get_units(5), 1);     // print the average of 5 readings from the ADC minus tare weight, divided
                                                // by the SCALE parameter set with set_scale
}

void loop() {
  weighButtonState = digitalRead(weighButtonPin);

  // TODO: "Activate" the actual code once we're no longer testing.

  if (weighButtonState == HIGH) {
    Serial.print("'Weigh' button has been pressed!");
    // weigh();
    // if (isCorrectlyPlaced()) {
    //   turn LED green:
    //   digitalWrite(greenLED, HIGH);
    //   digitalWrite(redLED, LOW);
    //   deactivate the maglock:
    //   digitalWrite(maglockPin, LOW);
    //   delay(5000);
    // } else {
    //   turn LED red:
    //   digitalWrite(redLED, HIGH);
    //   digitalWrite(greenLED, LOW);
    //   delay(1000);
    // }
    digitalWrite(ledPin, HIGH);
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW);
    // turn on LED ready light:
    // digitalWrite(redLED, HIGH);
    // digitalWrite(greenLED, HIGH);
    delay(1000);
  }
}
