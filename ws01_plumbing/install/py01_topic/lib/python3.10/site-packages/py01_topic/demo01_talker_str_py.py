import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Talker(Node):
    def __init__(self):
        self.count = 0
        super().__init__("talker_node_py")
        self.get_logger().info("发布方创建(python)")
        self.publisher =  self.create_publisher(String,"chatter",10)
        self.timer = self.create_timer(1.0,self.on_timer)
    
    def on_timer(self):
        message =String()
        message.data = "Helloworld(python)!" + str(self.count)
        self.publisher.publish(message)
        self.count += 1
        self.get_logger().info("发布的数据是:%s" % message.data)


def main():
    rclpy.init()
    rclpy.spin(Talker())
    rclpy.shutdown()


if __name__ == '__main__':
    main()