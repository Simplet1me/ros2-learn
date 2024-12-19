import launch
import launch_ros

import launch_ros.parameter_descriptions
def generate_launch_description():
    node01 = launch_ros.actions.Node(
        package='cpp01_png_sreach',
        executable='demo01_map_pub',
    )

    rviz = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
    )

    return launch.LaunchDescription([
        node01,
        rviz
    ])