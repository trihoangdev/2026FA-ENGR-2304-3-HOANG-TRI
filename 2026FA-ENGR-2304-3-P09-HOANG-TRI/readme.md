# ENGR 2304 Final Project: Pressure Regulation and Rocket Launch Countdown

An Arduino Uno program (simulated in Tinkercad) that regulates a compressor until a desired pressure is reached, then runs a rocket launch countdown.

## What the program does

1. **Reads the desired pressure** from a dial on pin A0 (0 to 100 psi).
2. **Reads the current pressure** from a second dial on pin A2, which simulates the compressor output (0 to 100 psi).
3. **Shows both values on the LCD** (`Target` and `Now`).
4. **Regulates the compressor:** while the current pressure is below the target, the compressor output (pin 7) stays ON. When the target is reached, the compressor turns OFF.
5. **Starts the rocket countdown:** it counts down from 10 to 0, showing the number in **binary on 4 LEDs** (pins 13, 12, 8, 4) and in decimal on the LCD.
6. **Launch:** the LCD shows `LIFTOFF!` and the program stops.

## Binary convention

As required by the assignment, numbers not written with the `0x` prefix are treated as binary (for example `0b1010` is 10, `0b1100100` is 100).

## Hardware (Tinkercad)

| Part                               | Connection         |
| ---------------------------------- | ------------------ |
| Target pressure dial               | A0                 |
| Simulated compressor pressure dial | A2                 |
| Compressor LED                     | Pin 7              |
| Countdown LEDs (bit 0 to bit 3)    | Pins 13, 12, 8, 4  |
| I2C LCD (16x2)                     | SDA = A4, SCL = A5 |

## How to run

1. Open the Tinkercad circuit `ENGR-2304-FINAL-PROJECT`.
2. Click **Code**, switch to **Text**, and paste the code from this repository.
3. Click **Start Simulation**.
4. Turn the left dial to set the target pressure, then turn the right dial up until `Now` reaches the target.
5. Watch the countdown on the LEDs and the LCD.

## Files

- `2026FA-ENGR-2304-3-P09-HOANG-TRI.ino`: main Arduino source code
- `README.md`: this file

## Design

- `https://www.tinkercad.com/things/ht9rwt0yVnR-2026fa-engr-2304-3-p09-hoang-tri/editel?returnTo=%2Fdashboard%2Fdesigns%2Fall&sharecode=fPahoB_UYSPWOckZMK_DWSWIfB7ygCrp5vssi8vKPa8`

## Author

Tri Hoang, ENGR 2304, Dallas College
