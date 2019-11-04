/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>


#define MAX_PWM_COUNT       9000
#define sysClock            3000000

int main()
{
    // Declare angle variable as a float
    double angle;
    
    // Ask for user input
    printf("Please enter an angle value: ");
    
    /* Scan console for user input, and store the value (as a float) to the address of the angle variable
     * if the "&" isn't included, the function will not read the value stored in angle's address i.e. angle
     * The scanf() function passes a pointer, which is not promoted from float to double. This means you 
        have to specifically tell the function to look for a double. Hence, the %lf instead of %f
     */
    scanf("%lf", &angle); 
    
    // Print the angle value to the console
    // printf("You entered: %f", angle);

    // Convert angle to PWM duty cycle command
    double duty_cycle = (angle/405)+0.5;
    int duty_cycle_count = duty_cycle*MAX_PWM_COUNT;
    double real_duty_cycle = ((float) duty_cycle_count)/9000;
    double ideal_count = duty_cycle*MAX_PWM_COUNT;
    double error = (duty_cycle - real_duty_cycle) * 405;
    /* Above, here is a source of error. The decimals which "should" get taken along are
        instead truncated to accomodate uint_16t-natured dutyCycle class definition.
     * This means that we're systemically a small amount off from the specified angle for 
        angle values which are not multiples of 9-deg. Fortunately, 45-deg is a multiple of 9.
     * I suspect that the casting of duty_cycle_count to an int uses floor() for rounding because
        an angle of +135 yields duty_cycle_count of 7499 rather than 7500.
     */
    printf("\nIdeal Duty Cycle          = %f", duty_cycle);
    printf("\nActual Duty Cycle         = %f", real_duty_cycle);
    printf("\nIdeal Duty Cycle Count    = %f / 9000", ideal_count);
    printf("\nActual Duty Cycle Count   = %d / 9000", duty_cycle_count);
    printf("\nIdeal Angle               = %f", angle);
    printf("\nActual Angle              = %f", angle-error);
    printf(" (-%f)", error);
    
    /*
    // Output PWM signal at the specified duty cycle
    pwmConfig.dutyCycle = duty_cycle_count;     // probably would rather ditch the variable altogether and calculate everything in-line
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);     
    */
    return 0;
}

