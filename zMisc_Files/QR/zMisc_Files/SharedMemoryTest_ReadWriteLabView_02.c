/* Test the PicoC shared memory functions, reading and writing from LabView.

Instructions:
Set up LabView to read Shared Variable Integers 0x11 (17) 0x25 (37) and 0x64 (100) as sensors, streaming, every 200ms.
Set up LabView to read Shared Variable Float 0x04 (4) and 0xF8 (248) as sensors, streaming, every 200 ms.
Set up LabView to write into Shared Variable Integers 0x21 (33) and 0xF5 (245) as motors. Use values of 0x00 and 0xFF as the data to write (on button down and button up).

Watch the sensor values change (set them to streaming to see it live), and then
start changing the motor values. The sensor values will change based on the motor
values sent in.

This test demonstrates several important features:

* Reading from multiple shared variables, both 32-bit integer and floating point values, as sensors within LabView.
* Writing into multiple shared variables, with 8-bit values, as motors within LabView.
* A PicoC program that's able to send changing data to the PC through shared variables (floats and 32-bit ints).
* A PicoC program that's able to receive changing data from the PC through shared variables (8-bit ints).
* A PicoC program that uses the input changes from the PC to change it's output values.

This PicoC program will run for approximately 1 minute and then terminate on its own.
*/

int i = 0, j = 0;
int iterations = 600;
int increment_speed = 5;
int delay1 = 20;
int sign = 1;                   // Controls direction of pico_int[0x64] movement.
int speed_64 = 0;               // Controls how fast pico_int[0x64] moves

// Initialize all of the shared variables that we use to reasonable initial values.
// Note you don't have to use hex notation for the variable indexes.
// Each variable type has 256 elements, from 0 through 255.
// Integers are signed numbers from -2,147,483,684 to +2,147,483,647
pico_int[0x11] = 1000;          // decimal 17,  output to LabView,  range 0 to 5000
pico_int[0x21] = 0x00;          // decimal 33,  input from LabView, range 0 to 255
pico_int[0x25] = 255;           // decimal 37,  output to LabView,  range 0 to 255
pico_int[0x64] = -10000;        // decimal 100, output to LabView,  range -10000 to +10000
pico_int[0xF5] = 0x00;          // decimal 245, input from LabView, range 0 to 255
pico_float[0x04] = 14.21;       // decimal 4,   output to LabView,  range 0.0 to 20.0
pico_float[0xF8] = -987.654;    // decimal 248, output to LabView,  range -1000.0 to 1000

printf("Starting to run SharedMemoryTest_ReadWriteLabView demo application.\n\r");

// Exit the main loop if PC sets the trigger variable to 2
while(iterations)
{
    // 0x11 (int) will go from 0 to 5000 and then back to 0, 
    // or from 5000 down to 0 and then back to 5000, depending on if
    // 0x21 is above 0x80 or below 0x80.
    if (pico_int[0x21] > 0x80) {
        increment_speed = 5;
    } else if (pico_int[0x21] < 0x80) {
        increment_speed = -5;
    } else {
        increment_speed = 0;
    }
    pico_int[0x11] = pico_int[0x11] + increment_speed;
    if (pico_int[0x11] > 5000) {
        pico_int[0x11] = 0;
    }
    if (pico_int[0x11] < 0) {
        pico_int[0x11] = 5000;
    }
    
    // 0x64 (int) will move smoothly from -10000 to 10000 and back.
    // The speed at which it will move is dependent on the value of 0xF5 (int).
    speed_64 = 100 + pico_int[0xF5];
    pico_int[0x64] = pico_int[0x64] + (speed_64 * sign);
    if (pico_int[0x64] < -10000) {
        sign = 1;
    }
    if (pico_int[0x64] > 10000) {
        sign = -1;
    }
    
    // pico_int[0x25] will either stay at zero (if pico_int[0xF5] >= 0x80) or
    // flip flop from 0 to 255 every 2 seconds (if pico_int[0xF5] < 0x80).
    if (delay1) {
        delay1--;
    }
    else {
        delay1 = 20; // Schedule us to run in another 2 seconds
        if (pico_int[0xF5] < 0x80) {
            // Flip all of the bits
            pico_int[0x25] = (~pico_int[0x25]) & 0xFF;
        }
        else {
            pico_int[0x25] = 0x00;
        }
    }
    
    // pico_float[0x04] will randomly walk between 10.0 and 20.0 if pico_int[0xF5] < 0x20
    // and it will randomly walk around from 0.0 to 10.0 if pico_int[0xF5] > 0xC0
    // Between those values, it will walk between 10.0 and 20.0.
    pico_float[4] = pico_float[4] + 0.5;
    if (pico_int[0xF5] < 0x20) {
        if (pico_float[4] < 10.0) {
            pico_float[4] = 10.0;
        }
    }
    if (pico_int[0xF5] > 0xC0) {
        if (pico_float[4] > 10.0) {
            pico_float[4] = 10.0;
        }
    }
    if (pico_float[4] > 20.0) {
        pico_float[4] = 20.0;
    }
    if (pico_float[4] < 0.0) {
        pico_float[4] = 0.0;
    }

    // pico_float[0xF8] will move between -1000.0 to +1000.0
    pico_float[0xF8] = pico_float[0xF8] + 123.456;
    if (pico_float[0xF8] > 1000.0) {
        pico_float[0xF8] = -1000.0;
    }
    
    iterations--;
    delay(100);             // Run at about 10Hz rate
}

printf(" We are now all done.\n\r");

exit(1);