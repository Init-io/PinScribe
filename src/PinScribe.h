#ifndef PINSCRIBE_H
#define PINSCRIBE_H

#include <Arduino.h>
#include <functional>  // For using std::function with callbacks

class PinScribe  {
private:
    int pinStates[16];                  // Store pin states (HIGH/LOW)
    int savedStates[16];                // Save pin states for restoration
    unsigned long lastDebounceTimes[16]; // Last debounce times
    bool lastStates[16];                // Last known states for debouncing
    unsigned long lastPressTimes[16];   // For double press detection
    unsigned long pressStartTimes[16];  // For long press detection
    bool longPressTriggered[16];        // Track if a long press callback has been triggered

public:
    PinScribe ();

    void add(int pin, String type);                // Add a pin
    void set(int pin, int state);                  // Set a pin state
    int get(int pin);                              // Get a digital pin state
    int analogRead(int pin);                       // Read analog pin value
    void analogWrite(int pin, int value);          // Write PWM value to a pin
    void toggle(int pin);                          // Toggle a pin's state
    void blink(int pin, int onTime, int offTime);  // Blink an LED
    bool debounce(int pin, unsigned long interval); // Debounce an input
    void onPress(int pin, std::function<void()> callback);  // Button press
    void onRelease(int pin, std::function<void()> callback); // Button release
    void onDoublePress(int pin, std::function<void()> callback, unsigned long timeout = 500); // Double press
    void onLongPress(int pin, std::function<void()> callback, unsigned long duration = 3000); // Long press
    void saveState(int pin);                       // Save a pin's state
    void restoreState(int pin);                    // Restore a pin's state
};

#endif
