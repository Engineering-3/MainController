int x, adc3;
float adc3_volts;
printf("Program starting.\n\r");
for (x=0; x < 10; x++)
{
                adc3 = readi2c2(0x1C, 0xB3);
                adc3_volts = ((float)adc3/1024.0) * 5.0;
                printf("ADC3 = %fV\n\r", adc3_volts);
                delay(100);
}
printf("Program complete.\n\r");
exit(1);