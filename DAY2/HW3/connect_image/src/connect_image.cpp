#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // 이미지 로드
  cv::Mat background = cv::imread("../image/background.png");
  cv::Mat overlay = cv::imread("../image/image.png");



  // 투명도 설정
  double alpha = 0.5;  // 오버레이 이미지 투명도

  // (0,0)에 위치할 ROI 설정
  cv::Mat roi = background(cv::Rect(0, 0, overlay.cols, overlay.rows));

  // 이미지 합성
  cv::addWeighted(overlay, alpha, roi, 1.0, 0.0, roi);

  // 결과 출력
  cv::namedWindow("Result", cv::WINDOW_AUTOSIZE);
  cv::imshow("Result", background);


  cv::waitKey(0);
  return 0;
}
