#include "debug.h"

/* Global define */
#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3
#define SW5 4

// #define A 0
// #define B 1
// #define C 2
// #define D 3
// #define E 4

#define LEDINPUT 0
#define LEDLOW 1
#define LEDHIGH 2

#define test 19

// #define N 0
// #define M 1
// #define V 2
// #define R 3


enum Telegraph {N, M, V, R, S, W, O, F, T, P, B, G, Y, H, K, E, I, L, A, D};

// debug
int incomingcommand = 0;
void serialdebug(int incomingcommand_);
int lastinputstatus = 0;
// debug end

/* Global Variable */
int selectedswitch = 0;
int inputstatus = 0;
int cycleshort = 0;
int cyclelong = 0;
int inputflag = 0;
int LEDPWM[20];

void SetMultiplexSwitch(int selectedswitch_, int state);
int ReadSwitch(void);
void SetLEDpin(int pin, int state);

// Initialises switches GPIOs and clocks
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; // structure variable used for the GPIO configuration
    GPIO_PinRemapConfig(AFIO_PCFR1_PA12_REMAP, DISABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // to Enable the clock for Port C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // to Enable the clock for Port A

    // initialise PC5 as input (SW left)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // initialise PC6 as input (SW middle)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // initialise PC7 as input (SW right)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // initialise PD6 as output (SW1 select)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // initialise PD5 as output (SW2 select)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // initialise PD4 as output (SW3 select)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // // initialise PD3 as output (SW4 select)
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOD, &GPIO_InitStructure);

    // // initialise PD2 as output (SW5 select)
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOD, &GPIO_InitStructure);

    // initialise PA1 as output (SW4 select)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // initialise PA2 as output (SW5 select)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void morsedebug(int payload)
{
    for (int n = 0; n < 5; n++)
    {
        SetLEDpin(n, LEDINPUT);
    }

    SetLEDpin(0, LEDLOW);
    for (int n = 0; n < payload; n++)
    {
        // SetLEDpin(1, LEDHIGH);
        GPIO_WriteBit(GPIOD, GPIO_Pin_2, SET);
        Delay_Ms(50);
        // SetLEDpin(1, LEDLOW);
        GPIO_WriteBit(GPIOD, GPIO_Pin_2, RESET);
        Delay_Ms(100);
    }
    Delay_Ms(200);
}

void debugfunction(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // to Enable the clock for Port C
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // to Enable the clock for Port A
    //  PD0 (A)
    //  PC0 (B)
    //  PA1 (C)
    //  PC3 (D)
    //  PA2 (E)

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOD, GPIO_Pin_0, RESET);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_0, SET);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOA, &GPIO_InitStructure);
    // GPIO_WriteBit(GPIOA, GPIO_Pin_1, SET);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOC, &GPIO_InitStructure);
    // GPIO_WriteBit(GPIOC, GPIO_Pin_3, SET);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOA, &GPIO_InitStructure);
    // GPIO_WriteBit(GPIOA, GPIO_Pin_2, SET);
}

int main(void)
{
    uint8_t GPIOInputStatus = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();
    // initialise SW select and LEDs
    for (int n = 0; n < 5; n++)
    {
        SetMultiplexSwitch(n, SET);
        SetLEDpin(n, LEDINPUT);
    }

    // Set all LEDs to maximum brightness
    for (int n = 0; n < 20; n++)
        LEDPWM[n] = 99;

    // DEBUG
    // debugfunction();
    // for (int i = 0; i < 5; i++)
    // {
    //     for (int n = 0; n < 5; n++)
    //     {
    //         for (int y = 0; y < 5; y++)
    //             SetLEDpin(y, LEDINPUT);
    //         SetLEDpin(i, LEDLOW);
    //         SetLEDpin(n, LEDHIGH);
    //         Delay_Ms(50);
    //     }
    // }

 

    // for (int i = 0; i < 5; i++)
    // {
    //     SetLEDpin(i, LEDLOW);

    //     for (int n = 0; n < 4; n++)
    //     {
    //            for (int y = 0; y < 5; y++) // Set all LEDs as inputs
    //     SetLEDpin(y, LEDINPUT);
    //     SetLEDpin(i, LEDLOW);
    //         if (LEDPWM[i * 4 + n] >= cyclelong)
    //             SetLEDpin((i + n + 1) % 5, LEDHIGH);
    //                         Delay_Ms(50);

    //             SetLEDpin((i + n + 1) % 5, LEDLOW);
    //     }
    // }


    LEDPWM[A] = 0;
        LEDPWM[D] = 0;

    LEDPWM[G] = 0;

    LEDPWM[L] = 0;

    // GPIO_WriteBit(GPIOC, GPIO_Pin_0, RESET);
    // GPIO_WriteBit(GPIOD, GPIO_Pin_0, RESET);
    //  USART_Printf_Init(115200);
    // printf("SystemClk:%d\r\n", SystemCoreClock);
    // printf("GPIO Toggle TEST\r\n");

    while (1)
    {
        cycleshort++;
        if (cycleshort > 4)
            cycleshort = 0; // cycle between 5 state each loop
        cyclelong++;
        if (cyclelong > 99)
            cyclelong = 0; // cycle between 100 state each loop

        // Multi Switches read(as described in the draw.io document)
        SetMultiplexSwitch(cycleshort, RESET);
        if (ReadSwitch())
            inputflag = 1;
        SetMultiplexSwitch(cycleshort, SET);
        // Multi Switches end

        // Charlieplex LED controller (as described in the draw.io document)
        for (int n = 0; n < 5; n++) // Set all LEDs as inputs
            SetLEDpin(n, LEDINPUT);
        SetLEDpin(cycleshort, LEDLOW);
        for (int n = 0; n < 4; n++)
        {
            if (LEDPWM[cycleshort * 4 + n] >= cyclelong)
                SetLEDpin((cycleshort + n + 1) % 5, LEDHIGH);
        }
        // Charlieplex LED controller end

        // debug
        if (inputflag)
        {
            morsedebug(inputstatus);
            inputflag = 0;
        }
        Delay_Us(100);
    }
}

void SetMultiplexSwitch(int selectedswitch_, int state)
{
    switch (selectedswitch_)
    {
    case SW1: // PD6
        GPIO_WriteBit(GPIOD, GPIO_Pin_6, state);
        break;
    case SW2: // PD5
        GPIO_WriteBit(GPIOD, GPIO_Pin_5, state);
        break;
    case SW3: // PD4
        GPIO_WriteBit(GPIOD, GPIO_Pin_4, state);
        break;
    case SW4: // PD3//new is PA1
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, state);
        break;
    case SW5: // PD2 //new is PA2
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, state);
        break;
    }
}

// Reads the switches state and populate input status, returns 1 if an input is detected
int ReadSwitch(void)
{
    // PC5 - left
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 0)
    {
        inputstatus = 1 + cycleshort * 3;
        return 1;
    }
    // PC6 - button
    else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == 0)
    {
        inputstatus = 2 + cycleshort * 3;
        return 1;
    }
    // PC7 - right
    else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == 0)
    {
        inputstatus = 3 + cycleshort * 3;
        return 1;
    }
    else
        return 0;
}

// Sets the 5 LED pins either as input, high or low
void SetLEDpin(int pin, int state)
{
    //  PD0 (A)
    //  PC0 (B)
    //  PA1 (C) new PD3
    //  PC3 (D)
    //  PA2 (E) new PD2
    GPIO_PinRemapConfig(AFIO_PCFR1_PA12_REMAP, DISABLE);

    // original
    // uint16_t LEDinputLUT[5] = {GPIO_Pin_0, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_3, GPIO_Pin_2};
    // uint32_t LEDinputportLUT[5] = {GPIOD, GPIOC, GPIOA, GPIOC, GPIOA};

    uint16_t LEDinputLUT[5] = {GPIO_Pin_0, GPIO_Pin_0, GPIO_Pin_3, GPIO_Pin_3, GPIO_Pin_2};
    uint32_t LEDinputportLUT[5] = {GPIOD, GPIOC, GPIOD, GPIOC, GPIOD};

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // to Enable the clock for Port C

    switch (state)
    {
    case LEDINPUT:
        GPIO_InitStructure.GPIO_Pin = LEDinputLUT[pin];
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(LEDinputportLUT[pin], &GPIO_InitStructure);
        break;

    case LEDLOW:
        GPIO_InitStructure.GPIO_Pin = LEDinputLUT[pin];
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(LEDinputportLUT[pin], &GPIO_InitStructure);
        GPIO_WriteBit(LEDinputportLUT[pin], LEDinputLUT[pin], RESET);
        break;

    case LEDHIGH:
        GPIO_InitStructure.GPIO_Pin = LEDinputLUT[pin];
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(LEDinputportLUT[pin], &GPIO_InitStructure);
        GPIO_WriteBit(LEDinputportLUT[pin], LEDinputLUT[pin], SET);
        break;
    }
}