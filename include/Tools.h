/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once

#include <iostream>
#include <math.h>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

struct States
{
    Vector3d P_E, V_E;
};

double clip(double x, double minv, double maxv);

Quaterniond Euler2Quaternion(Vector3d euler);

double twoPI(double angle);