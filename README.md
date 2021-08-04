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



## Install Mavros in your catkin workspace

[reference](https://dev.px4.io/v1.9.0/en/ros/mavros_installation.html)

Prerequsites: ROS, Gazebo, px4

```shell
## Install dependencies
sudo apt-get install python-catkin-tools python-rosinstall-generator -y

## Create catkin workspace
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin init
wstool init src

## 1. SInstall MAVLink
###we use the Kinetic reference for all ROS distros as it's not distro-specific and up to date
rosinstall_generator --rosdistro kinetic mavlink | tee /tmp/mavros.rosinstall

## 2. Install MAVROS from source using either released or latest version:
## Released/stable
rosinstall_generator --upstream mavros | tee -a /tmp/mavros.rosinstall

## 3. Create workspace & deps:
wstool merge -t src /tmp/mavros.rosinstall
wstool update -t src
rosdep install --from-paths src --ignore-src -y

## 4. Install GeographicLib datasets:
sudo ./src/mavros/mavros/scripts/install_geographiclib_datasets.sh

## 5. Build source
catkin build

# 6. Make sure that you use setup.bash or setup.zsh from workspace.
source devel/setup.bash
. devel/setup.bash
```



## Launch Gazebo with ROS Wrappers

To run SITL wrapped in ROS the ROS environment needs to be updated, then launch as usual:

```
cd <Firmware_clone>
DONT_RUN=1 make px4_sitl_default gazebo
source ~/catkin_ws/devel/setup.bash    
source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$(pwd)/Tools/sitl_gazebo
```

