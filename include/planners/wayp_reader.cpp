#include<planners/wayp_reader.h>

WayPointsReader::WayPointsReader()
{
    infile.open("waypoints.txt");
}

MatrixXd WayPointsReader::read()
{
    infile>>N;

    MatrixXd waypoints(3, N);
    Vector3d tmp;

    waypoints.col(0).setZero();

    int i = 0, count = 0;
    double x, y, z;
    while (infile>>x>>y>>z)
    {
        // printf("waypoint %d: %.2f, %.2f, %.2f\n",i,x,y,z);
        if (i >= N)
        {
            printf("More waypoints than setting!\n");
            printf("Using only first %d waypoints.\n\n", N);
            break;
        }

        // give in waypoint (x, y, z)
        tmp << x, y, z;

        if (count == 0)
        {
            waypoints.col(count) << tmp;
            count++;
        }
        else if ((tmp - waypoints.col(count-1)).norm() <= 0.5)
        {
            printf("Distance of waypoints %d and %d is too close!\n\n", i, i+1);
        }
        else
        {
            waypoints.col(count) << tmp;
            count++;
        }
        i++;
    }
    if (i < N)
    {
        printf("Less waypoints than setting!\n");
        printf("Setting last %d wapoints as origin point.\n", N-i);
    }

    N = count;
    return waypoints;
}
