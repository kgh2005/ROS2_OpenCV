#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main() {
    // 이미지 로드
    cv::Mat image = cv::imread("../resources/image.png");

    if(image.empty()) {
        std::cout << "Error: Could not load image" << std::endl;
        return -1;
    }

    // BGR을 HSV로 변환
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // 노란색 마스크를 저장할 Mat 객체
    cv::Mat mask_yellow;

    // 노란색 HSV 범위 설정
    cv::inRange(hsv, cv::Scalar(20, 170, 100), cv::Scalar(30, 255, 255), mask_yellow);


    // 이진화 이미지에 가우시안 블러 적용
    cv::Mat blurred_mask;
    cv::GaussianBlur(mask_yellow, blurred_mask, cv::Size(5,5), 0);


    // 결과 표시
    cv::imshow("Original Image", image);
    cv::imshow("Gaussian Blurred", blurred_mask);
    cv::imshow("Yellow", mask_yellow);

    // 결과 저장
    cv::imwrite("blurred_image.jpg", blurred_mask);
    cv::imwrite("yellow.jpg", mask_yellow);

    // 키 입력 대기
    cv::waitKey(0);

    return 0;
}
