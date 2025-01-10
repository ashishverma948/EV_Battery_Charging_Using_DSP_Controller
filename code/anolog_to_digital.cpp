#include "F28x_Project.h"

void InitADC() {
    EALLOW; 

    AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;  
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0;  

    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;    
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); 

    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; 
    DELAY_US(1000); 

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;   
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14;   
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;  
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;    // Enable INT1
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  // Clear INT1 flag

    EDIS; 
}

void InitEPWM_ADCTrigger() {
    EALLOW;

    // Configure EPWM1 for ADC trigger
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;    // SOCA on up-count CMPA match
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     // Generate SOCA on the 1st event

    EDIS;
}

interrupt void ADC_ISR() {
    uint16_t adcResult;

    // Read the ADC result
    adcResult = AdcaResultRegs.ADCRESULT0;

    // Example: Use the ADC value to update PWM duty cycle
    float dutyCycle = ((float)adcResult / 4095.0) * 100.0; // Scale 12-bit ADC result to 0-100%
    UpdatePWMDutyCycle(dutyCycle);

    // Clear the interrupt flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    // Acknowledge the interrupt
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

int main(void) {
    InitSysCtrl(); // Initialize system control
    InitGpio();    // Initialize GPIOs
    InitPWM();     // Initialize PWM
    InitADC();     // Initialize ADC
    InitEPWM_ADCTrigger(); // Set up EPWM trigger for ADC

    // Configure interrupts
    EALLOW;
    PieVectTable.ADCA1_INT = &ADC_ISR;       // Map ADC ISR
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;       // Enable ADC interrupt
    IER |= M_INT1;                           // Enable CPU INT1
    EINT;                                    // Enable Global Interrupts
    ERTM;                                    // Enable Real-Time Debug Mode
    EDIS;

    while (1) {
        // Main loop - all functionality is handled by the ISR
    }
}
