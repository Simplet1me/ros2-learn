#include <iostream>  
#include <vector>  
#include <Eigen/Dense>  

struct Motion {  
    Eigen::Vector2f position;  // 当前的位置  
    float Vmax;                 // 最大速度  
    float amax;                // 最大加速度  
    Eigen::Vector2f velocity;   // 当前速度  初始化为0

    Motion(Eigen::Vector2f start, float maxSpeed, float maxAcceleration)  
        : position(start), Vmax(maxSpeed), amax(maxAcceleration), velocity(Eigen::Vector2f::Zero()) {}  


    //前进参数
    void moveAlongPath(const std::vector<Eigen::Vector2f>& path) {  
        //遍历路径
        for (size_t i = 0; i < path.size() - 1; ++i) {  

            //向量起点和中点，向量起点为i中点是i+1
            //即当前点到下一个点的向量
            Eigen::Vector2f start = path[i];  
            Eigen::Vector2f end = path[i + 1];  

            // 计算当前路径段的方向和单位向量  
            Eigen::Vector2f direction = end - start;  
            //距离取模
            float distance = direction.norm();  

            //如果向量的模大于0 返回向量的模，否则就是0模
            Eigen::Vector2f unitDirection = distance > 0 ? direction.normalized() : Eigen::Vector2f::Zero();  

            // 如果不是最后一段，计算下一个目标点来判断曲率  
            Eigen::Vector2f nextDirection;  
            if (i < path.size() - 2) {  
                Eigen::Vector2f nextEnd = path[i + 2]; // 下一个目标  
                //下一段向量 = 下个终点 - 当前终点
                nextDirection = nextEnd - end;  
            } else {  
                nextDirection = end - start; // 如果是最后一段，设为当前方向  
            }  

            // 计算曲率并判断是否减速  
            float curvature = calculateCurvature(direction, nextDirection);  
            float corneringFactor = (curvature > 0.1f) ? 0.5f : 1.0f; // 曲率阈值，自定义，太高则减速  

            // 动态调整目标速度  = 单位向量 * 最大速度 * 曲率阈值
            Eigen::Vector2f targetVelocity = unitDirection * Vmax * corneringFactor;  

            // 加速到目标速度  
            float timeToAcc = (targetVelocity - velocity).norm() / amax;  //加速所需时间，速度差/最大加速度
            if (timeToAcc > 0) {  
                accelerate(timeToAcc, targetVelocity);  
            }  

            // 移动到当前路径段结束点  
            moveTowards(end);  

            // 如果是最后一段，减速到0  
            if (i == path.size() - 2) {  
                decelerateToStop();  
            }  
        }  
    }  

private:  
    //加速
    void accelerate(float timeToAcc, const Eigen::Vector2f& targetVelocity) {  
        Eigen::Vector2f acceleration = (targetVelocity - velocity).normalized() * amax;  

        velocity += acceleration * timeToAcc;  

        // 限制速度不超过最大速度  
        if (velocity.norm() > Vmax) {  
            velocity.normalize();  
            velocity *= Vmax;  
        }  
    }  

    void moveTowards(const Eigen::Vector2f& end) {  
        // 利用当前速度更新位置  
        float deltaTime = 1.0f; // 时间步长  
        position += velocity * deltaTime;  

        // 输出当前位置  
        std::cout << "Moving to: (" << position.x() << ", " << position.y() << ")\n";  
    }  

    void decelerateToStop() {  
        velocity.setZero(); // 将速度设为0  
        std::cout << "Stopped at: (" << position.x() << ", " << position.y() << ")\n";  
    }  

    //曲率计算 需要输入两段向量
    float calculateCurvature(const Eigen::Vector2f& direction, const Eigen::Vector2f& nextDirection) {  
        // 计算曲率 = (dx1 * dy2 - dy1 * dx2) / (|v1| * |v2|) 的值相关  
        float dx1 = direction.x();  
        float dy1 = direction.y();  
        float dx2 = nextDirection.x();  
        float dy2 = nextDirection.y();  
        
        // 曲率公式计算  
        return std::abs(dx1 * dy2 - dy1 * dx2) / (direction.norm() * nextDirection.norm() + 1e-6); // 避免除以零  
    }  
};  

int main() {  
    Eigen::Vector2f start(0, 0);  
    float maxSpeed = 5.0f;  
    float maxAcceleration = 2.0f;  
    
    //初始化motion类，参数； 起点，最大速度，最大加速度
    Motion motion(start, maxSpeed, maxAcceleration);  

    //起点，手动模拟路径
    std::vector<Eigen::Vector2f> path = {  
        start,  
        Eigen::Vector2f(3, 2),  
        Eigen::Vector2f(6, 5),  
        Eigen::Vector2f(8, 3),  
        Eigen::Vector2f(10, 10)  
    };  
    //沿路径前进
    motion.moveAlongPath(path);  

    return 0;  
}