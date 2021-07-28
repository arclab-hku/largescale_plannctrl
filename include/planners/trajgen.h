/*
Description: Generate trajectory for large scale waypoints. 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once

#include "planners/fast/traj_min_jerk.hpp"
#include <planners/wayp_reader.h>

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <Eigen/Eigen>
#include <stdlib.h>
#include <queue>

using namespace std;
using namespace Eigen;
using namespace min_jerk;

/*
// Generate Straight Trajectory
*/
class StraightTrajGenerator
{
    private:
        // initial params
        double MaxVel_, MinVel_, AccRate_;
        double MaxAccTime_, MaxAccDistc_;

        // for certain traj, to generate
        double accDistc_, constDistc_;
        double accTime_, constTime_;
        double velMax_;
        Vector3d dirct_, start_pt_, end_pt_;

    public:
        StraightTrajGenerator(
            double MINVEL=4.0,
            double MAXVEL=14.0,
            double MAXACC=4.0
        );

        double generate(
            Vector3d start, 
            Vector3d end);      // return total time
        void get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d);
};

/*
// Generate Polynomial Trajectory by minimum-jerk
*/
class PolyTrajGenerator
{
    private:
        double MaxVel, MaxVelCal, MaxAcc;

        JerkOpt jerkOpt;              // optimizer

        VectorXd allocateTime(const MatrixXd &wayPs, double vel, double acc);

    public:
        // Vector3d iVel, iAcc, fVel, fAcc;

        VectorXd ts;        // time for pieces
        double totalT;

        Trajectory minJerkTraj;       // optimal trajectory

        PolyTrajGenerator(double MAXVEL=4.0, double MAXACC=4.0);
        double generate(
            MatrixXd waypoints, 
            int num,        // number of waypoints
            Vector3d iVel,
            Vector3d iAcc,
            Vector3d fVel,
            Vector3d fAcc
        );
        void get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d);
};

/*
// Generate Trajectory by waypoints.txt
// return desire p, v, a, by time
*/
class TrajectoryGenerator
{
    private:
        double MaxVel_, MaxAcc_, MaxCnrVel_;

        // set waypoints
        MatrixXd waypoints_;    // pva * time
        int index_wayp_;        // waypoints_[index_wayp_] is to be passed next.

        // current generated traj
        bool currentTraj_;   // 0=corner, 1=straight
        Vector3d start_pt_, end_pt_;      //
        double time_traj_;          // totol time of current traj
        double time_offset_;    // start time of current in whole traj

        // params for staright
        Vector3d strght_dirct_;

        // params for corner
        double CnrMaxSeg = 7.0;     // preserve segment for corner
        double CnrSeg = 1.0;            // corner waypoint segment
        double CnrMaxVel = 4.0;     // initial & final vel 

        bool starting, ending;  // start & end wayp of whole traj has zero vel&ac

        WayPointsReader waypRead_;        // read waypoints from txt
        PolyTrajGenerator cornerTraj_;
        StraightTrajGenerator strghtTraj_;

        Vector3d getNewPoint_ (Vector3d start, Vector3d dirct, double length);
        void segment_(Vector3d start, Vector3d end, double &distc, Vector3d &dirct);
        // MaxtrixXd genCorWayp_(queue<Vector3d>& q_wayp, int Num);

        queue<Vector3d> q_crnWayps;   // waypoints for corner gen

        void straightGen_();
        void cornerGen_(Vector3d start_dirct, Vector3d end_dirct);
        
        // generate a trajectory from start point go by waypoints_[i_wp].
        void makeNxtTraj_();

    public:
        bool trajFinished;

        TrajectoryGenerator(
            double MAXVEL = 15.0,
            double MAXACC = 4.0,
            double MAXCORVEL = 4.0
        );

        // return desire p, v, a for current time
        void initial_generate(Vector3d START);
        void get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d);
};
