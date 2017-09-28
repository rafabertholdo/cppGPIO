#include <iostream>
#include <chrono>
#include <thread>
#include "GPIO.h"

using namespace std;

int main (void) {
    bool inputstate;

    GPIO gpio18("18", GPIODirection::output);
    GPIO gpio17("17", GPIODirection::input);

    int hitCount =0;
    int maxHitCount = 0;

    cout << "How many button presses: ";
    cin >> maxHitCount;

    if (gpio18.isStreamGood() && gpio17.isStreamGood()) {
        bool oldButtonState = 0;
        while (hitCount < maxHitCount) {
            bool buttonState = gpio17.getValue();
            if (oldButtonState != buttonState && oldButtonState) {
                hitCount++;
            }
            gpio18.setValue(buttonState);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            oldButtonState = buttonState;
        }
    } else {
        cout << "Cannot initialize streams....." << endl;
    }

    cout << "Exiting....." << endl;
    return 0;
}
