/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include<logs/log_flight.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Eigen>
#include <time.h>
// #include <fstream>

#include <Tools.h>

using namespace std;
using namespace Eigen;

class LogFlight
{
    private:
        // states
        FILE *fp_posi;
        FILE *fp_velo;
        
        // desires
        FILE *fp_posid;
        FILE *fp_velod;

    public:
        LogFlight(string name0);
        ~LogFlight();

        // basics
        void states(States state);
        void desires(Vector3d p, Vector3d v);
};