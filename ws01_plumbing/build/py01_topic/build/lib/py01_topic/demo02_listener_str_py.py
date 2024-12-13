import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Listener(Node):
    def __init__(self):
        super().__init__("Listener_node_py")
        self.get_logger().info("订阅方节点创建")
        self.subscription = self.create_subscription(String,"chatter",self.do_cb,10)


    def do_cb(self,msg):
        self.get_logger().info("订阅的数据:%s" % msg.data)


def main():
    rclpy.init()
    rclpy.spin(Listener())
    rclpy.shutdown()

if __name__ == '__main__':
    main()