# ROS2
GUI publisher
# ROS2Gui
Creating custom GUI with Qt and ROS2

## How to Launch the GUI
1. [Install ROS2 Foxy](https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/). Make sure to setup your environment with:

        source /opt/ros/foxy/setup.bash

    > *NOTE:* You may want to add that line to your `~/.bashrc`

2. Create a colcon workspace (*Note:* Feel free to change `~/ws_ros2` to whatever absolute path you want):

        export COLCON_WS=~/ws_ros2/
        mkdir -p $COLCON_WS/src

3. Clone the required repositories and install any dependencies:

        cd $COLCON_WS/src
        git clone https://github.com/rahulmvjce/ROS2.git
        rosdep install --ignore-src --from-paths . -y

4. Configure and build the workspace
        colcon build --packages-select veh_interfaces
        colcon build
        source $COLCON_WS/install/setup.bash

6. Launch the GUI using the following command:

        ros2 launch qtros2 gui.launch.py
