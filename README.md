# large scale plan and controls

A large scale planner and corresponding controller for quadrotor.



## Run the Code

### run the code

* clone the repo in your catkin workspace

  * mavros should be installed in this workspace.

  ```
  cd ~/catkin_ws/src/		# go into your catkin workspace
  git clone https://github.com/arclab-hku/largescale_plannctrl.git
  ```

* build the ros package

  ```
  cd ~/catkin_ws/		# go into your catkin workspace
  catkin build plannctrl
  ```

* source bash file & launch

  ```
  source devel/setup.bash
  roslaunch plannctrl ctrlEnv.launch
  ```

* set your way-points in `src/waypoints.txt`

  * The first line of the file is the number of way-points. The rest are the x-y-z coordinate of the way-points.
  
* source bash file & run

  ```
  # open a new terminal
  cd ~/catkin_ws/		# go into your catkin workspace
  source devel/setup.bash
  cd src/largescale_plannctrl/src		# go into folder with waypoints.txt
  rosrun plannctrl track_node
  ```
  
* setting parameters: parameters can be set after rosrun

  * the first argument is maximum velocity, the second is acceleration

  ```
  rosrun plannctrl track_node 15.0 2.0
  ```

  * the default maximum velocity is `15.0`, default acceleration is `2.0`.
  * the path for reading way points can be set in `include/planners/wayp_reader.cpp`



### read and log

* read way points
  * Set the way points in the `src/waypoints.txt`. 
  * The first line of the file is the number of way-points. The rest are the x-y-z coordinate of the way-points.



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

### src/

This folder includes all c++ main codes.

