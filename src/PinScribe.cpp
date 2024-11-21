#include "PinScribe.h"

// Constructor
PinScribe::PinScribe() {
    for (int i = 0; i < 16; i++) {
        pinStates[i] = LOW;
        savedStates[i] = LOW;
        lastDebounceTimes[i] = 0;
        lastStates[i] = HIGH;  // Default to HIGH (button unpressed)
        lastPressTimes[i] = 0;
        pressStartTimes[i] = 0;
        longPressTriggered[i] = false;
    }
}

// Add a pin with its type
void PinScribe::add(int pin, String type) {
    if (type == "output") {
        pinMode(pin, OUTPUT);
        pinStates[pin] = LOW; // Default state
    } else if (type == "input") {
        pinMode(pin, INPUT_PULLUP);
    }
}

// Set a digital state
void PinScribe::set(int pin, int state) {
    digitalWrite(pin, state);
    pinStates[pin] = state;
}

// Get a digital state
int PinScribe::get(int pin) {
    return digitalRead(pin);
}

// Read an analog value
int PinScribe::analogRead(int pin) {
    return ::analogRead(pin);
}

// Write a PWM value
void PinScribe::analogWrite(int pin, int value) {
    ::analogWrite(pin, value);
}

// Toggle a pin's state
void PinScribe::toggle(int pin) {
    set(pin, !pinStates[pin]);
}

// Blink an LED
void PinScribe::blink(int pin, int onTime, int offTime) {
    set(pin, HIGH);
    delay(onTime);
    set(pin, LOW);
    delay(offTime);
}

// Debounce an input
bool PinScribe::debounce(int pin, unsigned long interval) {
    bool current = digitalRead(pin);

    if (current != lastStates[pin]) {
        lastDebounceTimes[pin] = millis(); // Reset debounce timer
    }

    if (millis() - lastDebounceTimes[pin] > interval) {
        return current; // Return stable state
    }

    return lastStates[pin]; // Ignore unstable state
}


// Trigger a callback on button press
void PinScribe::onPress(int pin, std::function<void()> callback) {
    if (debounce(pin, 50) && get(pin) == LOW) {
        callback();
    }
}

// Trigger a callback on button release
void PinScribe::onRelease(int pin, std::function<void()> callback) {
    if (debounce(pin, 50) && get(pin) == HIGH) {
        callback();
    }
}

// Trigger a callback on double press
void PinScribe::onDoublePress(int pin, std::function<void()> callback, unsigned long timeout) {
    bool currentState = get(pin); // Current button state (HIGH/LOW)

    // Detect first press (LOW after HIGH)
    if (currentState == LOW && lastStates[pin] == HIGH) {
        unsigned long now = millis();

        // Check if it's a second press within the timeout
        if (now - lastPressTimes[pin] <= timeout) {
            callback(); // Trigger double press callback
            lastPressTimes[pin] = 0; // Reset after double press
        } else {
            // First press detected
            lastPressTimes[pin] = now;
        }
    }

    // Update last known state
    lastStates[pin] = currentState;
}




// Trigger a callback on long press
void PinScribe::onLongPress(int pin, std::function<void()> callback, unsigned long duration) {
    if (get(pin) == LOW) {
        if (!longPressTriggered[pin]) {
            if (pressStartTimes[pin] == 0) {
                pressStartTimes[pin] = millis(); // Start tracking press duration
            }
            if (millis() - pressStartTimes[pin] >= duration) {
                callback();
                longPressTriggered[pin] = true; // Mark long press as triggered
            }
        }
    } else {
        // Reset if button is released
        pressStartTimes[pin] = 0;
        longPressTriggered[pin] = false;
    }
}

// Save a pin's state
void PinScribe::saveState(int pin) {
    savedStates[pin] = pinStates[pin];
}

// Restore a pin's state
void PinScribe::restoreState(int pin) {
    set(pin, savedStates[pin]);
}
