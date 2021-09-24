#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pbPlots.h"
#include "supportLib.h" 


double actuator(double pwm_input) // convert PWM [50-255] to RPMs [0-150]
{
    if (pwm_input >= 255.0)
    {
        //return 150.0;
        return 0.0;
    }
    else if(pwm_input <= 50.0)
    {
        return 0.0;
    }
    else
    {
        //return (pwm_input * 150) / 255;
        return 0.0;
    }
}


double level_limiter(double control_output) // receives controller output and limit its level
{
    if (control_output <= 50.0)
    {
        return 50.0;
    }
    else if (control_output >= 255)
    {
        return 255.0;
    }
    else
    {
        return control_output;
    }
}

void main()
{
    int time_of_sim = 110;
    double k_time[time_of_sim];

    // time array for plot signals
    for (int i = 0; i < time_of_sim; i++)
    {
        k_time[i] = i; // discrete time for plotting
    }

    double k_setpoint[time_of_sim];

    // time array for plot signals
    for (int i = 0; i < time_of_sim; i++)
    {
        if (i >= 10)
        {
            k_setpoint[i] = 100.0; // signal of RPM setpoint through the time
        }
        else
        {
            k_setpoint[i] = 0.0; // signal of setpoint through the time
        }
    }
    
    // arrays to save historical data
    double k_error[time_of_sim];
    double k_value_control[time_of_sim];
    double k_value_pwm[time_of_sim];
    double k_value_actuator[time_of_sim];

    // PI constants
    double Kp = 0.5977;
    double Ki = 0.0781; // rate of change, grater -> more speed to reach setpoint

    // PWM value after level limiter
    double pwm_output = 0.0;

    // initial value to start the algorithm
    k_error[0] = 0.0;
    k_value_control[0] = 0.0; // initial control output for k-1 time
    k_value_pwm[0] = level_limiter(k_value_control[0]);
    k_value_actuator[0] = actuator(k_value_pwm[0]);

    for (int k = 1; k < time_of_sim; k++)
    {
        k_error[k] = k_setpoint[k-1] - k_value_actuator[k-1]; // this is the current error
        k_value_control[k] = k_value_control[k-1] + Kp * k_error[k] + Ki * k_error[k-1];
        k_value_pwm[k] = level_limiter(k_value_control[k]);
        k_value_actuator[k] = actuator(k_value_pwm[k]);
    }
    
    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_time[i]);
    // }

    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_setpoint[i]);
    // }

    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_error[i]);
    // }

    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_value_control[i]);
    // }

    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_value_pwm[i]);
    // }
    
    // for (int i = 0; i < time_of_sim; i++)
    // {
    //     printf("%f \n", k_value_actuator[i]);
    // }

    FILE *fp;
    fp = fopen("output.csv","w");

    fprintf(fp, "TIME \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n", k_time[i]);
    }
    fprintf(fp, "SETPOINT \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n", k_setpoint[i]);
    }
    fprintf(fp, "ERROR \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n", k_error[i]); 
    }
    fprintf(fp, "CONTROL \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n", k_value_control[i]);
    }
    fprintf(fp, "PWM \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n",  k_value_pwm[i]);
    }
    fprintf(fp, "RPM \n");
    for (int i = 0; i < time_of_sim; i++)
    {
        fprintf(fp, "%f\n", k_value_actuator[i]);
    }
    
    fclose(fp);
    fp = 0;


    RGBABitmapImageReference *canvasReference1 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference1, 800, 400, k_time, time_of_sim, k_setpoint, time_of_sim);
    
    size_t length1;
	double *pngdata1 = ConvertToPNG(&length1, canvasReference1->image);
	WriteToFile(pngdata1, length1, "setpoint.png");
	DeleteImage(canvasReference1->image);


    RGBABitmapImageReference *canvasReference2 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference2, 800, 400, k_time, time_of_sim, k_error, time_of_sim);
    
    size_t length2;
	double *pngdata2 = ConvertToPNG(&length2, canvasReference2->image);
	WriteToFile(pngdata2, length2, "error.png");
	DeleteImage(canvasReference2->image);


    RGBABitmapImageReference *canvasReference3 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference3, 800, 400, k_time, time_of_sim, k_value_control, time_of_sim);
    
    size_t length3;
	double *pngdata3 = ConvertToPNG(&length3, canvasReference3->image);
	WriteToFile(pngdata3, length3, "controller.png");
	DeleteImage(canvasReference3->image);


    RGBABitmapImageReference *canvasReference4 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference4, 800, 400, k_time, time_of_sim, k_value_pwm, time_of_sim);

    size_t length4;
	double *pngdata4 = ConvertToPNG(&length4, canvasReference4->image);
	WriteToFile(pngdata4, length4, "pwm_control.png");
	DeleteImage(canvasReference4->image);


    RGBABitmapImageReference *canvasReference5 = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference5, 800, 400, k_time, time_of_sim, k_value_actuator, time_of_sim);

    size_t length5;
	double *pngdata5 = ConvertToPNG(&length5, canvasReference5->image);
	WriteToFile(pngdata5, length5, "actuator.png");
	DeleteImage(canvasReference5->image);
}