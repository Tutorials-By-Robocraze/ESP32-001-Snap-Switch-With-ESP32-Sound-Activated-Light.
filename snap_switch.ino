// Define the pins connected to the sound sensor and the LED
const int ANALOG_PIN = A0;  // GPIO 36 (A0) for Analog Output
const int LED_PIN = 2;     // GPIO 27 for the LED

// Define the threshold for sound detection
const int SOUND_THRESHOLD = 1;

// Variables to manage the LED state and detect a rising edge event
bool ledState = false;           // Tracks the current state of the LED (false = OFF, true = ON)
bool wasAboveThreshold = false;  // Flag to detect when the sound level crosses the threshold

void setup() {
  // Initialize Serial Communication for debugging
  Serial.begin(115200);
  Serial.println("\nSound Sensor Toggle Control Initialized...");
  Serial.println("------------------------------------");

  // Set the LED pin as an output and initialize it to LOW (off)
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the value from the Analog Output pin.
  int analogValue = analogRead(ANALOG_PIN);

  // Print the current analog value for diagnostics
  Serial.print("Analog Value (Intensity): ");
  Serial.println(analogValue);

  // Check if the sound intensity is above the threshold
  if (analogValue > SOUND_THRESHOLD) {
    // If the sound is above the threshold and it was NOT above the threshold
    // in the previous loop cycle, this is a "rising edge" event.
    if (!wasAboveThreshold) {
      // Invert the LED's state
      ledState = !ledState;

      // Update the LED to the new state
      digitalWrite(LED_PIN, ledState);

      // Print a message to the Serial Monitor
      if (ledState) {
        Serial.println("Threshold met! LED is now ON.");
      } else {
        Serial.println("Threshold met again! LED is now OFF.");
      }

      // Set the flag to true to prevent the toggle from happening
      // repeatedly while the sound is still above the threshold.
      wasAboveThreshold = true;
    }
  } else {
    // If the sound is below the threshold, reset the flag.
    // This allows the toggle to happen again the next time the threshold is met.
    wasAboveThreshold = false;
  }

  // Wait for a short moment before the next reading
  delay(500);
}