import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
import os

import launch_ros.parameter_descriptions
def generate_launch_description():
    #获取默认urdf路径 
    urdf_package_path = get_package_share_directory('robot_description')
    default_urdf_path = os.path.join(urdf_package_path,'urdf','robot.urdf')
    default_rviz_config_path = os.path.join(urdf_package_path,'config','display_robot_model.rviz')
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name = 'model',default_value = str(default_urdf_path),description = '加载的模型文件路径'
    )

    command_result = launch.substitutions.Command(['cat ',launch.substitutions.LaunchConfiguration('model')])
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(command_result,value_type=str)

    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description':robot_description_value}]
    )

    action_joint_state_publisher = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher'
    )

    action_rviz_node = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', default_rviz_config_path]
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path,
        action_robot_state_publisher,
        action_joint_state_publisher,
        action_rviz_node
    ])