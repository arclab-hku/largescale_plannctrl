/*
Description: Run 
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
    if (Vr(0) == 0 && Vr(1) == 0)
        yawr_dot = 0;
    else
        yawr_dot = (Vr(0) * Ar(1) - Ar(0) * Vr(1)) / (Vr(0) * Vr(0) + Vr(1) * Vr(1));
    yawr = yawr + yawr_dot * h_;        // yaw reference
    if (yawr > M_PI)                                    // correct 
        yawr = yawr - 2 * M_PI;
    else if (yawr < -M_PI)
        yawr = yawr + 2 * M_PI;

    yawCtrl = yawr;
    // yawCtrl = atan2(Vr(1), Vr(0));
}

void BackStepping::LinearController_(Vector3d P, Vector3d V, Vector3d desire_P, Vector3d desire_Pd, Vector3d desire_Pdd)
{
    // integral position error
    Vector3d Pe0 = desire_P - P;
    Int_Pe_ = Int_Pe_ + h_ * Pe0;

    // position control
    Vector3d Pe = desire_P - P + K1_ * Int_Pe_;          // position error
    Vc = desire_Pd + A1_ * Pe + K1_ * (desire_P - P);       // virtual control input (velocity)
}

void BackStepping::controller(States state, Vector3d desire_P, Vector3d desire_Pd, Vector3d desire_Pdd)
{
    Vector3d P = coor_(state.P_E);
    Vector3d V = coor_(state.V_E);

    LinearController_(P, V, coor_(desire_P), coor_(desire_Pd), coor_(desire_Pdd));
    YawController_(desire_P, desire_Pd, desire_Pdd);

    velCtrl = coor_(Vc);
}
