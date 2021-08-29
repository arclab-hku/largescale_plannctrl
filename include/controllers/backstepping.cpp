/*
Description: A Backsteppint Controller 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include <controllers/backstepping.h>

BackStepping::BackStepping(int FREQ)
{
    // control frequency
    h_ = 1.0 / FREQ;

    // control parameters
    A1_ << 0.8, 0.0, 0.0,       // position error
            0.0, 0.8, 0.0,
            0.0, 0.0, 0.7;
    K1_ << 0.3, 0.0, 0.0,       // integral of position error
            0.0, 0.3, 0.0,
            0.0, 0.0, 0.7;

    // variables for control
    Int_Pe_ << 0, 0, 0;
    yawr = 0.0;
}

Vector3d BackStepping::coor_(Vector3d p)
{
    p(1) = -p(1);
    p(2) = -p(2);
    return p;
}

void BackStepping::YawController_(Vector3d Pr, Vector3d Vr, Vector3d Ar)
{
    // dot of yaw
    if (abs(Vr(0)) < 0.1 && abs(Vr(1)) < 0.1)
        yawr_dot = 0;
    else
        yawr_dot = (Vr(0) * Ar(1) - Ar(0) * Vr(1)) / (Vr(0) * Vr(0) + Vr(1) * Vr(1));
    yawr = twoPI(yawr + yawr_dot * h_);        // yaw reference 1

    // yaw reference 2
    double yawr_vtang = yawr;
    if (abs(Vr(0)) < 0.1 && abs(Vr(1)) < 0.1)        // vx, vy << 1
    {
        yawr_vtang = yawr;
    }
    else if (Vr(0) == 0)       // vx<<1
    {
        if (Vr(1) > 0) yawr_vtang = M_PI / 2;
        else yawr_vtang = -M_PI / 2;
    }
    else if (Vr(1) == 0)       // vy << 1
    {
        if (Vr(0) > 0) yawr_vtang = 0;
        else yawr_vtang = -M_PI;
    }
    else if (abs(Vr(0)/Vr(1)) < 0.1)       // vx<<1
    {
        if (Vr(1) > 0) yawr_vtang = M_PI / 2;
        else yawr_vtang = -M_PI / 2;
    }
    else if (abs(Vr(1)/Vr(2)) < 0.1)       // vy << 1
    {
        if (Vr(0) > 0) yawr_vtang = 0;
        else yawr_vtang = -M_PI;
    }
    else
    {
        yawr_vtang = atan2(Vr(1), Vr(0));
    }

    // correct steay error on yaw.
    double yaw_error = yawr_vtang - yawr;

    if (abs(yaw_error) > 0.1 && abs(yaw_error - yaw_errorlast) < 0.01)
    {
        // printf ("yaw r: %.4f, yaw r 2: %.4f\n", yawr, yawr_vtang);
        correct_yaw++;
        if (correct_yaw >= 7)
        {
            yawr = twoPI(yawr + yaw_error);
            correct_yaw = 0;
            // printf("---correcting---\n%.4f\n",correct_yaw);
        }
    }
    else
    {
        correct_yaw = 0;
    }
    yaw_errorlast = yaw_error;

    yawCtrl = yawr;
}

void BackStepping::controller(States state, Vector3d desire_P, Vector3d desire_Pd, Vector3d desire_Pdd)
{
    Vector3d P = coor_(state.P_E);
    Vector3d V = coor_(state.V_E);

    YawController_(desire_P, desire_Pd, desire_Pdd);
}
