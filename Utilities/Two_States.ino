//------------------------------------------------------------------------------
// Two_States.ino
// File to show simply on how to switch states using State Machine Library.
// Style: State Machine
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <StateMachine.h>

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define STATE_DELAY 100

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------
StateMachine machine = StateMachine();

//------------------------------------------------------------------------------
// Functions Declaration
//------------------------------------------------------------------------------
void onState();
bool evOff();
void offState();
bool evOn();

//------------------------------------------------------------------------------
// Setup and Loop
//------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    // Definition of the state and the transitions.
    State *S1 = machine.addState(&onState);
    State *S2 = machine.addState(&offState);
    S1->addTransition(&evOff, S2);
    S2->addTransition(&evOn, S1);

    delay(1000);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    machine.run();
    delay(STATE_DELAY);
}

//------------------------------------------------------------------------------
// Functions Definition
//------------------------------------------------------------------------------
void onState()
{
    Serial.println("On State");
    if (machine.executeOnce)
    {
        Serial.println("Turn the LED On (Just 1x btw)...");
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

bool evOff()
{
    bool return_val = false;
    // Two seconds until off.
    const uint8_t on_interval = 20;
    static uint8_t counter_off = 0;
    if (++counter_off > on_interval)
    {
        counter_off = 0;
        return_val = true;
    }

    return return_val;
}

void offState()
{
    Serial.println("Off State");
    if (machine.executeOnce)
    {
        Serial.println("Turn the LED OFF (Just 1x btw)...");
        digitalWrite(LED_BUILTIN, LOW);
    }
}

bool evOn()
{
    bool return_val = false;
    // One seconds until on again.
    const uint8_t on_interval = 10;
    static uint8_t counter_on = 0;
    if (++counter_on > on_interval)
    {
        counter_on = 0;
        return_val = true;
    }

    return return_val;
}
