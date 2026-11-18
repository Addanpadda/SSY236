FROM osrf/ros:humble-desktop

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        ros-humble-tiago-simulation \
        ros-humble-omni-base-gazebo \
        ros-humble-pal-gazebo-worlds \
        ros-humble-launch-pal \
        ros-humble-gazebo-ros-pkgs \
        ros-humble-gazebo-msgs \
        ros-humble-tf2-tools \
        python3-colcon-common-extensions \
        mesa-utils \
    && rm -rf /var/lib/apt/lists/*

# Non-root user (the devcontainer adjusts its UID to match the host user).
RUN useradd -m -u 1000 -s /bin/bash -G video dev \
    && echo "source /opt/ros/humble/setup.bash" >> /home/dev/.bashrc \
    && echo "source /usr/share/gazebo/setup.sh" >> /home/dev/.bashrc \
    && echo '[ -f install/setup.bash ] && source install/setup.bash' >> /home/dev/.bashrc

USER dev
