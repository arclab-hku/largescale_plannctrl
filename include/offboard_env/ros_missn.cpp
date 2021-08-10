/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include <offboard_env/ros_missn.h>

RosClass::RosClass(ros::NodeHandle* nodehandle, int FREQ):
        nh_(*nodehandle), 
        rate(FREQ)
{
    // subscribers
    //// mavros states
    state_sub_ = nh_.subscribe<mavros_msgs::State>("mavros/state", 10, &Listener::stateCb, &listener_);
    exstate_sub_ = nh_.subscribe<mavros_msgs::ExtendedState>("mavros/extended_state", 10, &Listener::estateCb, &listener_);
    //// control states
    pos_sub_ = nh_.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 1, &Listener::posCb, &listener_);
    vel_sub_ = nh_.subscribe<geometry_msgs::TwistStamped>("mavros/local_position/velocity_local", 1, &Listener::velCb, &listener_);

    // publishers
    pos_pub_ = nh_.advertise<mavros_msgs::PositionTarget>("mavros/setpoint_raw/local", 1);
    raw_pub_ = nh_.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude", 1);

    // fcu modes
    arming_client_ = nh_.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    land_client_ = nh_.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");
    set_mode_client_ = nh_.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");

    // control frequency
    Freq_ = FREQ;
    h_ = 1.0 / FREQ;
}

void RosClass::init(double HGT)
{
    LaunchHgt_ = HGT;
}

States RosClass::launch(void)
{
    get_state_();
    Start << state.P_E(0), state.P_E(1), LaunchHgt_;

    mavros_msgs::PositionTarget takeoff;
    takeoff.type_mask = 8 + 16 + 32 + 64 + 128 + 256 + 2048;
    takeoff.position.x = Start(0);
    takeoff.position.y = Start(1);
    takeoff.position.z = Start(2);
    takeoff.yaw = 0;

    // wait for arm and offboard mode.
    printf("Waiting for arm and OFFBOARD mode.\n");
    while (!listener_.flight_state.armed && ros::ok())
    {
        setArm_();
        ros::spinOnce();
        rate.sleep();
    }    
    while (listener_.flight_state.mode != "OFFBOARD" && ros::ok()) 
    {
        pos_pub_.publish(takeoff);
        setMode_Offboard_();
        ros::spinOnce();
        rate.sleep();
    }
    printf("Armed. OFFBOARD mode.\n");

    // take off
    while (ros::ok())
    {
        Vector3d distance = Start - listener_.P_E;
        if (distance.norm() < 1.0)
        {
            break;
        }
        pos_pub_.publish(takeoff);
        ros::spinOnce();
        rate.sleep();
    }

    get_state_();

    return state;
}

States RosClass::step(double double_n, Vector3d vec3_n, string mode)
{
    // step
    if (mode == "yaw_n_position")
    {
        mavros_msgs::PositionTarget p_sp;
        p_sp.type_mask = 8 + 16 + 32 + 64 + 128 + 256 + 2048;
        p_sp.position.x = vec3_n(0);
        p_sp.position.y = vec3_n(1);
        p_sp.position.z = vec3_n(2);
        p_sp.yaw = double_n;

        pos_pub_.publish(p_sp);
    }
    else if (mode == "yaw_n_velocity")
    {
        mavros_msgs::PositionTarget v_sp;
        v_sp.coordinate_frame = 1;
        v_sp.type_mask = 1 + 2 + 4 + 64 + 128 + 256 + 2048;
        v_sp.velocity.x = vec3_n(0);
        v_sp.velocity.y = vec3_n(1);
        v_sp.velocity.z = vec3_n(2);
        v_sp.yaw = double_n;

        pos_pub_.publish(v_sp);
    }

    ros::spinOnce();
    rate.sleep();

    get_state_();

    //crashed_();

    return state;
}

void RosClass::land(void)
{
    // get_state_();
    // End << state.P_E(0), state.P_E(1), 1.0;

    // // fly to land point
    // mavros_msgs::PositionTarget land;
    // land.type_mask = 8 + 16 + 32 + 64 + 128 + 256 + 2048;
    // land.position.x = End(0);
    // land.position.y = End(1);
    // land.position.z = End(2);
    // land.yaw = 0;

    // pos_pub_.publish(land);
    // while (ros::ok())
    // {
    //     Vector3d distance = End - listener_.P_E;
    //     if (distance.norm() < 0.4)
    //     {
    //         break;
    //     }
    //     pos_pub_.publish(land);
    //     ros::spinOnce();
    //     rate.sleep();
    // }

    printf("Setting Land Mode.\n");

    // set land mode
    bool landed = setLand_();
    while (ros::ok() && ! landed && listener_.flight_state.armed)
    {
        landed = setLand_();
        ros::spinOnce();
        rate.sleep();
    }

    printf("Landed.\n");
}

States RosClass::get_state_(void)
{
    state.P_E = listener_.P_E;
    state.V_E = listener_.V_E;
    return state;
}

// void RosClass::crashed_()
// {
//     double z = state.P_E(2);
//     if (z<0.1)
//     {
//         printf("Crashed at height %.2f.\n", z);
//         done =  true;
//     }
//     else
//     {
//         done = false;
//     }
// }

/*
fcu modes
*/

bool RosClass::setArm_()
{
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    if (arming_client_.call(arm_cmd) && arm_cmd.response.success)
    {
        //ROS_INFO("Vehicle armed");
        return true;
    }
    return false;
}

bool RosClass::setLand_()
{
    mavros_msgs::CommandTOL land_cmd;
    land_cmd.request.altitude = 0;
    land_cmd.request.latitude = 0;
    land_cmd.request.longitude = 0;
    land_cmd.request.min_pitch = 0;
    land_cmd.request.yaw = 0;

    if (land_client_.call(land_cmd) && land_cmd.response.success)
    {
        //ROS_INFO("Vehicle landed");
        return true;
    }
    return false;
}

bool RosClass::setMode_Offboard_()
{
    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    if (set_mode_client_.call(offb_set_mode) && offb_set_mode.response.mode_sent)
    {
        //ROS_INFO("Offboard enabled");
        return true;
    }
    return false;
}

// listener
void Listener::stateCb(const mavros_msgs::State::ConstPtr& msg)
{
    flight_state = *msg;
}
void Listener::estateCb(const mavros_msgs::ExtendedState::ConstPtr& msg)
{
    flight_estate = *msg;
}

void Listener::posCb(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    geometry_msgs::PoseStamped pose = *msg;
    // position
    P_E(0) = pose.pose.position.x;
    P_E(1) = pose.pose.position.y;
    P_E(2) = pose.pose.position.z;
}

void Listener::velCb(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    geometry_msgs::TwistStamped velocity = *msg;
    // linear velocity
    V_E(0) = velocity.twist.linear.x;
    V_E(1) = velocity.twist.linear.y;
    V_E(2) = velocity.twist.linear.z;
}
