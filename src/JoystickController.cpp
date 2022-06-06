#include "JoystickController.h"
#include "JoystickControllerVersion.h"



std::string cr::joystick::JoystickController::getVersion()
{
    return JOYSTICK_CONTROLLER_VERSION;
}



cr::joystick::JoystickController::JoystickController() :
    m_joystick(nullptr)
{
    m_stopThreadsFlag.store(true);

    // Init buttons flags.
    for (int i = 0; i < 256; ++i)
        m_buttons[i].store(false);

    // Init axes value.
    for (int i = 0; i < 256; ++i)
        m_axes[i].store(false);

    // Init hut value.
    m_hatValue.store(-1);
}



cr::joystick::JoystickController::~JoystickController()
{
    // Stop thread.
    m_stopThreadsFlag.store(true);
    if (m_joysticThread.joinable())
        m_joysticThread.join();

    // Close joystick.
    if (m_joystick != nullptr)
        SDL_JoystickClose(m_joystick);
}



int cr::joystick::JoystickController::init()
{
    // Init SDL2 library.
    SDL_Init(SDL_INIT_JOYSTICK);

    // Get number of joystic.
    return SDL_NumJoysticks();
}



bool cr::joystick::JoystickController::open(int joystickId)
{
    // Stop thread.
    m_stopThreadsFlag.store(true);
    if (m_joysticThread.joinable())
        m_joysticThread.join();

    // Close joystick before.
    if (m_joystick != nullptr)
        SDL_JoystickClose(m_joystick);
    m_joystick = nullptr;

    // Open joystick.
    m_joystick = SDL_JoystickOpen(joystickId);
    if (m_joystick == NULL)
    {
        m_joystick = nullptr;
        return false;
    }

    // Launch event read thread.
    m_stopThreadsFlag.store(false);
    m_joysticThread = std::thread(
                &cr::joystick::JoystickController::joystickEventsThreadFunction,
                this);

    return true;
}



void cr::joystick::JoystickController::close()
{
    // Stop thread.
    m_stopThreadsFlag.store(true);
    if (m_joysticThread.joinable())
        m_joysticThread.join();

    // Close joystick.
    if (m_joystick != nullptr)
        SDL_JoystickClose(m_joystick);
    m_joystick = nullptr;
}



std::string cr::joystick::JoystickController::getName()
{
    // Check if joystic not open.
    if (m_joystick == nullptr)
        return "";

    // Return name.
    return std::string(SDL_JoystickName(m_joystick));
}



int cr::joystick::JoystickController::getNumButtons()
{
    // Check if joystic not open.
    if (m_joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumButtons(m_joystick);
}



int cr::joystick::JoystickController::getNumAxes()
{
    // Check if joystic not open.
    if (m_joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumAxes(m_joystick);
}



int cr::joystick::JoystickController::getNumHats()
{
    // Check if joystic not open.
    if (m_joystick == nullptr)
        return -1;

    // Return number of buttons.
    return SDL_JoystickNumHats(m_joystick);
}



bool cr::joystick::JoystickController::getButtonState(int buttonId,
                                                      bool resetButton)
{
    // Check buttob ID.
    if (buttonId >= 256 || buttonId < 0)
        return false;

    bool state = m_buttons[buttonId].load();
    if (resetButton)
        m_buttons[buttonId].store(false);

    // Return button state.
    return state;
}



int cr::joystick::JoystickController::getHatValue()
{
    // Return hut value.
    return m_hatValue.load();
}



int cr::joystick::JoystickController::getAxisValue(int axisId)
{
    // Check axis ID.
    if (axisId >= 256 || axisId < 0)
        return -1;

    // Return axis value.
    return m_axes[axisId].load();
}



void cr::joystick::JoystickController::joystickEventsThreadFunction()
{
    const uint32_t waitTime = 10; // Wait time 10 ms.

    while (!m_stopThreadsFlag.load())
    {
        SDL_Event evt;
        if (SDL_PollEvent(&evt) != 0) {
            // Chenge value of joystick variables.
            switch (evt.type)
            {
                case SDL_JOYAXISMOTION:
                    m_axes[evt.jaxis.axis].store((int)evt.jaxis.value);
                    break;

                case SDL_JOYBUTTONDOWN:
                    m_buttons[evt.jbutton.button].store(true);
                    break;

                case SDL_JOYBUTTONUP:
                    m_buttons[evt.jbutton.button].store(false);
                    break;

                case SDL_JOYHATMOTION:
                    m_hatValue.store((int)evt.jhat.value);
                    break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
}



















