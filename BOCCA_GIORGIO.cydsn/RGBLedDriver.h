/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _RGB_LED_DRIVER_H_
    #define _RGB_LED_DRIVER_H_
    
    #include "project.h"
    
    /**
    *   \brief Struct holding color data
    */
    typedef struct {
        uint16 red;    ///< Red value   0 - 255
        uint16 green;  ///< Green value 0 - 255
        uint16 blu;    ///< Blu value   0 - 255
    } Color;
        
    /**
    *   \brief Start RGB Led Driver.
    */
    void RGBLed_Start(void);
    
    /**
    *   \brief Stop RGB Led Driver.
    */
    void RGBLed_Stop(void);
    
    /**
    *   \brief Write new color value.
    */
    void RGBLed_WriteColor(Color c);
    
    
#endif

/* [] END OF FILE */
