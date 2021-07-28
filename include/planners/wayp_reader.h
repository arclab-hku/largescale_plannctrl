#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <Eigen/Eigen>
#include <fstream>

using namespace std;
using namespace Eigen;

/*
// get waypoints from file.
*/
class WayPointsReader
{
    private:
        ifstream infile;

    public:
        int N;

        WayPointsReader();
        MatrixXd read();
};
