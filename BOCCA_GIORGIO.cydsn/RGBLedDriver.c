/**
*   \brief Source code for RGB Led Driver.
*/

#include "RGBLedDriver.h"

static void RGBLed_WriteRed(uint16 red);       // Write new red value
static void RGBLed_WriteGreen(uint16 green);   // Write new green value
static void RGBLed_WriteBlu(uint16 blue);       // Write new blu value

void RGBLed_Start(void)
{
    // Start PWM Components
    PWM_RG_Start(); // Start PWM connected to red and green channels
    PWM_B_Start();  // Start PWM connected to blu channel
}

void RGBLed_Stop(void)
{
    // Stop PWM Components
    PWM_RG_Stop(); // Stop PWM connected to red and green channels
    PWM_B_Stop();  // Stop PWM connected to blu channel
}

void RGBLed_WriteColor(Color c)
{
    RGBLed_WriteRed(c.red);
    RGBLed_WriteGreen(c.green);
    RGBLed_WriteBlu(c.blu);
}

static void RGBLed_WriteRed(uint16 red)
{
    PWM_RG_WriteCompare1(red);
}

static void RGBLed_WriteGreen(uint16 green)
{
    PWM_RG_WriteCompare2(green);
}

static void RGBLed_WriteBlu(uint16 blu)
{
    PWM_B_WriteCompare(blu);
}
/* [] END OF FILE */
