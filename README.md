# EWMA
Exponentially Weighted Moving Average filter is used for smoothing data series readings.

Unlike the method with a history buffer that calculates an average of the last N readings, this method consumes significantly less memory and works faster.

`output = alpha * reading + (1 - alpha) * lastOutput`

- alpha = Smoothing factor, in range [0,1]. Higher the value - less smoothing (higher the latest reading impact)
- reading = current input value
- lastOutput = last filter output value
- output = filter output value after the last reading
