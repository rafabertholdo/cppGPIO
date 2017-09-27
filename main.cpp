#include <iostream>
#include <chrono>
#include <thread>
#include "GPIO.h"

using namespace std;

int main (void) {
    bool inputstate;
    GPIO gpio4 = GPIO("4", GPIODirection::output);
    GPIO gpio17 = GPIO("17", GPIODirection::input);

    if (gpio4.isStreamGood() && gpio17.isStreamGood()) {
        while (1) {
            gpio4.setValue(gpio17.getValue());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } else {
        cout << "Cannot initialize streams....." << endl;
    }

    cout << "Exiting....." << endl;
    return 0;
}