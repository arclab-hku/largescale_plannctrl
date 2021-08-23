/*
Description: Generate trajectory for large scale waypoints. 
Author: XIE Yuhan
Email: yuhanxie@connect.hku.hk
Updated: 28th. Jul. 2021
*/
#pragma once
#include <planners/trajgen.h>

TrajectoryGenerator::TrajectoryGenerator(
    // Vector3d START, 
    double MAXVEL,
    double MAXACC,
    double MAXCORVEL):
        cornerTraj_(MAXCORVEL),
        strghtTraj_(MAXCORVEL, MAXVEL-1.0, MAXACC)
{
    // constants
    MaxVel_ = MAXVEL;
    MaxAcc_ = MAXACC;
    MaxCnrVel_ = MAXCORVEL;

    // read waypoints from txt
    waypoints_ = waypRead_.read();
    index_wayp_ = 0;

    // initialize
    start_pt_ << 0.0, 0.0, 0.0;
    time_offset_ = 0.0;
    trajFinished = 0;
    starting = 1;
    ending = 0;

    LaunchHht = waypoints_(2, 0);       // launch height
}

void TrajectoryGenerator::initial_generate(Vector3d START)
{
    start_pt_ = START;
    // make trajectory for initial
    starting = 1;
    makeNxtTraj_();
    starting = 0;
}

Vector3d TrajectoryGenerator::getNewPoint_ (Vector3d start, Vector3d dirct, double length)
{
    Vector3d result;
    result = start + length * dirct;
    return result;
}

void TrajectoryGenerator::segment_(Vector3d start, Vector3d end, double &distc, Vector3d &dirct)
{
    Vector3d diff = end - start;
    distc = diff.norm();                 //distance
    dirct = 1.0/distc* diff;             // direction
}

// generate a straight trajectory
void TrajectoryGenerator::straightGen_()
{
    currentTraj_ = 1;
    time_traj_ = strghtTraj_.generate(start_pt_, end_pt_);
}

// generate a corner polynomial trajectory by PolyTrajGenerator
void TrajectoryGenerator::cornerGen_(Vector3d start_dirct, Vector3d end_dirct)
{
    // printf ("\nmaking a corner\n");
    currentTraj_ = 0;

    // get matrix of wayps
    MatrixXd wayps(3, q_crnWayps.size());

    wayps.col(0) = q_crnWayps.front();
    q_crnWayps.pop();
    int count = 1;

    // printf("waypoints for generation\n");
    while (!q_crnWayps.empty()) 
    {
        Vector3d wpi = q_crnWayps.front();

        // make sure two waypoints not be too close.
        if ((wpi - wayps.col(count-1)).norm()> 0.5)
        {
            // printf("count%d\n",count);
            wayps.col(count) = wpi;
            // cout <<wpi<<endl<<endl;
            count++;
        }

        // delete the first
        q_crnWayps.pop();
    }

    // initial & final state
    Vector3d iVel, iAcc, fVel, fAcc;
    iVel.setZero();
    iAcc.setZero();
    fVel.setZero();
    fAcc.setZero();
    if (!starting)
    {
        // printf("not starting\n");
        iVel = MaxCnrVel_ * start_dirct;
        iAcc = MaxAcc_ * start_dirct;
    }
    if (!ending)
    {
        // printf("not ending\n");
        fVel = MaxCnrVel_ * end_dirct;
        fAcc = MaxAcc_ * end_dirct;
    }

    // printf("initial&final vel&acc\n");
    // cout<<iVel<<endl<<iAcc<<endl<<fVel<<endl<<fAcc<<endl;

    // generate
    time_traj_ = cornerTraj_.generate(
        wayps, count,          // number of waypoints
        iVel, iAcc,
        fVel, fAcc
    );
    end_pt_ = wayps.col(count - 1);
}

/*
// generate a trajectory from start point go by waypoints_[i_wp].
// return whether a corner trajectory is generated.
*/
void TrajectoryGenerator::makeNxtTraj_()
{
    // get distance&direction from start point to waypoints_[i_wp]
    Vector3d dirct;
    double distc;
    segment_(start_pt_, waypoints_.col(index_wayp_), distc, dirct);     // go through
    
    while (distc == 0)
    {
        start_pt_ = waypoints_.col(index_wayp_);
        printf("\nwaypoint %d path generated\n", index_wayp_);
        printf("(%.2f, %.2f, %.2f)\n", waypoints_(0,index_wayp_), waypoints_(1,index_wayp_), waypoints_(2,index_wayp_));
        index_wayp_++;
        segment_(start_pt_, waypoints_.col(index_wayp_), distc, dirct);     // go through
    }

    if (distc > CnrMaxSeg+0.1 && !starting)
    {                                   //////////////////////// straight next
        // do not update i_wp, cause waypoint[i_wp] has not passed.
        end_pt_ =  waypoints_.col(index_wayp_) - CnrMaxSeg * dirct;
        straightGen_();
        return ;
    }
    else                             //////////////////////// corner next
    {   
        // corner segment for start
        double corner_seg = CnrSeg;
        if (distc < CnrSeg*3)       // distance from start to first wayp
            corner_seg = CnrSeg/2;

        // directions for corner traj. gen.
        Vector3d start_dirct = dirct;

        // collecting waypoints
        q_crnWayps.push(start_pt_);

        // is starting
        if (starting)
        {
            // push starting point end
            q_crnWayps.push(getNewPoint_(start_pt_, dirct, corner_seg)); 

            if (distc > CnrMaxSeg*2)
            {   // first waypoint couple distance is long
                q_crnWayps.push(getNewPoint_(start_pt_, dirct, CnrMaxSeg));
                cornerGen_(start_dirct, dirct);
                return;
            }
            // else continue corner
        }

        bool making_corner = 1;
        while (making_corner && index_wayp_ < waypRead_.N)
        {
            // push start of a corner       
            Vector3d start_a_corner = getNewPoint_(waypoints_.col(index_wayp_), -dirct, corner_seg);
            if ((start_a_corner - q_crnWayps.back()).norm()>0.4)  // make sure the distance
            {
                q_crnWayps.push(start_a_corner); 
            }

            // end of traj
            if (index_wayp_ == (waypRead_.N-1))
            {   
                q_crnWayps.push(waypoints_.col(index_wayp_));
                ending = 1;
                printf("\nlast waypoint %d ", index_wayp_+1);
                printf("(%.2f, %.2f, %.2f) path generated\n", waypoints_(0,index_wayp_), waypoints_(1,index_wayp_), waypoints_(2,index_wayp_));
                index_wayp_ = waypRead_.N;
                cornerGen_(start_dirct, dirct);
                return ;
            }

            // next waypoint segment
            segment_(waypoints_.col(index_wayp_), waypoints_.col(index_wayp_+1), distc, dirct);     // get distance&direction from i_wp to i_wp+1

            // push the end of a corner       
            if (distc >= CnrSeg*3)          // re-distribute corner segment
                corner_seg = CnrSeg;
            else
                corner_seg = distc/3;
            q_crnWayps.push(getNewPoint_(waypoints_.col(index_wayp_), dirct, corner_seg));

            // waypoint[i_wp] is passed now.
            printf("waypoint %d ", index_wayp_+1);
            printf("(%.2f, %.2f, %.2f) path generated\n", waypoints_(0,index_wayp_), waypoints_(1,index_wayp_), waypoints_(2,index_wayp_));
            index_wayp_++;

            // stop making a corner
            if (distc >= CnrMaxSeg*2)
                making_corner = 0;
        }

        q_crnWayps.push(getNewPoint_(waypoints_.col(index_wayp_-1), dirct, CnrMaxSeg));       // end of all corner
        cornerGen_(start_dirct, dirct);
        return ;
    }
}

void TrajectoryGenerator::get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d)
{
    if (timee <= time_offset_ + time_traj_)
    {
        // current traj piece not finished yet.
        if (currentTraj_)
        {
            strghtTraj_.get_desire(timee - time_offset_, p_d, v_d, a_d);
        }
        else 
        {
            cornerTraj_.get_desire(timee - time_offset_, p_d, v_d, a_d);
        }
        return ;
    }
    // current traj piece finished

    if (ending || index_wayp_ == waypRead_.N)
    {
        trajFinished = 1;
        p_d = waypoints_.col(waypRead_.N-1);
        v_d << 0.0,0.0,0.0;
        a_d << 0.0,0.0,0.0;
        return;
    }

    // update time offset
    time_offset_ += time_traj_;

    // generate new traj piece
    start_pt_ = end_pt_;
    makeNxtTraj_();

    if (currentTraj_)
    {
        strghtTraj_.get_desire(timee - time_offset_, p_d, v_d, a_d);
    }
    else 
    {
        cornerTraj_.get_desire(timee - time_offset_, p_d, v_d, a_d);
    }
    return ;
}

/*
// Generate Straight Trajectory
*/
StraightTrajGenerator::StraightTrajGenerator(double MINVEL, double MAXVEL, double MAXACC)
{
    MinVel_ = MINVEL;
    MaxVel_ = MAXVEL;
    AccRate_ = MAXACC;
    //
    MaxAccTime_ = (MaxVel_ - MinVel_) / AccRate_;
    MaxAccDistc_ = MinVel_ * MaxAccTime_ +0.5 * AccRate_ * pow(MaxAccTime_, 2);
}

double StraightTrajGenerator::generate(Vector3d start, Vector3d end)
{
    start_pt_ = start;
    end_pt_ = end;

    double distc = (end - start).norm();        // distance
    dirct_ = (end - start)/distc;                           // direction

    // allocate time
    if (distc > MaxAccDistc_ * 2)
    {
        // accelerate
        accDistc_ = MaxAccDistc_;
        accTime_ = MaxAccTime_;
        // constant velocity
        constDistc_ = distc - MaxAccDistc_*2;
        constTime_ = constDistc_/MaxVel_;
        velMax_ = MaxVel_;
    }
    else
    {
        // accelerate
        accDistc_ = distc / 2;
        accTime_ = (-MinVel_ + sqrt(MinVel_*MinVel_+2*AccRate_*accDistc_)) / AccRate_;
        velMax_ = MinVel_ + accTime_ * AccRate_;
        // constant velocity
        constDistc_ = 0.0;
        constTime_ = 0.0;
    }

    return accTime_+accTime_ + constTime_;

}

void StraightTrajGenerator::get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d)
{
    if (timee < accTime_)
    {
        // accel
        a_d = AccRate_ * dirct_;
        v_d = (MinVel_ + AccRate_*timee) * dirct_;
        p_d = start_pt_ + (MinVel_*timee + 0.5*AccRate_*pow(timee,2)) * dirct_;
        return;
    }
    timee -=accTime_;
    if (timee < constTime_)
    {
        // const vel
        a_d << 0.0,0.0,0.0;
        v_d = velMax_*dirct_;
        p_d = start_pt_ + (accDistc_ + velMax_*timee) * dirct_;
        return;
    }
    timee -=constTime_;
    if (timee < accTime_)
    {
        // de-accel;
        a_d = -AccRate_ * dirct_;
        v_d = (velMax_ - AccRate_*timee) * dirct_;
        p_d = start_pt_ + (accDistc_ + constDistc_ + velMax_*timee - 0.5*AccRate_*pow(timee,2)) * dirct_;
        return;
    }
    p_d = end_pt_;
    v_d = MinVel_ * dirct_;
    a_d = AccRate_ * dirct_;
    return;
}

/*
// Generate Polynomial Trajectory by minimum-jerk
*/
PolyTrajGenerator::PolyTrajGenerator(double MAXVEL, double MAXACC)
{
    MaxVel = MAXVEL;
    MaxVelCal = MAXVEL;
    MaxAcc = MAXACC;
}

// allocate time for waypoints
VectorXd PolyTrajGenerator::allocateTime(const MatrixXd &wayPs,
             double vel,
             double acc)
{
    int N = (int)(wayPs.cols()) - 1;
    VectorXd durations(N);
    if (N > 0)
    {
        Eigen::Vector3d p0, p1;
        double dtxyz, D, acct, accd, dcct, dccd, t1, t2, t3;

        for (int k = 0; k < N; k++)
        {
            p0 = wayPs.col(k);
            p1 = wayPs.col(k + 1);
            D = (p1 - p0).norm();       // distance

            acct = vel / acc;                   // accelerate time
            accd = (acc * acct * acct / 2);     // accelerate distance
            dcct = vel / acc;                   // de-accelerate time
            dccd = acc * dcct * dcct / 2;       // de-accelerate distance

            if (D < accd + dccd)
            {
                t1 = sqrt(acc * D) / acc;
                t2 = (acc * t1) / acc;
                dtxyz = t1 + t2;
            }
            else
            {
                t1 = acct;
                t2 = (D - accd - dccd) / vel;
                t3 = dcct;
                dtxyz = t1 + t2 + t3;
            }

            durations(k) = dtxyz;
        }
    }

    return durations;
}

double PolyTrajGenerator::generate(
    MatrixXd waypoints, 
    int num,
    Vector3d iVel,
    Vector3d iAcc,
    Vector3d fVel,
    Vector3d fAcc)
{
    MatrixXd wayps = waypoints.block(0, 0, 3, num);

    // intial & finial state
    Matrix3d iS, fS;        // xyz * pva        
    iS.setZero();
    fS.setZero();
    iS.col(0) << wayps.col(0);       // p
    fS.col(0) << wayps.col(num - 1);
    iS.col(1) << iVel;       // v
    fS.col(1) << fVel;
    iS.col(2) << iAcc;       // a
    fS.col(2) << fAcc;

    // set initial & finial waypoints
    jerkOpt.reset(iS, fS, num - 1);

    // time allocate
    ts = allocateTime(wayps, MaxVelCal, MaxAcc);

    // generate & get trajectory
    jerkOpt.generate(wayps.block(0, 1, 3, num - 2), ts);
    jerkOpt.getTraj(minJerkTraj);

    // check maximum velocity
    // while (!minJerkTraj.checkMaxVelRate(MaxVel))
    // {
    //     printf("maximum velocity %.2f\n", minJerkTraj.getMaxVelRate());

    //     // re-allocate time
    //     MaxVelCal = MaxVelCal - 0.5;
    //     ts = allocateTime(waypoints, MaxVelCal, MaxAcc);

    //     // generate&get trajectory
    //     jerkOpt.generate(waypoints.block(0, 1, 3, num - 2), ts);
    //     jerkOpt.getTraj(minJerkTraj);
    // }
    // printf("maximum velocity %.2f\n", minJerkTraj.getMaxVelRate());

    return minJerkTraj.getTotalDuration();
}

void PolyTrajGenerator::get_desire(double timee, Vector3d &p_d, Vector3d &v_d, Vector3d &a_d)
{
    p_d = minJerkTraj.getPos(timee);
    v_d = minJerkTraj.getVel(timee);
    a_d = minJerkTraj.getAcc(timee);
}
