/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include <controllers/backstepping.h>

#include <iostream>
#include <Eigen/Eigen>

#include <Tools.h>

using namespace std;
using namespace Eigen;

class BackStepping
{
    private:
        // constant
        double h_;
        // control parameters
        Matrix3d A1_, K1_;
        Vector3d Vc;
        // variables for control
        Vector3d Int_Pe_;
        double yawr_dot, yawr;

        // tool functions
        Vector3d coor_(Vector3d p);
        // controllers
        void LinearController_(Vector3d P, Vector3d V, Vector3d desire_P, Vector3d desire_Pd, Vector3d desire_Pdd);
        void YawController_(Vector3d Pr, Vector3d Vr, Vector3d Ar);

    public:
        // control inputs
        double yawCtrl;
        Vector3d velCtrl;

        BackStepping(int FREQ = 100);

        void controller(States state, Vector3d desire_P, Vector3d desire_Pd, Vector3d desire_Pdd);
};