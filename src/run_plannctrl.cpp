/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#include <Eigen/Eigen>
#include <math.h>
 
#include <ros/ros.h>

#include <offboard_env/ros_missn.h>
#include <controllers/backstepping.h>
#include <planners/trajgen.h>
#include <Tools.h>

using namespace std;
using namespace Eigen;

#define CtrlFreq 50         // control frequency
#define MAXVEL 15.0         // maximum velocity
#define MAXACC 4.0         // maximum acceleration
#define MAXCORVEL 6.0         // maximum corner velocity

int main(int argc, char **argv)
{
    double MaxVel, MaxAcc, MaxCnrVel = MAXCORVEL;

    // initialize node
    ros::init(argc, argv, "track_node");
    ros::NodeHandle nh;                // Create a handle to this process node.

    if (argc > 1)
    {
        MaxVel = clip(strtod(argv[1], NULL), 1.0, 16.0);
        MaxAcc = clip(strtod(argv[2], NULL), 0.1, 5.0);
        cout << MaxVel << endl
             << MaxAcc << endl;
        // max corner velocity
        if (MaxVel < MAXCORVEL)
            MaxCnrVel = MaxVel;
    }
    else
    {
        MaxVel = MAXVEL;
        MaxAcc = MAXACC;
        MaxCnrVel = MAXCORVEL;
    }

    // Intialize Planner
    TrajectoryGenerator reference(MaxVel, MaxAcc, MaxCnrVel);

    // Initialize ROS
    RosClass flying(&nh, CtrlFreq);
    flying.init(reference.LaunchHht);

    // Intialize Controller
    BackStepping bsc(CtrlFreq);     // controller

    // Launch the Drone
    States state = flying.launch();
    reference.initial_generate(state.P_E);
    printf("Vehicle Launched.\n");

    int i = 0;
    // for (int i = 0; i <= FlyStep; i++)
    while (!reference.trajFinished && ros::ok())
    {
        double timee = 1.0 * (i + 1) / CtrlFreq;
        // printf ("time %.2f\n", timee);

        //refer
        Vector3d p_d, v_d, a_d;
        reference.get_desire(timee, p_d, v_d, a_d);

        // calculate control inputs
        bsc.controller(state, p_d, v_d, a_d);

        // step forward
        state = flying.step(bsc.yawCtrl, p_d, "yaw_n_position"); 
        // state = flying.step(bsc.yawCtrl, bsc.velCtrl, "yaw_n_velocity"); 

        i++;
    }
    printf("\nMission Finished.\n");

    // landing
    printf("Landing.\n");
    flying.land();
    return 0;
}

