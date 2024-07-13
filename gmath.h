#ifndef GMATH_H
#define GMATH_H

#include <cmath>
#include <iostream>
#include <vector>
#include <QtDebug>

const double PI = 3.14159265358979323846;
//const double L1 = 130;
//const double L2 = 114 + 110 ;

struct Gmath
{
    static double angleDifference(double angle1, double angle2) {
        return std::fmod(std::fabs(angle1 - angle2), 2 * PI);
    }

    static void forward_kinematics(double L1, double L2, double theta1, double theta2, double &x, double &y)
    {
        x = L1 * cos(theta1) + L2 * cos(theta1 + theta2);
        y = L1 * sin(theta1) + L2 * sin(theta1 + theta2);
    }

   static bool inverse_kinematics(double L1, double L2, double x, double y, double pre_deg1, double pre_deg2, double &theta1, double &theta2)
   {
       //若(x,y)在工作空间里，则c2必在[-1,1]里，但由于计算精度，c2的绝对值可能稍微大于1
       double c2 = (x * x + y * y - L1 * L1 - L2 * L2) / (2 * L1 * L2);
       qDebug() << c2;
       if (c2 > 1) c2 = 1;
       if (c2 < -1) c2 = -1;

       double temp = 1 - c2 *c2;
       if (temp < 0)
           temp = 0;
       double tmp_deg1 = atan2(sqrt(temp), c2);
       double tmp_deg2 = atan2(-sqrt(temp), c2);
       double diff1 = angleDifference(tmp_deg1, pre_deg2);
       double diff2 = angleDifference(tmp_deg2, pre_deg2);
       if (diff1 < diff2){
           theta2 = tmp_deg1;
       }else {
           theta2 = tmp_deg2;
       }
       double s2 = sin(theta2);
       theta1 = atan2(y, x) - atan2(L2 * s2, L1 + L2 * c2);

       return 0;
   }
};

#endif // GMATH_H
