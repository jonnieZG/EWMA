# EWMA
Exponentially Weighted Moving Average filter is used for smoothing data series readings. Unlike the method with a history buffer that calculates an average of the last N readings, this method consumes significantly less memory and works faster.

For example, if you have a wonky ADC, like the one in ESP8266, with a lot of noise, you will need a filter to smooth out the readings. Basically, EWMA filter allows you to specify the weight of the last reading versus the previous filtered value, by setting the `alpha` parameter. Roughly said, if you set `alpha` to, let's say, 0.1 it means that the result will be approximately the average of the last 10 readings.

`output = alpha * reading + (1 - alpha) * lastOutput`

- `alpha` = Smoothing factor, in range [0,1]. Higher the value - less smoothing (higher the latest reading impact)
- `reading` = current input value
- `lastOutput` = last filter output value
- `output` = filter output value after the last reading

# EWMAT - Template for no-float filter
Exponentially Weighted Moving Average filter template that allows restriction to a specific data type (generally a non-floating-point
data type), such as `uint32_t`. Avoiding floating point arithmetics can significantly decrease code footprint, especially in embeded
devices, such as Arduino or STM32.

Note that the integer data type has to be as big as possible (32 bits at least, signed or unsinged), in order to allow internal
calculations to be correctly performed, since the result will overflow in case when a too small data type is chosen.

The filtered value in this class is calculated as:

`output = (alpha * reading + (alphaScale - alpha) * lastOutput) / alphaScale`
 
If you want to create a filter for integers, with an alpha value of 0.03, you will just do the following:

`EwmaT <int> filter(3, 100)`

- `alpha` = Smoothing factor in range [0,`alphaScale`]. Higher the value - less smoothing (higher the latest reading impact)
- `alphaScale` = Number that will divide the `alpha` value, in order to get the actual alpha parameter of the filter (usually 10, 100, 1000 etc.)
- `lastOutput` = last filter output value
- `output` = filter output value after the last reading

# Applications

Some sensors, like accelerometers or fast photoresistors that move a lot, give you quite noisy readings, meaning that two consecutive readings usually can differ up to 10%. These spikes make detection of movements (or whatever correlated events) impossible, so in order to smooth them out, you need to use a filter like this one.

Instantiate a filter, find an `alpha` value that meets the best your sampling frequency and noise level (the actual value is something you have to find out by trial and error) and feed it with readings from the sensor. Instead of using these readings directly in your further applications (calulations or whatever), read the `.output` value from the filter - and that's all.

# Example
This example reads ADC input and filters it with two separate EWMA filters, each one with a different smoothing factor. You can observe how the first one is faster to detect changes, but more prone to noise, while the last one is less prone to noise, but slower to detect changes. The selection of the best alpha value depends on your actual application, the amount of noise and sampling frequency.

```C++
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
```
