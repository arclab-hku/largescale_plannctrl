/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include <Tools.h>

double clip(double x, double minv, double maxv)
{
    if (x<=minv)
    {
        return minv;
    }
    else if (x>=maxv)
    {
        return maxv;
    }
    else
    {
        return x;
    }
}

Quaterniond Euler2Quaternion(Vector3d euler)
{
    double cr = std::cos(euler(0) * 0.5);
    double sr = std::sin(euler(0) * 0.5);
    double cp = std::cos(euler(1) * 0.5);
    double sp = std::sin(euler(1) * 0.5);
    double cy = std::cos(euler(2) * 0.5);
    double sy = std::sin(euler(2) * 0.5);

    Quaterniond q;
    q.w() = cr * cp * cy + sr * sp * sy;
    q.x() = sr * cp * cy - cr * sp * sy;
    q.y() = cr * sp * cy + sr * cp * sy;
    q.z() = cr * cp * sy - sr * sp * cy;

    return q.normalized();
}
