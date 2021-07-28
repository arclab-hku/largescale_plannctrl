/*
Description: Run 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include<logs/log_flight.h>

LogFlight::LogFlight(string name0)
{
    time_t timep;
    time(&timep);

    string name = name0; //+ to_string(timep%100000);

    // states
    fp_posi = fopen(("/home/johanna/catkin_ws/src/large_scale_plannctrl/logs/" + name + "_posi.txt").c_str(), "w+");
    fp_velo = fopen(("/home/johanna/catkin_ws/src/large_scale_plannctrl/logs/" + name + "_velo.txt").c_str(), "w+");

    // desires
    fp_posid = fopen(("/home/johanna/catkin_ws/src/large_scale_plannctrl/logs/" + name + "_posid.txt").c_str(), "w+");
    fp_velod = fopen(("/home/johanna/catkin_ws/src/large_scale_plannctrl/logs/" + name + "_velod.txt").c_str(), "w+");
}

LogFlight::~LogFlight()
{
    // close all fp

    //// states
    fclose(fp_posi);
    fclose(fp_velo);

    //// desires
    fclose(fp_posid);
    fclose(fp_velod);
}

void LogFlight::states(States state)
{
    fprintf(fp_posi, "%.2f  %.2f  %.2f\n", state.P_E(0), state.P_E(1), state.P_E(2));
    fprintf(fp_velo, "%.2f  %.2f  %.2f\n", state.V_E(0), state.V_E(1), state.V_E(2));
}

void LogFlight::desires(Vector3d p, Vector3d v)
{
    fprintf(fp_posid, "%.2f  %.2f  %.2f\n", p(0), p(1), p(2));
    fprintf(fp_velod, "%.2f  %.2f  %.2f\n", v(0), v(1), v(2));
}