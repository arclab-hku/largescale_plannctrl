# large scale plan and controls

A large scale planner and corresponding controller for quadrotor.



## Run the Code

### run the code

* clone the repo in your catkin workspace

  * mavros should be installed in this workspace.

* set your way-points in `src/waypoints.txt`

  * The first line of the file is the number of way-points. The rest are the x-y-z coordinate of the way-points.

* build the ros package

  ```
  cd ~/catkin_ws/
  catkin build plannctrl_fast 
  ```

* source bash file

  ```
  source devel/setup.bash
  ```

* launch & run

  ```
  roslaunch plannctrl_fast ctrlEnv.launch
  # open a new terminal
  rosrun plannctrl_fast track_node
  ```
  
* setting parameters: parameters can be set after rosrun

  * the first argument is maximum velocity, the second is acceleration

  ```
  rosrun plannctrl_fast track_node 15.0 2.0
  ```

  * the default maximum velocity is `15.0`, default acceleration is `2.0`.



### read and log

* read way points
  * Set the way points in the `src/waypoints.txt`. 
  * The first line of the file is the number of way-points. The rest are the x-y-z coordinate of the way-points.
* log drone states and reference trajectory
  * the path of the log files is set in `include/logs/log_flight.cpp`. 
  * this class logs the drone states and the reference for every time step.
  * if you don't need the logger, you can comment the `logger` lines in the `src/run_plannctrl.cpp` file. 
  * the logs can be plot out by the code `logs/handle.m` in matlab.



## the repos

### launch/

This folder includes all launch files.

The `ctrlEnv.launch` file launches MAVROS, PX4 SITL, Gazebo and also the Gazebo environment including ground plane and iris model.

Roslaunch the launch file before rosrun the codes.

### include/

This folder includes all modules for c++, including:

* simulation and off-board flight environment `offboard_env/`) with corresponding call backs(`call_states`);
* controllers and planners;
* tracking references;
* flight logs.

### src/

This folder includes all c++ main codes.

