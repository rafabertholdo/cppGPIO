#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>

enum class GPIODirection {
    input,
    output
};

/* GPIO 
 * Purpose: Each object instantiated from this class will control a GPIO pin 
 */
class GPIO
{
public:
    GPIO(const std::string& x, const GPIODirection direction);
    ~GPIO();
    GPIO(GPIO const&)            = delete;
    void operator=(GPIO const&)  = delete;

    const std::string& GPIONum();
    const GPIODirection& direction();

    void setValue(const bool& value);
    const bool getValue();
    const bool& isStreamGood();
private:
    std::string m_GPIONum;
    GPIODirection m_direction;
    bool m_streamGood;

    void setInputDirection();
    void setOutputDirection();
    void setDirection(const std::string& dir);
    void exportGPIO();
    void unexportGPIO();
    const std::string readFile(const std::string& path);
    const void writeFile(const std::string& path, const std::string& value);
};

#endif