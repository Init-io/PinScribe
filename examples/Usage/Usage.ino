#include <PinScribe.h>

PinScribe pinScribe;

// Pin Definitions
const int buttonPin = 2;
const int ledPin = 13;
const int analogPin = A0;

void setup() {
  // Initialize pin modes
  pinScribe.add(buttonPin, "input");   // Set buttonPin as input
  pinScribe.add(ledPin, "output");     // Set ledPin as output

  // Initialize serial communication
  Serial.begin(9600);
  
  // Save initial states
  pinScribe.saveState(ledPin);
}

void loop() {
  // Example 1: Toggle LED on button press
  pinScribe.onPress(buttonPin, []() {
    Serial.println("Button Pressed");
    pinScribe.toggle(ledPin);  // Toggle LED state
  });

  // Example 2: Long press on the button triggers an action
  pinScribe.onLongPress(buttonPin, []() {
    Serial.println("Long Press Detected!");
    pinScribe.blink(ledPin, 500, 500); // Blink LED on long press
  });

  // Example 3: Double press on the button
  pinScribe.onDoublePress(buttonPin, []() {
    Serial.println("Double Press Detected!");
    pinScribe.set(ledPin, HIGH);  // Turn on LED
    delay(500);
    pinScribe.set(ledPin, LOW);   // Turn off LED
  });

  // Example 4: Debouncing the button
  bool stableState = pinScribe.debounce(buttonPin, 50); // Debounce with 50ms interval
  if (stableState == LOW) {
    Serial.println("Stable Button State: LOW");
  } else {
    Serial.println("Stable Button State: HIGH");
  }

  // Example 5: Analog read (if connected to an analog sensor)
  int analogValue = pinScribe.analogRead(analogPin);  // Read analog value from pin A0
  Serial.print("Analog Value: ");
  Serial.println(analogValue);

  // Example 6: Analog Write (PWM to control LED brightness)
  int pwmValue = map(analogValue, 0, 1023, 0, 255);  // Map analog value to PWM range
  pinScribe.analogWrite(ledPin, pwmValue);  // Write PWM value to LED pin

  // Example 7: Save and Restore Pin State
  if (analogValue > 512) { // For example, turn on LED if the analog value is greater than half
    pinScribe.set(ledPin, HIGH);
  } else {
    pinScribe.restoreState(ledPin); // Restore the LED state to the saved state
  }

  // Example 8: Blink LED with specified on and off times
  pinScribe.blink(ledPin, 300, 300); // Blink the LED with a 300ms on/off period

  // Delay to prevent flooding serial output
  delay(100);
}


//Explanation of All Methods in the Example:

// 1. **`add(int pin, String type)`**
//- Adds a pin to the `PinScribe` library and sets its mode (`input` or `output`).
//- **Example**: `pinScribe.add(buttonPin, "input");`

// 2. **`set(int pin, int state)`**
//- Sets the state of a pin (either `HIGH` or `LOW`).
//- **Example**: `pinScribe.set(ledPin, HIGH);`

// 3. **`get(int pin)`**
//- Gets the current state of a pin (`HIGH` or `LOW`).
  // - **Example**: `int state = pinScribe.get(buttonPin);`

// 4. **`analogRead(int pin)`**
  // - Reads the analog value from the specified pin (0 to 1023).
 //  - **Example**: `int analogValue = pinScribe.analogRead(analogPin);`

// 5. **`analogWrite(int pin, int value)`**
  // - Writes a PWM value (0 to 255) to a pin. This is used to control the brightness of LEDs.
 //  - **Example**: `pinScribe.analogWrite(ledPin, pwmValue);`

// 6. **`toggle(int pin)`**
  // - Toggles the state of a digital pin (from `HIGH` to `LOW`, or `LOW` to `HIGH`).
   //- **Example**: `pinScribe.toggle(ledPin);`

// 7. **`blink(int pin, int onTime, int offTime)`**
  //- Blinks an LED (or any digital device) with specified on and off durations.
  // - **Example**: `pinScribe.blink(ledPin, 500, 500);`

// 8. **`debounce(int pin, unsigned long interval)`**
 // - Debounces a digital input to ensure stable state readings. Returns the stable state after the debounce time has passed.
  // - **Example**: `bool stableState = pinScribe.debounce(buttonPin, 50);`

// 9. **`onPress(int pin, std::function<void()> callback)`**
  // - Registers a callback to be called when the pin is pressed (in the `LOW` state).
 //  - **Example**: 
 //    ```cpp
 //    pinScribe.onPress(buttonPin, []() {
  //     pinScribe.toggle(ledPin);
 //    });
  //   ```

// 10. **`onRelease(int pin, std::function<void()> callback)`**
 //  - Registers a callback to be called when the pin is released (in the `HIGH` state).
  // - **Example**:
  //   ```cpp
 //    pinScribe.onRelease(buttonPin, []() {
 //      Serial.println("Button Released");
 //    });
 //    ```

// 11. **`onDoublePress(int pin, std::function<void()> callback, unsigned long timeout = 500)`**
  // - Registers a callback to be called when the pin is pressed twice within a given timeout (default 500ms).
  // - **Example**: 
  //   ```cpp
  //   pinScribe.onDoublePress(buttonPin, []() {
   //    pinScribe.set(ledPin, HIGH);
  //   });
   //  ```

// 12. **`onLongPress(int pin, std::function<void()> callback, unsigned long duration = 3000)`**
 //  - Registers a callback to be called when the pin is pressed for a long duration (default 3000ms).
  // - **Example**: 
  //   ```cpp
  //   pinScribe.onLongPress(buttonPin, []() {
  //     pinScribe.blink(ledPin, 500, 500);
  //   });
  //   ```

// 13. **`saveState(int pin)`**
  // - Saves the current state (either `HIGH` or `LOW`) of the pin, so it can be restored later.
 //  - **Example**: `pinScribe.saveState(ledPin);`

// 14. **`restoreState(int pin)`**
   //- Restores the pin to the state it was in when `saveState()` was called.
 //  - **Example**: `pinScribe.restoreState(ledPin);`

//

// Summary:

//This example demonstrates **all the methods** of the `PinScribe` library by interacting with a button and an LED:
//- **Button presses** trigger actions such as toggling, long press detection, and double press detection.
////- **Debouncing** ensures stable input readings.
//- **Analog input** and **PWM output** control LED brightness.
//- **Pin state saving and restoring** allows for flexible pin state management.

//This should give you a comprehensive understanding of how to use all the methods in the `PinScribe` library.