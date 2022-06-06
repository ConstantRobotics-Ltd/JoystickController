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
