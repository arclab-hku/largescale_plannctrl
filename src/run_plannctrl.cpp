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
// #include <logs/log_flight.h>

using namespace std;
using namespace Eigen;

#define CtrlFreq 50         // control frequency
#define LaunchHht 3.0       // launch height
// #define MaxVel 15.0         // maximum velocity
// #define MaxAcc 2.0       // acceleration set
// #define MaxCnrVel 4.0       // max corner velocity

int main(int argc, char **argv)
{
    double MaxVel, MaxAcc, MaxCnrVel = 4.0;

    // Initialize ROS
    ros::init(argc, argv, "track_node");
    if (argc > 1)
    {
        MaxVel = clip(strtod(argv[1], NULL), 1.0, 16.0);
        MaxAcc = clip(strtod(argv[2], NULL), 0.1, 5.0);
        // max corner velocity
        if (MaxVel < 4.0)
            MaxCnrVel = MaxVel;
    }
    else
    {
        MaxVel = 15.0;
        MaxAcc = 2.0;
        MaxCnrVel = 4.0;
        cout << MaxVel << " " << MaxAcc << " " << MaxCnrVel << endl;
    }

    ros::NodeHandle nh;                // Create a handle to this process node.
    RosClass flying(&nh, CtrlFreq);
    flying.init(LaunchHht);

    // Intialize Planner
    TrajectoryGenerator reference(MaxVel, MaxAcc, MaxCnrVel);
    // double FlyTime = reference.generate();
    // int FlyStep = floor(FlyTime * CtrlFreq);

    // Intialize Controller
    BackStepping bsc(CtrlFreq);     // controller

    // LogFlight logger("plannctrl");    //logging
    
    // Launch the Drone
    States state = flying.launch();
    reference.initial_generate(state.P_E);
    printf("Vehicle Launched.\n");

    int i = 0;
    // for (int i = 0; i <= FlyStep; i++)
    while (!reference.trajFinished)
    {
        double timee = 1.0 * (i + 1) / CtrlFreq;

        //refer
        Vector3d p_d, v_d, a_d;
        reference.get_desire(timee, p_d, v_d, a_d);

        // calculate control inputs
        bsc.controller(state, p_d, v_d, a_d);

        // step forward
        // state = flying.step(bsc.yawCtrl, p_d, "yaw_n_position"); 
        state = flying.step(bsc.yawCtrl, bsc.velCtrl, "yaw_n_velocity"); 
        
        // log
        // logger.desires(p_d, v_d);
        // logger.states(state);

        // break if crashed
        if (flying.done)
        {
            break;
        }
        i++;
    }

    printf("\nMission Finished.\n");

    // landing
    printf("Landing.\n");
    flying.land();
    return 0;
}

