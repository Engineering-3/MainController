/* Test the PicoC shared memory functions, reading and writing from LabView.

Instructions:
Set up LabView to read Shared Variable Integers 0x11 0x25 and 0x64 as sensors.
Set up LabView to read Shared Variable Float 0x04 and 0xF8 as sensors.
Set up LabView to write into Shared Variable Integers 0x21 and 0xF5 as motors.
Set up LabView to write into Shared Variable Floats 0x05 and 0xF9 as motors.

Watch the sensor values change (set them to streaming to see it live), and then
start changing the motor values. The sensor values will change based on the motor
values sent in.

This test demonstrates several important features:

* Reading from multiple shared variables, both 32-bit integer and floating point values, as sensors within LabView.
* Writing into multiple shared variables, both 32-bit integer and floating point values, as motors within LabView.
* A PicoC program that's able to send changing data to the PC through shared variables.
* A PicoC program that's able to receive changing data from the PC through shared variables.
* A PicoC program that uses the input changes from the PC to change it's output values.

This PicoC program will run for approximately 1 minute and then terminate on its own.
*/

int i = 0, j = 0;
int iterations = 600;
int increment_speed = 5;
int delay1 = 20;
int sign = 1;

// Initialize all of the shared variables that we use to reasonable initial values.
// Note you don't have to use hex notation for the variable indexes.
// Each variable type has 256 elements, from 0 through 255.
// Integers are signed numbers from -2,147,483,684 to +2,147,483,647
pico_int[0x11] = 1000;  // decimal 17, range 0 to 50000
pico_int[0x21] = 0x00;
pico_int[0x25] = 255;   // Decimal 37, range 0 to 255
pico_int[0x64] = -10000;// decimal 100, range -10000 to +10000
pico_int[0xF5] = 0x00;
pico_float[0x04] = 14.21;
pico_float[5] = 0.0;
pico_float[0xF8] = -987.654;
pico_float[249] = 10.0;     // Same as pico_float[0xf9]

printf("Starting to run SharedMemoryTest_ReadWriteLabView demo application.\n\r");

// Exit the main loop if PC sets the trigger variable to 2
while(iterations)
{
    // This one will move up or down at different rates
    pico_int[0x11] = pico_int[0x11] + increment_speed;
    if (pico_int[0x11] > 5000) {
        pico_int[0x11] = 0;
    }
    if (pico_int[0x21] > 128) {
        increment_speed = -50;
    }
    else {
        increment_speed = 5;
    }

    pico_int[0x64] = pico_int[0x64] + (100 * sign);
    if (pico_int[0x64] < -10000) {
        sign = 1;
    }
    if (pico_int[0x64] > 10000) {
        sign = -1;
    }
    
    // Trigger this action every 2 seconds
    if (delay1) {
        delay1--;
    }
    else {
        delay1 = 20;
//        if (pico_int[0xF5] == 0xFF) {
            // Flip all of the odd bits
            pico_int[0x25] = (~pico_int[0x25]) & 0xFF;
//        }
 //       else {
            // Flip all of the even bits
//            pico_int[0x25] = pico_int[0x25] | ~(pico_int[0x25] & 0xAA);
//        }
    }
    
    // 
//    pico_float[4] = pico_float[4] + (float)rand(100)/pico_float[5];
    pico_float[4] = pico_float[4] + 4.682;
    if (pico_float[4] > 200.0) {
        pico_float[4] = 0.0;
    }
    
    //printf("%f\n\r", pico_float[4]);
    
    iterations--;
    delay(100);             // Run at about 10Hz rate
}

printf(" We are now all done.\n\r");

exit(1);