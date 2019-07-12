/*
 * This example reads ADC input and filters it with two separate EWMA filters, each one 
 * with a different smoothing factor. 
 * 
 * You can observe how the first one is faster to detect changes, but more prone to noise, 
 * while the last one is less prone to noise, but slower to detect changes. 
 * 
 * The selection of the best alpha value depends on your actual application, the amount of
 * noise and sampling frequency.
 */
 
#include <Arduino.h>
#include <Ewma.h>

Ewma adcFilter1(0.1);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma adcFilter2(0.01);  // More smoothing - less prone to noise, but slower to detect changes

void setup()
{
    Serial.begin(115200);
    pinMode(A0, INPUT);
}

void loop()
{
    int raw = analogRead(A0);
    float filtered1 = adcFilter1.filter(raw);
    float filtered2 = adcFilter2.filter(raw);
    Serial.printf("Raw=%d, Filter1=%.3f, Filter2=%.3f", raw, filtered1, filtered2);
    
    delay(100);
}
