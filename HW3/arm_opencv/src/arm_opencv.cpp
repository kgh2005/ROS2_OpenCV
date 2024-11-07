#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const cv::Point CENTER(WIDTH/2, HEIGHT/2);
const int ARM1_LENGTH = 100;
const int ARM2_LENGTH = 80;

void drawRoboticArm(cv::Mat& image, double angle1, double angle2) {
    // 첫 번째 관절 위치 계산
    int x1 = CENTER.x + ARM1_LENGTH * cos(angle1);
    int y1 = CENTER.y + ARM1_LENGTH * sin(angle1);
    cv::Point joint1(x1, y1);

    // 두 번째 관절 위치 계산
    int x2 = x1 + ARM2_LENGTH * cos(angle1 + angle2);
    int y2 = y1 + ARM2_LENGTH * sin(angle1 + angle2);
    cv::Point joint2(x2, y2);

    // 배경을 검은색으로 초기화
    image = cv::Scalar(0, 0, 0);

    // 로봇 팔 그리기
    cv::circle(image, CENTER, 10, cv::Scalar(0, 0, 255), -1);  // 베이스 관절
    cv::line(image, CENTER, joint1, cv::Scalar(255, 255, 255), 3);  // 첫 번째 팔

    cv::circle(image, joint1, 8, cv::Scalar(0, 255, 0), -1);  // 중간 관절
    cv::line(image, joint1, joint2, cv::Scalar(255, 255, 255), 3);  // 두 번째 팔

    cv::circle(image, joint2, 6, cv::Scalar(255, 0, 0), -1);  // 끝 관절
}

int main() {
    cv::Mat image(HEIGHT, WIDTH, CV_8UC3);
    cv::namedWindow("Arm");

    double angle1 = 0.0;  // 첫 번째 관절 각도
    double angle2 = 0.0;  // 두 번째 관절 각도

    while (1) {
        // 각도 업데이트
        angle1 += 0.1;  // 첫 번째 관절 회전 속도
        angle2 += 0.1;  // 두 번째 관절 회전 속도

        // 로봇 팔 그리기
        drawRoboticArm(image, angle1, angle2);

        // 이미지 출력
        cv::imshow("Arm", image);

        // ESC 키를 누르면 종료
        char key = cv::waitKey(30);
        if (key == 27) break;
    }

    return 0;
}
