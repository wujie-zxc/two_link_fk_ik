#include "mainwindow.h"

#include <QApplication>

#include <cmath>
#include <iostream>
#include <vector>
#include <QtDebug>

//const double PI = 3.14159265358979323846;
//const double L1 = 130;
//const double L2 = 114 ;

//// Forward kinematics function
//void forwardKinematics(double l1, double l2, double theta1, double theta2, double& x, double& y) {
//    // Convert angles from degrees to radians
//    theta1 = theta1 * PI / 180.0;
//    theta2 = theta2 * PI / 180.0;

//    // Calculate the end-effector position
//    x = l1 * cos(theta1) + l2 * cos(theta1 + theta2);
//    y = l1 * sin(theta1) + l2 * sin(theta1 + theta2);
//}

//// Inverse kinematics function
//void inverseKinematics(double l1, double l2, double x, double y, double& theta1, double& theta2) {
//    // Calculate the distance between the base and the end-effector
//    double d = sqrt(x*x + y*y);

//    // Check if the point is reachable
//    if (d > l1 + l2 || d < abs(l1 - l2)) {
//        std::cerr << "Point not reachable" << std::endl;
//        return;
//    }

//    // Calculate the angles
//    double c2 = (d*d - l1*l1 - l2*l2) / (2*l1*l2);
//    double s2 = sqrt(1 - c2*c2);
//    theta2 = atan2(s2, c2);
//    double c1 = (x*l1 + x*l2*c2 - y*l2*s2) / (l1*d);
//    double s1 = (y*l1 + y*l2*c2 + x*l2*s2) / (l1*d);
//    theta1 = atan2(s1, c1);

//    // Convert angles from radians to degrees
//    theta1 = theta1 * 180.0 / PI;
//    theta2 = theta2 * 180.0 / PI;
//}

//// Inverse kinematics function
//void inverseKinematics(double l1, double l2, double x, double y, std::vector<std::pair<double, double>>& solutions) {
//    // Calculate the distance between the base and the end-effector
//    double d = std::sqrt(x*x + y*y);

//    // Check if the point is reachable
//    if (d > l1 + l2 || d < std::abs(l1 - l2)) {
//        std::cerr << "Point not reachable" << std::endl;
//        return;
//    }

//    // Calculate possible angles for theta2
//    double c2 = (d*d - l1*l1 - l2*l2) / (2*l1*l2);
//    double s2 = std::sqrt(1 - c2*c2);
//    double theta2_1 = std::atan2(s2, c2);
//    double theta2_2 = std::atan2(-s2, c2); // Second solution for theta2

//    // Calculate theta1 for both theta2 values
//    double c1_1 = (x*l1 + x*l2*c2 - y*l2*s2) / (l1*d);
//    double s1_1 = (y*l1 + y*l2*c2 + x*l2*s2) / (l1*d);
//    double theta1_1 = std::atan2(s1_1, c1_1);

//    double c1_2 = (x*l1 + x*l2*c2 + y*l2*s2) / (l1*d);
//    double s1_2 = (y*l1 + y*l2*c2 - x*l2*s2) / (l1*d);
//    double theta1_2 = std::atan2(s1_2, c1_2);

//    // Convert angles from radians to degrees
//    solutions.push_back({theta1_1 * 180.0 / PI, theta2_1 * 180.0 / PI});
//    solutions.push_back({theta1_2 * 180.0 / PI, theta2_2 * 180.0 / PI});
//}

//void inverseKinematics_cos(double x, double y, double& theta1, double& theta2, double a1, double a2) {
//    double cosT_beta_numerator = (a1 * a1 + x * x + y * y - a2 * a2);
//    double cosT_beta_denumerator = 2 * a1 * sqrt(x * x + y * y);

//    theta1 = atan2(y, x) - acos(cosT_beta_numerator / cosT_beta_denumerator);

//    double cosT_alpha_numerator = a1 * a1 + a2 * a2 - (x * x + y * y);
//    double cosT_alpha_denumerator = 2 * a1 * a2;

//    theta2 = acos(cosT_alpha_numerator / cosT_alpha_denumerator) - PI;
//}

//// 计算两个角度之间的差值
//double angleDifference(double angle1, double angle2) {
//    return std::fmod(std::fabs(angle1 - angle2), 2 * PI);
//}


//// 逆向运动学
//int inverse_kinematics(double x, double y, double prevTheta1, double prevTheta2, double &deg1, double &deg2) {
//    // 检查目标位置是否在机械臂的工作范围内
//       double distanceSquared = x * x + y * y;
//       double maxReach = L1 + L2;
//       double minReach = std::abs(L1 - L2);
//       if (distanceSquared > maxReach * maxReach || distanceSquared < minReach * minReach) {
//           qDebug() << "Target position is out of reach";
//           return -1;
//       }

//       double cosTheta2 = (distanceSquared - L1 * L1 - L2 * L2) / (2 * L1 * L2);

//       // 检查 cosTheta2 是否在有效范围内
//       if (cosTheta2 < -1.0 || cosTheta2 > 1.0) {
//           qDebug() << "cosTheta2 out of range";
//           return -1;
//       }

//       double sinTheta2 = sqrt(1 - cosTheta2 * cosTheta2);

//       // 两组解
//      double t_angle2_1 = atan2(sinTheta2, cosTheta2);
//      double t_angle2_2 = atan2(-sinTheta2, cosTheta2);

//       double k1 = L1 + L2 * cosTheta2;
//       double k2 = L2 * sinTheta2;

//       double t_angle1_1 = atan2(y, x) - atan2(k2, k1);
//       double t_angle1_2 = atan2(y, x) - atan2(-k2, k1);

//       // 选择最小角度变化的解
//       double diff1 = angleDifference(t_angle1_1, prevTheta1) + angleDifference(t_angle1_2, prevTheta2);
//       double diff2 = angleDifference(t_angle2_1, prevTheta1) + angleDifference(t_angle2_2, prevTheta2);

//       if (diff1 < diff2) {
//           deg1 = t_angle1_1;
//           deg2 = t_angle1_2;
//       } else {
//           deg1 = t_angle2_1;
//           deg2 = t_angle2_2;
//       }
//       return 0;
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
