/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <Eigen/Eigen>

#include <ros/ros.h>
#include <mavros_msgs/State.h>//subs
#include <mavros_msgs/ExtendedState.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/PositionTarget.h>//pubs
#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/CommandBool.h> //services
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>

#include <Tools.h>

using namespace std;
using namespace Eigen;

class Listener
{
    private:

    public:
        // mavros states
        mavros_msgs::State flight_state;
        mavros_msgs::ExtendedState flight_estate;
        
        Vector3d P_E, V_E;

        void stateCb(const mavros_msgs::State::ConstPtr &);
        void estateCb(const mavros_msgs::ExtendedState::ConstPtr &);
        void posCb(const geometry_msgs::PoseStamped::ConstPtr &);
        void velCb(const geometry_msgs::TwistStamped::ConstPtr &);
};

/*
// Basic functions to mavros
*/
class RosClass
{
    private:
        // ros
        ros::NodeHandle nh_;
        ros::Subscriber state_sub_, exstate_sub_, pos_sub_, vel_sub_;
        ros::Publisher pos_pub_, raw_pub_;
        ros::ServiceClient arming_client_, land_client_, set_mode_client_;
        ros::Rate rate;

        Listener listener_;  // listen drone states from mavros, handle the raw data.

        // drone states
        States state;
        // waypoints
        Vector3d Start, End;
        double LaunchHgt_;

        // control parameters
        int Freq_;
        double h_;

        States get_state_(void);
        void crashed_();

        // fcu modes
        bool setArm_(void);
        bool setLand_(void);
        bool setMode_Offboard_(void);

    public:
        bool done;

        // init ros node
        RosClass(ros::NodeHandle *nodehandle, int FREQ);
        // init variables
        void init(double HGT = 2.0);

        //basic missions
        States launch(void);
        States step(double double_n, Vector3d vec3_n, string mode);
        void land(void);
};

