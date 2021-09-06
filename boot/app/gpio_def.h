#ifndef __GPIO_DEF_H__
#define __GPIO_DEF_H__

/* inputs: */
/* buttons: left, right, up, down, select */
#define PIN_BIT_BUT_U 3
#define PIN_PORT_BUT_U MDR_PORTD

#define PIN_BIT_BUT_D 4
#define PIN_PORT_BUT_D MDR_PORTD

#define PIN_BIT_BUT_L 5
#define PIN_PORT_BUT_L MDR_PORTD

#define PIN_BIT_BUT_R 6
#define PIN_PORT_BUT_R MDR_PORTD

#define PIN_BIT_BUT_S 2
#define PIN_PORT_BUT_S MDR_PORTD

/* outputs: */
#define PIN_BIT_LED0 9
#define PIN_PORT_LED0 MDR_PORTA

#define PIN_BIT_LED1 13
#define PIN_PORT_LED1 MDR_PORTA

#define PIN_BIT_LED2 8
#define PIN_PORT_LED2 MDR_PORTC

#define PIN_BIT_LED3 9
#define PIN_PORT_LED3 MDR_PORTC

#define PIN_BIT_LED4 0
#define PIN_PORT_LED4 MDR_PORTD

#define PIN_BIT_LED5 7
#define PIN_PORT_LED5 MDR_PORTD

#define PIN_BIT_LED6 12
#define PIN_PORT_LED6 MDR_PORTD

#define PIN_BIT_LED7 0
#define PIN_PORT_LED7 MDR_PORTB

/* IO macro */
#define PIN_READ(PIN_PORT, PIN_BIT) ((PIN_PORT->RXTX & (1 << PIN_BIT)) ? 1 : 0)
#define PIN_SET_HI(PIN_PORT, PIN_BIT) (PIN_PORT->RXTX |= (1 << PIN_BIT))
#define PIN_SET_LO(PIN_PORT, PIN_BIT) (PIN_PORT->CLRTX = (1 << PIN_BIT))
#define PIN_SET_TGL(PIN_PORT, PIN_BIT) ((PIN_PORT->RXTX & (1 << PIN_BIT))   \
                                            ? PIN_SET_LO(PIN_PORT, PIN_BIT) \
                                            : PIN_SET_HI(PIN_PORT, PIN_BIT))

/* user IO */
#define GET_PIN(pin) PIN_READ(PIN_PORT_##pin, PIN_BIT_##pin)
#define SET_PIN(pin) PIN_SET_HI(PIN_PORT_##pin, PIN_BIT_##pin)
#define RST_PIN(pin) PIN_SET_LO(PIN_PORT_##pin, PIN_BIT_##pin)
#define TGL_PIN(pin) PIN_SET_TGL(PIN_PORT_##pin, PIN_BIT_##pin)

// index: 0..7
#define SET_LED(index) PIN_SET_HI(PIN_PORT_LED##index, PIN_BIT_LED##index)
#define RST_LED(index) PIN_SET_LO(PIN_PORT_LED##index, PIN_BIT_LED##index)
#define TGL_LED(index) PIN_SET_TGL(PIN_PORT_LED##index, PIN_BIT_LED##index)

/*
* Configure pin as input, set hight level:
* FUNC = port
* OE = in
* ANALOG = 1 (digital)
* PWR = max fast
*/
#define PIN_CONFIG_IN(PIN_PORT, PIN_BIT)                                      \
    do                                                                        \
    {                                                                         \
        PIN_PORT->FUNC &= ~((1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1))); \
        PIN_PORT->OE &= ~(1 << PIN_BIT);                                      \
        PIN_PORT->ANALOG |= (1 << PIN_BIT);                                   \
        PIN_PORT->PWR |= (1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1));     \
    } while (0)

#define CONFIG_IN(pin) PIN_CONFIG_IN(PIN_PORT_##pin, PIN_BIT_##pin)

/*
* Configure pin as output, set hight level:
* FUNC = port
* OE = out
* ANALOG = 1 (digital)
* RXTX = 1
* PWR = max fast
*/
#define PIN_CONFIG_OUT_HI(PIN_PORT, PIN_BIT)                                  \
    do                                                                        \
    {                                                                         \
        PIN_PORT->FUNC &= ~((1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1))); \
        PIN_PORT->OE |= (1 << PIN_BIT);                                       \
        PIN_PORT->ANALOG |= (1 << PIN_BIT);                                   \
        PIN_PORT->RXTX |= (1 << PIN_BIT);                                     \
        PIN_PORT->PWR |= (1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1));     \
    } while (0)

#define CONFIG_OUT_HI(pin) PIN_CONFIG_OUT_HI(PIN_PORT_##pin, PIN_BIT_##pin)
/*
* Configure pin as output, set low level:
* FUNC = port
* OE = out
* ANALOG = 1 (digital)
* RXTX = 0
* PWR = max fast
*/
#define PIN_CONFIG_OUT_LO(PIN_PORT, PIN_BIT)                                  \
    do                                                                        \
    {                                                                         \
        PIN_PORT->FUNC &= ~((1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1))); \
        PIN_PORT->OE |= (1 << PIN_BIT);                                       \
        PIN_PORT->ANALOG |= (1 << PIN_BIT);                                   \
        PIN_PORT->RXTX &= ~(1 << PIN_BIT);                                    \
        PIN_PORT->PWR |= (1 << (PIN_BIT * 2)) | (1 << (PIN_BIT * 2 + 1));     \
    } while (0)

#define CONFIG_OUT_LO(pin) PIN_CONFIG_OUT_LO(PIN_PORT_##pin, PIN_BIT_##pin)

#endif // __GPIO_DEF_H__
