# large scale plan and control

A large scale planner and corresponding controller for quadrotor.



## Run the Code

### run the code

* clone the repo under `~/`

* set your way-points in `run/waypoints.txt`

  * The first line of the file is the number of way-points. The rest are the x-y-z coordinate of the way-points.

* source bash file

  ```
  # go into the folder
  source devel/setup.bash
  ```

* launch mavros & gazebo

  ```
  roslaunch plannctrl_fast ctrlEnv.launch
  ```
  
* run the tracking node

  ```
  # open a new terminal
  cd ~/run/
  ./track_node
  ```

  * (optional) setting parameters: parameters can be set after `./track_node`

  * the first argument is maximum velocity, the second is acceleration

    ```
    ./track_node 10.0 2.0
    ```

  * the default maximum velocity is `15.0`, default acceleration is `2.0`.


