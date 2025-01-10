#include "F28x_Project.h"

#define PWM_FREQUENCY 10000   // 10 kHz
#define SYSTEM_CLOCK 100e6    // 100 MHz
#define TB_CLK (SYSTEM_CLOCK / 2) // Assuming prescaler divides by 2

void InitPWM() {
    EALLOW; 

    EPwm1Regs.TBPRD = TB_CLK / PWM_FREQUENCY; 
    EPwm1Regs.TBPHS.bit.TBPHS = 0;          
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;  // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1; // High-speed time base clock pre-scaler
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;    // Time base clock pre-scaler

    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD / 2; // Start with 50% duty cycle

    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;    // Set on up-count
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR; // Clear on down-count

    EDIS; 
}

void UpdatePWMDutyCycle(float dutyCycle) {
    EALLOW; // Enable protected register access

    if (dutyCycle > 100.0) dutyCycle = 100.0;
    if (dutyCycle < 0.0) dutyCycle = 0.0;

    EPwm1Regs.CMPA.bit.CMPA = (uint16_t)((dutyCycle / 100.0) * EPwm1Regs.TBPRD);

    EDIS; // Disable protected register access
}

int main(void) {
    InitSysCtrl(); // Initialize system control (clock, watchdog, etc.)
    InitGpio();    // Initialize GPIOs
    DINT;          // Disable CPU interrupts

    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // GPIO0 set for EPWM1A output
    EDIS;

    // Initialize PWM
    InitPWM();

    // Main loop
    while (1) {
        // Example: Dynamically change duty cycle from 0% to 100% and back
        for (float duty = 0.0; duty <= 100.0; duty += 1.0) {
            UpdatePWMDutyCycle(duty);
            DELAY_US(10000); // 10 ms delay
        }
        for (float duty = 100.0; duty >= 0.0; duty -= 1.0) {
            UpdatePWMDutyCycle(duty);
            DELAY_US(10000); // 10 ms delay
        }
    }
}
