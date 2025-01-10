#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
#define SAMPLE_RATE 48000   
#define PHASE_SHIFT_DEG 45  

float inputBuffer[1024];    
float outputBuffer[1024];   
uint16_t bufferIndex = 0;

void applyPhaseShift(float* input, float* output, int bufferSize, float phaseShiftRadians) {
    float delaySamples = (phaseShiftRadians / (2 * PI)) * SAMPLE_RATE; 
    int integerDelay = (int)delaySamples;  
    float fractionalDelay = delaySamples - integerDelay;  

    for (int i = 0; i < bufferSize; i++) {
        int delayedIndex = (bufferIndex - integerDelay + 1024) % 1024;
        float delayedSample = input[delayedIndex];

        int nextIndex = (delayedIndex + 1) % 1024;
        delayedSample += fractionalDelay * (input[nextIndex] - input[delayedIndex]);

        output[i] = delayedSample;
        bufferIndex = (bufferIndex + 1) % 1024; 
    }
}

int main(void) {
    float phaseShiftRadians = PHASE_SHIFT_DEG * (PI / 180.0); 

    for (int i = 0; i < 1024; i++) {
        inputBuffer[i] = sin(2 * PI * 1000 * i / SAMPLE_RATE); // 1 kHz sine wave
    }

    // Apply phase shift
    applyPhaseShift(inputBuffer, outputBuffer, 1024, phaseShiftRadians);

    // Output signal (replace with DAC code in real implementation)
    for (int i = 0; i < 1024; i++) {
        // Output outputBuffer[i] to DAC
    }

    return 0;
} 