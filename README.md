***
![JOYSTIC](_static/jcontroller_logo_with_borders.png)
***
## 
## OVERVIEW
C++ library **JoystickController** version **2.0ю0** is designed to help developers work with joysticks. The library is cross-platform and uses the **SDL v2** library. The library is cross-platform and uses the **SDL v2** library. The library works only with HID compatible joysticks.
the library provides:
* Checking the availability of joysticks in the system.
* Initializing the selected joystick.
* Geting information about the joystick (name, number of axes and buttons, etc.).
* Getting the state of buttons, axis positions and more.

The library contains a description of just one class **JoystickController** with simple interface for easy use:
```c++
namespace cr
{
namespace joystick
{
    /**
     * @brief Class to work with joystick.
     */
    class JoystickController
    {
    public:

        /**
         * @brief Get library version.
         * @return String of library version in "2.0.0" format.
         */
        static std::string getVersion();

        /**
         * @brief Construct a new Joystick Controller object.
         */
        JoystickController();

        /**
         * @brief Destroy the Joystick Controller object.
         */
        ~JoystickController();

        /**
         * @brief Init library.
         * @return number of joysticks in OS.
         */
        int init();

        /**
         * @brief Method to open joystick.
         * @param joystickId ID of joystick (from 0 to number-1).
         * @return true if joystick open.
         * @return false if joystick not open.
         */
        bool open(int joystickId);

        /**
         * @brief Close joystick.
         */
        void close();

        /**
         * @brief Get the Name of joystick.
         * @return name of joystick or empty string if joystick not open.
         */
        std::string getName();

        /**
         * @brief Get number of buttons in joystick.
         * @return number of buttons or -1 string if joystick not open.
         */
        int getNumButtons();

        /**
         * @brief Get number of axes in joystick.
         * @return number of axes or -1 string if joystick not open.
         */
        int getNumAxes();

        /**
         * @brief Get number of huts in joystick.
         * @return number of huts or -1 string if joystick not open.
         */
        int getNumHats();

        /**
         * @brief Get button state (pushed ot not pushed).
         * @param buttonId ID of button.
         * @param resetButton Flag to reset button state if you want.
         * @return true if the button pushed.
         * @return false if the button released.
         */
        bool getButtonState(int buttonId, bool resetButton = false);

        /**
         * @brief Get the Hut Value.
         * @return hut value ot -1 if joystick not open.
         */
        int getHatValue();

        /**
         * @brief Get the Axis Value object
         * @param axis_ID ID of axis.
         * @return value of axis.
         */
        int getAxisValue(int axisId);
    };
}
}
```
***

## 
## LIBRARY INITIALIZATION
To initialize the library we use the method **init()**. The method returns the number of available joysticks in the system. The method initializes the **SDL** library.
```c++
/**
 * @brief Init library.
 * @return number of joysticks in OS.
 */
int init();
```
***
## OPENING THE JOYSTICK
To open the joystick you need to call the **open()** method. This method opens joystick according to joystick_ID (joystick number). The number of the joystick is its serial number. The number of joysticks in the system can be obtained using the method **init()**.
```c++
/**
 * @brief Init library.
 * @return number of joysticks in OS.
 */
int init();
```
The joystick will close automatically when the program ends. In order to close the joystick independently you need to use the method **close()**. When the **open()** method is called again, the joystick will be closed and reopened (the same joystick or another joystick according to its joystick_ID).
***
## GETTING JOYSTICK INFORMATION
If the joystick is open (after calling the **open()** method), you can get its name using the method **getName()**, the number of available buttons on the joystick using the method **getNumButtons()**, the number of available axes using the method **getNumAxes()** and the number of available switches using the method **getNumHats()**.
***
## GETTING THE STATE OF THE BUTTONS
To get the state of the button the method **getButtonState()**. The button can be found either in the "pressed" state or in the "free" state. The method takes the ID of the button (from 0 to number_of_buttons - 1). If the button is pressed, the method returns **TRUE**. If the button is not pressed, the method returns **FALSE**. The method also takes the **resetButton** parameter. If **resetButton == true** the state of button inside the library will be switched to "free".
```c++
/**
 * @brief Get button state (pushed ot not pushed).
 * @param buttonId ID of button.
 * @param resetButton Flag to reset button state if you want.
 * @return true if the button pushed.
 * @return false if the button released.
 */
bool getButtonState(int buttonId, bool resetButton = false);
```
***
## GETTING AXIS VALUE
To get the value of the axis the method **getAxisValue()**. The method takes ID of axis as parameter and return current value of axis.
```c++
/**
 * @brief Get the Axis Value object
 * @param axis_ID ID of axis.
 * @return value of axis.
 */
int getAxisValue(int axisId);
```
***
## GETTING SWITCH (HAT) VALUE
To get the value of the switch the method **getHatValue()**. The method returns current hat value.
```c++
/**
 * @brief Get the Hut Value.
 * @return hut value ot -1 if joystick not open.
 */
int getHatValue();
```
***
## SIMPLE EXAMPLE
The example application shows how to work with the library. The application receives the current values of the axes and buttons of the joystick and outputs them to the console.
```c++
#include <iostream>
#include <chrono>
#include <ctime>
#include <JoystickController.h>

using namespace cr::joystick;


// Entry point.
int main(void)
{
    std::cout << "Joystick Controller v" <<
                 JoystickController::getVersion() <<
                 " test application" << std::endl;

    // Create joystick controller object.
    JoystickController joystickController;

    // Get number of joysticks.
    int numJoysticks = joystickController.init();

    // Check number of joysticks.
    if (numJoysticks <= 0)
    {
        std::cout << "No available joysticks. Exit..." << std::endl;
        return -1;
    }
    std::cout << "Number of joysticks: " << numJoysticks <<
                 std::endl << std::endl;

    // Dialog to enter joystick ID to open.
    int joystickId = 0;
    std::cout << "Enter joystick ID (from 0 to " <<
                 (numJoysticks - 1) << "): ";
    std::cin >> joystickId;

    // Open joystick.
    if (!joystickController.open(joystickId))
    {
        std::cout << "Joystic not open. Exit..." << std::endl;
        return -1;
    }

    // Get joystick info.
    std::string joystickName = joystickController.getName();
    int numButtons = joystickController.getNumButtons();
    int numAxes = joystickController.getNumAxes();
    int numHats = joystickController.getNumHats();

    // Show joystick info.
    std::cout << "Joystick open. Name: " << joystickName <<
                 " Buttons: " << numButtons <<
                 " Axes: " << numAxes <<
                 " Huts: " << numHats << std::endl << std::endl;

    // Main loop.
    while (true)
    {
        // Prepare joystick info.
        std::string joystickInfo = "Axes: ";
        for (int i = 0; i < numAxes; ++i)
            joystickInfo = joystickInfo +
                    std::to_string(joystickController.getAxisValue(i)) + ":";
        joystickInfo = joystickInfo + " hat value: " +
                std::to_string(joystickController.getHatValue());
        joystickInfo = joystickInfo + " buttons: ";
        for (int i = 0; i < numButtons; ++i)
            joystickInfo = joystickInfo +
                    (joystickController.getButtonState(i) ? "X " : "_ ");

        // Show joystic info.
        std::cout << joystickInfo << std::endl;

        // Wait.
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 1;
}
```