#include <opencv2/opencv.hpp>
#include <iostream>

void printHierarchy(const std::vector<cv::Vec4i>& hierarchy, const std::string& modeName) {
    std::cout << "== " << modeName << " ==" << std::endl;
    std::cout << "Hierarchy 정보 (형식: [next, previous, first_child, parent])" << std::endl;
    for (size_t i = 0; i < hierarchy.size(); ++i) {
        std::cout << "Contour " << i << ": ["
                  << hierarchy[i][0] << ", "
                  << hierarchy[i][1] << ", "
                  << hierarchy[i][2] << ", "
                  << hierarchy[i][3] << "]" << std::endl;
    }
    std::cout << std::endl;
}

void findContoursAndDraw(const cv::Mat& binary, int retrievalMode, const std::string& modeName, cv::Mat& outputImage) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // 외곽선 검출
    cv::findContours(binary, contours, hierarchy, retrievalMode, cv::CHAIN_APPROX_SIMPLE);

    // 외곽선을 출력 이미지에 그리기
    outputImage = cv::Mat::zeros(binary.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(outputImage, contours, static_cast<int>(i), cv::Scalar(0, 255, 0), 2);
    }

    // 계층 정보 출력
    printHierarchy(hierarchy, modeName);
}

int main() {
    // 이미지 경로
    std::string imagePath = "../image/image.png";

    // 이미지 불러오기 (컬러 모드로 불러오기)
    cv::Mat src = cv::imread(imagePath, cv::IMREAD_COLOR);

    // 그레이스케일 변환 및 이진화
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY);

    // 각 모드에 대한 결과 이미지 출력
    cv::Mat outputImage;

    // RETR_EXTERNAL
    findContoursAndDraw(binary, cv::RETR_EXTERNAL, "RETR_EXTERNAL", outputImage);
    cv::imshow("RETR_EXTERNAL", outputImage);

    // RETR_LIST
    findContoursAndDraw(binary, cv::RETR_LIST, "RETR_LIST", outputImage);
    cv::imshow("RETR_LIST", outputImage);

    // RETR_CCOMP
    findContoursAndDraw(binary, cv::RETR_CCOMP, "RETR_CCOMP", outputImage);
    cv::imshow("RETR_CCOMP", outputImage);

    // RETR_TREE
    findContoursAndDraw(binary, cv::RETR_TREE, "RETR_TREE", outputImage);
    cv::imshow("RETR_TREE", outputImage);

    cv::waitKey(0);  // 키 입력 대기 후 창 닫기
    return 0;
}
