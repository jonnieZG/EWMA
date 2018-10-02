# EWMA
Exponentially Weighted Moving Average filter is used for smoothing data series readings.

Unlike the method with a history buffer that calculates an average of the last N readings, this method consumes significantly less memory and works faster.

`output = alpha * reading + (1 - alpha) * lastOutput`

- alpha = Smoothing factor, in range [0,1]. Higher the value - less smoothing (higher the latest reading impact)
- reading = current input value
- lastOutput = last filter output value
- output = filter output value after the last reading

# EWMAT - Template for no-float filter
Filter template that allows restriction to only one specific data type, such as `uint32_t`. Avoiding floating point arithmetics 
can significantly decrease code footprint, especially in embeded devices, such as Arduino or STM32.

The filtered value in this class is calculated as:

`output = (alpha * reading + (alphaScale - alpha) * lastOutput) / alphaScale`
 
If you want to create a filter for integers, with an alpha value of 0.03, you will just do the following:

`EwmaT <int> filter(3, 100)`

- alpha = Smoothing factor in range [0,alphaScale]. Higher the value - less smoothing (higher the latest reading impact)
- alphaScale = Number that will divide the alpha, usually 10, 100, 1000 etc.
- lastOutput = last filter output value
- output = filter output value after the last reading
