#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void inverse_kinematic(double vx, double vy, double wz, double r1, double k1)
{
    double w1 = r1*( vx - vy - k1*wz );
    double w2 = r1*( vx + vy + k1*wz );
    double w3 = r1*( vx + vy - k1*wz );
    double w4 = r1*( vx - vy + k1*wz );

    printf("w1: %f [rad/s] \n", w1);
    printf("w2: %f [rad/s] \n", w2);
    printf("w3: %f [rad/s] \n", w3);
    printf("w4: %f [rad/s] \n", w4);
}

void forward_kinematic(double w1, double w2, double w3, double w4, double k1, double r4)
{
    double vx = (w1 + w2 + w3 + w4)*r4;
    double vy = (-w1 + w2 + w3 - w4)*r4;
    double wz = (-w1 + w2 - w3 + w4)*r4*(1/k1);
    
    printf("vx: %f [m/s] \n", vx);
    printf("vy: %f [m/s] \n", vy);
    printf("wz: %f [rad/s] \n", wz);
}

void main()
{
    const double lx = 0.115; // in [m]
    const double ly = 0.05; // in [m]
    const double wheel_radius = 0.03625; // in [m]
    const double r1 = 1.0 / wheel_radius;
    const double r4 = wheel_radius / 4;

    const double alpha_1 = 66.5; // [deg]
    const double alpha_2 = -66.5; // [deg]
    const double alpha_3 = 113.5; // [deg]
    const double alpha_4 = -113.5; // [deg]

    const double beta_1 = 90.0; // [deg]
    const double beta_2 = -90.0; // [deg]
    const double beta_3 = 90.0; // [deg]
    const double beta_4 = -90.0; // [deg]

    const double gamma_1 = -45.0; // [deg]
    const double gamma_2 = 45.0; // [deg]
    const double gamma_3 = 45.0; // [deg]
    const double gamma_4 = -45.0; // [deg]
    
    const double li = sqrt(pow(lx,2) + pow(ly,2)); // sin(alpha_1*(M_PI/180.0));

    //const double k1 = li * sin((beta_1 - gamma_1 - alpha_1)*(M_PI/180.0)) / sin(gamma_1*(M_PI/180.0)); // k1 = k2 = k3 = k4
    const double k1 = lx + ly; // k1 = k2 = k3 = k4

    // inverse kinematic equations
    double vx = 0.0;
    double vy = 0.0;
    double wz = 15.7;

    printf("vx: %f [m/s] \n", vx);
    printf("vy: %f [m/s] \n", vy);
    printf("wz: %f [rad/s] \n", wz);

    inverse_kinematic(vx, vy, wz, r1, k1);

    printf("\n");

    // forward kinematic equations
    double w1 = -15.7;
    double w2 = 15.7;
    double w3 = -15.7;
    double w4 = 15.7;

    printf("w1: %f [rad/s] \n", w1);
    printf("w2: %f [rad/s] \n", w2);
    printf("w3: %f [rad/s] \n", w3);
    printf("w4: %f [rad/s] \n", w4);

    forward_kinematic(w1, w2, w3, w4, k1, r4);    

}
