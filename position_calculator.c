#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pbPlots.h"
#include "supportLib.h" 


void plot_graphics(double xt[], double yt[], int size_of_vectors)
{
    double xs[] = {-1,0,1};
    double ys[] = {-1,0,1};

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    RGBABitmapImage image;

	DrawScatterPlot(canvasReference, 600, 600, xs, 3, ys, 3);

    double x1 = MapXCoordinateAutoSettings(-1, canvasReference->image, xs, 3);
    double y1 = MapYCoordinateAutoSettings(1, canvasReference->image, ys, 3);

    double x2 = MapXCoordinateAutoSettings(1, canvasReference->image, xs, 3);
    double y2 = MapYCoordinateAutoSettings(1, canvasReference->image, ys, 3);
    
    double x3 = MapXCoordinateAutoSettings(-1, canvasReference->image, xs, 3);
    double y3 = MapYCoordinateAutoSettings(-1, canvasReference->image, ys, 3);

    double x4 = MapXCoordinateAutoSettings(1, canvasReference->image, xs, 3);
    double y4 = MapYCoordinateAutoSettings(-1, canvasReference->image, ys, 3);

    DrawLine(canvasReference->image, x1, y1, x2, y2, 1, CreateRGBAColor(1.0,0.0,0.0,0.5));
    DrawLine(canvasReference->image, x1, y1, x3, y3, 1, CreateRGBAColor(1.0,0.0,0.0,0.5));
    DrawLine(canvasReference->image, x3, y3, x4, y4, 1, CreateRGBAColor(1.0,0.0,0.0,0.5));
    DrawLine(canvasReference->image, x2, y2, x4, y4, 1, CreateRGBAColor(1.0,0.0,0.0,0.5));

    for (int i = 0; i <= size_of_vectors; i++) // draw points
    {
        double xi = MapXCoordinateAutoSettings(xt[i], canvasReference->image, xs, 3);
        double yi = MapYCoordinateAutoSettings(yt[i], canvasReference->image, ys, 3);
        DrawFilledCircle(canvasReference->image, xi, yi, 4, CreateRGBAColor(0.0,1.0,0.0,1));
    }
    
    //DrawFilledCircle(canvasReference->image, x1, y1, 5, CreateRGBAColor(0.0,1,0.5,0.8));
    //DrawRectangle1px(canvasReference->image, x1, y1, 480, 480, CreateRGBAColor(0.5,0.5,0.5,0.8));
    //DrawFilledRectangle(canvasReference->image, x1, y1, 480, 480, CreateRGBAColor(0.5,0.5,0.5,1));

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "example.png");
	DeleteImage(canvasReference->image);
}


void main()
{
    double vx = 1.0; // [m/s]
    double vy = 0.0; // [m/s]
    double wz = 0.0; // [rad/s]
    
    double posx = 0.0; // current x position
    double x_coord[100]; // historical recording of x position

    double posy = 0.0; // current x position
    double y_coord[100]; // historical recording of x position

    double theta = 90.0; // current theta angle
    double z_coord[100]; // historical recording of x position

    const double tick_time = 0.05; // integral time interval 0.01[s] = 10ms 

    int time_of_integration = round(1/tick_time); // time in seconds / integral time interval

    printf("%d \n", time_of_integration);

    for (int i = 0; i <= time_of_integration; i++) // each for's iteration is a k time
    {
        if (i == round(time_of_integration/2))
        {
            vx = 0.0;
            vy = 1.0;
        } 
        
        // update historical data of position (later it is used for graphics)
        x_coord[i] = posx;
        y_coord[i] = posy;
        z_coord[i] = theta;

        // update current position by discrete integral
        posx = posx + vx * tick_time;
        posy = posy + vy * tick_time;
        theta = theta + wz * (180/M_PI) * tick_time; // conversion from [rad/s] to [deg]
    }

    printf("%f \n", x_coord[time_of_integration]);
    
    //printf("%d", sizeof(x_coord)/sizeof(x_coord[0]));
    plot_graphics(x_coord, y_coord, time_of_integration);
    
}