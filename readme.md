# ROS2 PCAN Driver for MacOSX

based on http://www.mac-can.com/

## Build
1. Download and install PCBUSB library from http://www.mac-can.com/
2. Build
```
colcon build --packages-select macpcan
```
3. Run
```
source install/setup.bash
ros2 run macpcan mac_pcan
```