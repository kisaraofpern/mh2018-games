#include <HX711.h>

// This is the order of the scales from left to right.
HX711 scaleSeshat; //scale #1
HX711 scaleBes;    //scale #2
HX711 scaleThoth;  //scale #3
HX711 scalePtah;   //scale #4

float weightBes;
float weightPtah;
float weightSeshat;
float weightThoth;
const float totalWeightExpected = 750; // grams
const float weightThreshold = 0.1;

// Mathematical constants
const int period = 32000;
const float pi = 3.14159;

// Pin assignments for scales
const byte scaleSeshatDOUT  = A0;  // data1
const byte scaleSeshatPD_SK = A1;  // clock1

const byte scaleBesDOUT     = A2;  // data2
const byte scaleBesPD_SK    = A3;  // clock2

const byte scaleThothDOUT   = A4;  // data3
const byte scaleThothPD_SK  = A5;  // clock3

const byte scalePtahDOUT    = A6;  // data4
const byte scalePtahPD_SK   = A7;  // clock4

// Pin assignments for other items
const int weighButtonPin = 45;
const int maglockPin     = 35;
const int redLED         = 10;
const int greenLED       = 9;
const int blueLED        = 8;

int weighButtonState = 0;
int brightness = 0;
int fadeAmount = 5;
float cycleCount = 0;

// Function definitions
// Check if the weights have been correctly placed.
bool isCorrectlyPlaced() {
  Serial.println("Judging the things.");
  if( (weightBes < weightThreshold)    || 
      (weightSeshat < weightThreshold) || 
      (weightPtah < weightThreshold)   ||
      (weightThoth < weightThreshold)) {
    return false;
  }
  return weightBes < weightSeshat && weightSeshat < weightPtah && weightPtah < weightThoth;
}

bool isValidTotalWeight() {
  const float weightTolerance = .1; // 10%
  const float totalWeight = weightBes + weightPtah + weightSeshat + weightThoth;
  return (totalWeight >= totalWeightExpected*(1-weightTolerance)) && (totalWeight <= totalWeightExpected*(1+weightTolerance));
}

// Get the weights from the scales.
void weigh() {
  Serial.println("Weighing the things");
  weightBes    = scaleBes.get_units(5);
  weightPtah   = scalePtah.get_units(5);
  weightSeshat = scaleSeshat.get_units(5);
  weightThoth  = scaleThoth.get_units(5);
}

void setup() {
  Serial.begin(38400);

  Serial.print("Initializing the buttons and lights...\n");
  pinMode(weighButtonPin, INPUT_PULLUP);
  pinMode(maglockPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  digitalWrite(maglockPin, LOW);

  Serial.print("Initializing the scales...\n");
  // Parameter 'gain' omitted from the invocations;
  // default value 128 is used by the HX711 library.

  scaleBes.begin(scaleBesDOUT, scaleBesPD_SK);
  scalePtah.begin(scalePtahDOUT, scalePtahPD_SK);
  scaleSeshat.begin(scaleSeshatDOUT, scaleSeshatPD_SK);
  scaleThoth.begin(scaleThothDOUT, scaleThothPD_SK);

  // set_scale() takes a float and uses it to convert the raw data to "human readable" data with units.
  scaleBes.set_scale(212.6260575296);
  scaleBes.tare();
  
  scalePtah.set_scale(209.350253807);
  scalePtah.tare();
  
  scaleSeshat.set_scale(210.441624365);
  scaleSeshat.tare();
  
  scaleThoth.set_scale(215.59390862944);
  scaleThoth.tare();

}

void loop() {
  weighButtonState = digitalRead(weighButtonPin);

  // Default state.
  analogWrite(greenLED, 70+64*sin((2*pi*cycleCount/period)));
  analogWrite(redLED, 132+122*sin((2*pi*cycleCount/period)));
  
  cycleCount++;
  if(cycleCount > period){
    cycleCount = 0;
  }
  
  if (weighButtonState == HIGH) {
    Serial.println("WEIGH button has been pressed.");
    // Once the WEIGH button has been pressed, judge the gifts.
    weigh();
    if (isCorrectlyPlaced() && isValidTotalWeight()) {
      Serial.println("Hooray.");
      // The weights have the correct relative weights.
      // Turn the LED green.
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);

      // Deactivate the magnetic lock.
      digitalWrite(maglockPin, HIGH);
      delay(5000);
    } else {
      Serial.println("Un-hooray.");
      // The gifts do not have the correct relative weights.
      // Turn the LED red.
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(5000);
    }
  }
}
