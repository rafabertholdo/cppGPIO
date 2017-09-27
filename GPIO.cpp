#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "GPIO.h"

using namespace std;

GPIO::GPIO(const string& gnum, const GPIODirection direction) :
    m_GPIONum(gnum),
    m_direction(direction) {
    //cout << "constructor" << endl;
    unexportGPIO();
    exportGPIO();
    //cout << "GPIO exmported" << endl;
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
    //cout << "reading file " << path << endl;
    ifstream stream(path.c_str());
    if (!stream) {
        m_streamGood = false;
	//cout << "stream read failed" << endl;
        return "";
    }
    m_streamGood = true;
    string result;
    stream >> result;
    stream.close();
    return result;
}

const void GPIO::writeFile(const std::string& path, const string& value) {
    //cout << "writing file " << path << endl;
    ofstream stream(path.c_str());
    if (!stream) {
	//cout << "stream write failed" << endl;
        m_streamGood = false;
        return;
    }
    m_streamGood = true;
    stream << value;
    stream.close();
}

void GPIO::setInputDirection() {
    //cout << "input" << endl;
    setDirection("in");
}

void GPIO::setOutputDirection() {
    //cout << "output" << endl;
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
	//cout << "setting direction " << direction << " on GPIO " << m_GPIONum << endl;
        writeFile("/sys/class/gpio/gpio" + m_GPIONum + "/direction", direction);
	//cout << "direction set" << endl;
    }
}

void GPIO::setValue(const bool& value) {
    //cout << "before set value" << endl;
    if (m_streamGood && m_direction == GPIODirection::output) {
        //cout << "setting value " << (value ? "1" : "0") << " on GPIO " << m_GPIONum << endl;
        writeFile("/sys/class/gpio/gpio" + m_GPIONum + "/value", value ? "1" : "0");
    }// else {
      //   cout << "invalid set" << endl;
   // }
}

const bool GPIO::getValue() {
    if (m_streamGood && m_direction == GPIODirection::input) {
        string value = readFile("/sys/class/gpio/gpio" + m_GPIONum + "/value");
        return value != "0";
    } else {
        return false;
    }
}
