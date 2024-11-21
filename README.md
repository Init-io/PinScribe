# PinScribe Library

The **PinScribe** library provides an easy and flexible way to manage and interact with GPIO pins on an Arduino. It supports various features such as pin state management, debouncing, and handling input events like button presses, double presses, long presses, and more. The library also allows for saving and restoring pin states, making it useful for persistent pin configurations.

## Features

- **Pin Management**: Set, get, toggle, and blink digital pins, as well as read/write analog values.
- **Debouncing**: Handles input noise and ensures stable button press readings.
- **Event Handling**: Attach callbacks to pin events such as button presses, releases, double presses, and long presses.
- **State Preservation**: Save and restore pin states to maintain configurations across resets.
- **Supports Multiple Pin Types**: Works with both digital and analog pins.
  
## Installation

1. Download the `PinScribe` library as a ZIP file.
2. In the Arduino IDE, navigate to **Sketch > Include Library > Add .ZIP Library**.
3. Select the downloaded ZIP file to add the library to your Arduino IDE.
4. Once installed, you can include the library in your projects like this:

```cpp
#include <PinScribe.h>
```

## Example Usage

### Basic Pin Management

```cpp
#include <PinScribe.h>

PinScribe pinScribe;

void setup() {
    pinScribe.add(13, "output");  // Set pin 13 as an output pin
    pinScribe.add(2, "input");    // Set pin 2 as an input pin with pull-up resistor
}

void loop() {
    pinScribe.set(13, HIGH);      // Set pin 13 high (turn on an LED)
    delay(1000);
    pinScribe.set(13, LOW);       // Set pin 13 low (turn off LED)
    delay(1000);
}
```

### Button Press Events

```cpp
#include <PinScribe.h>

PinScribe pinScribe;

void setup() {
    pinScribe.add(2, "input");    // Set pin 2 as an input pin for the button
    pinScribe.add(13, "output");  // Set pin 13 as an output for LED

    // Setup button press event
    pinScribe.onPress(2, []() {
        Serial.println("Button Pressed");
        pinScribe.set(13, HIGH);  // Turn on LED
    });

    // Setup button release event
    pinScribe.onRelease(2, []() {
        Serial.println("Button Released");
        pinScribe.set(13, LOW);   // Turn off LED
    });
}

void loop() {
    // Handle other code here
}
```

### Long Press Detection

```cpp
#include <PinScribe.h>

PinScribe pinScribe;

void setup() {
    pinScribe.add(2, "input");    // Set pin 2 as an input for button
    pinScribe.add(13, "output");  // Set pin 13 as an output for LED

    // Trigger callback on long press
    pinScribe.onLongPress(2, []() {
        Serial.println("Long Press Detected");
        pinScribe.set(13, HIGH);  // Turn on LED after long press
    });
}

void loop() {
    // Continuously check long press
}
```

### Double Press Detection

```cpp
#include <PinScribe.h>

PinScribe pinScribe;

void setup() {
    pinScribe.add(2, "input");    // Set pin 2 as an input for the button
    pinScribe.add(13, "output");  // Set pin 13 as an output for LED

    // Setup double press event
    pinScribe.onDoublePress(2, []() {
        Serial.println("Double Press Detected");
        pinScribe.set(13, HIGH);  // Turn on LED on double press
    });
}

void loop() {
    // Continuously check for double press
}
```

## Functions

### `PinScribe::add(int pin, String type)`
- **pin**: The pin number (0-15).
- **type**: The type of pin. Options are `"input"` (with pull-up) or `"output"`.

### `PinScribe::set(int pin, int state)`
- **pin**: The pin number.
- **state**: The state of the pin (`HIGH` or `LOW`).

### `PinScribe::get(int pin)`
- **pin**: The pin number.
- **returns**: The current state of the pin (`HIGH` or `LOW`).

### `PinScribe::toggle(int pin)`
- Toggles the current state of the pin (from `HIGH` to `LOW`, or vice versa).

### `PinScribe::blink(int pin, int onTime, int offTime)`
- **pin**: The pin number.
- **onTime**: Duration in milliseconds for the pin to stay `HIGH`.
- **offTime**: Duration in milliseconds for the pin to stay `LOW`.

### `PinScribe::debounce(int pin, unsigned long interval)`
- **pin**: The pin number.
- **interval**: Debounce interval in milliseconds.
- **returns**: The stable pin state (`HIGH` or `LOW`).

### `PinScribe::onPress(int pin, std::function<void()> callback)`
- **pin**: The pin number.
- **callback**: The function to be called when the button is pressed.

### `PinScribe::onRelease(int pin, std::function<void()> callback)`
- **pin**: The pin number.
- **callback**: The function to be called when the button is released.

### `PinScribe::onDoublePress(int pin, std::function<void()> callback, unsigned long timeout)`
- **pin**: The pin number.
- **callback**: The function to be called on a double press.
- **timeout**: Time window (in milliseconds) within which the double press must occur (default: 500ms).

### `PinScribe::onLongPress(int pin, std::function<void()> callback, unsigned long duration)`
- **pin**: The pin number.
- **callback**: The function to be called when the button is held for a long press.
- **duration**: Duration (in milliseconds) for the long press (default: 3000ms).

### `PinScribe::saveState(int pin)`
- **pin**: The pin number.
- Saves the current state of the pin for later restoration.

### `PinScribe::restoreState(int pin)`
- **pin**: The pin number.
- Restores the pin to the previously saved state.

## Compatibility

- This library is compatible with any Arduino board.
- Requires Arduino IDE version 1.8 or higher.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to fork this repository and submit pull requests. If you encounter any bugs or have feature requests, please open an issue.

---

For any questions or issues, please open an issue on GitHub. Happy coding! 🚀
