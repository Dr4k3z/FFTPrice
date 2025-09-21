#include <iostream>
#include <Eigen/Dense>

double dot_example() {
    Eigen::Vector2d a(1.0, 2.0), b(3.0, 4.0);
    return a.dot(b); // 11.0
}

double dot_example2() {
    Eigen::Vector2d a(1.0, 2.0), b(0.0, 1.0);
    return a.dot(b);
}

int main() {
    std::cout << dot_example() << std::endl;
    return 0;
}