#pragma once
#include <cstring>
#include <string>
#include <atomic>
#include <thread>
#include <SDL.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#undef main // Necessary for SDL libs.
#endif



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
         * @return number of joystics in OS.
         */
        int init();

        /**
         * @brief Method to open joystick.
         * @param joystickId ID of joystick (from 0 to number-1).
         * @return true if joystic open.
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

    private:

        SDL_Joystick* m_joystick;
        std::atomic<bool> m_buttons[256];
        std::atomic<int> m_axes[256];
        std::atomic<int> m_hatValue;
        std::thread m_joysticThread;
        std::atomic<bool> m_stopThreadsFlag;

        void joystickEventsThreadFunction();
    };
}
}
