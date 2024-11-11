#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

int main() {
    // 이미지 경로
    std::string imagePath = "../image/image.jpg";

    cv::Mat src = cv::imread(imagePath, cv::IMREAD_COLOR);

    // 그레이스케일 변환
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // Canny 엣지 검출
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150, 3);

    // 허프 선 변환 결과를 위한 복사본
    cv::Mat probabilisticHoughLinesImage = src.clone();

    // 확률적 허프 선 변환
    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(edges, linesP, 1, CV_PI / 180, 50, 50, 20);

    // 각도별 발견 횟수를 저장하는 배열
    int angle_count[181] = {0, };
    int unique_angles = 0;

    // 모든 선 그리기 및 각도 계산
    for (int i = 0; i < linesP.size(); i++) {
        const auto& l = linesP[i];

        // 선 그리기
        cv::line(probabilisticHoughLinesImage,
                cv::Point(l[0], l[1]),
                cv::Point(l[2], l[3]),
                cv::Scalar(0, 255, 0), 2);

        // 각도 계산
        double angle = std::atan2(l[3] - l[1], l[2] - l[0]);
        int angle_deg = static_cast<int>(std::round(angle * 180 / CV_PI));

        // 각도를 0~180 범위로 조정
        if(angle_deg < 0) {
            angle_deg += 180;
        }
        if(angle_deg == 180) {
            angle_deg = 0;
        }

        angle_count[angle_deg]++;
    }

    // 각도별 발견 횟수 출력
    for(int i = 0; i < 181; i++) {
        if(angle_count[i] > 0) {
            std::cout << i << "도: " << angle_count[i] << "개의 선" << std::endl;
        }
    }

    std::cout << "\n검출된 총 선의 개수: " << linesP.size() << std::endl;

    // 결과 출력
    cv::imshow("Original Image", src);
    cv::imshow("Canny Edges", edges);
    cv::imshow("All Detected Lines", probabilisticHoughLinesImage);

    cv::waitKey(0);
    return 0;
}
