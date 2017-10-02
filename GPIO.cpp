#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "GPIO.h"

using namespace std;

GPIO::GPIO(const string& gnum, const GPIODirection direction) :
    m_GPIONum(gnum),
    m_direction(direction) {

    unexportGPIO();
    exportGPIO();

    if (direction == GPIODirection::input) {
        setInputDirection();
    } else {
        setOutputDirection();
    }
}

GPIO::~GPIO() {
    unexportGPIO();
}

const string& GPIO::GPIONum() {
    return m_GPIONum;
}

const GPIODirection& GPIO::direction() {
    return m_direction;
}

const bool& GPIO::isStreamGood() {
    return m_streamGood;
}

const std::string GPIO::readFile(const std::string& path) {
    ifstream stream(path.c_str());
    if (!stream) {
        m_streamGood = false;
        return "";
    }
    m_streamGood = true;
    string result;
    stream >> result;
    stream.close();
    return result;
}

const void GPIO::writeFile(const std::string& path, const string& value) {
    ofstream stream(path.c_str());
    if (!stream) {
        m_streamGood = false;
        return;
    }
    m_streamGood = true;
    stream << value;
    stream.close();
}

void GPIO::setInputDirection() {
    setDirection("in");
}

void GPIO::setOutputDirection() {
    setDirection("out");
}

void GPIO::exportGPIO() {
    writeFile("/sys/class/gpio/export", m_GPIONum);
}

void GPIO::unexportGPIO() {
    writeFile("/sys/class/gpio/unexport", m_GPIONum);
}

void GPIO::setDirection(const string& direction) {
    if (m_streamGood) {
        writeFile("/sys/class/gpio/gpio" + m_GPIONum + "/direction", direction);
    }
}

void GPIO::setValue(const bool value) {
    if (m_streamGood && m_direction == GPIODirection::output) {
        writeFile("/sys/class/gpio/gpio" + m_GPIONum + "/value", value ? "1" : "0");
    }
}

const bool GPIO::getValue() {
    if (m_streamGood) {
        string value = readFile("/sys/class/gpio/gpio" + m_GPIONum + "/value");
        return value != "0";
    } else {
        return false;
    }
}
