# SSY236

## Devcontainer

ROS 2 Humble with the TIAGo simulation (Gazebo Classic) runs in a devcontainer, so nothing needs to be installed or built on the host.

**Requirements:** Docker (running), VS Code with the *Dev Containers* extension, an X11 session (for the Gazebo/RViz windows).

1. Open this folder in VS Code and run **Dev Containers: Reopen in Container** (the first build takes a few minutes).
2. In the container terminal, build and launch manually, eg.:
   ```
   cd 02
   colcon build
   source install/setup.bash
   ros2 launch world_perception tiago_gazebo.launch.py is_public_sim:=True base_type:=omni_base world_name:=custom_world
   ```