#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // 이미지 경로
  std::string imagePath = "../image/image.png";

  cv::Mat src = cv::imread(imagePath, cv::IMREAD_COLOR);

  cv::Mat src_gray;
  cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

  cv::Mat blurred;
  cv::blur(src_gray, blurred, cv::Size(7, 7));

  std::vector<cv::Vec3f> circles;

  int money = 0;

  // 원을 검출하는 코드
  // 검출된 원을 정보를 circles 벡터 안에 저장
  // x, y, radius 순으로 저장된다.
  cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, 30, 150, 60);

  for (const auto& c : circles) {
    cv::Point center(cvRound(c[0]), cvRound(c[1]));
    int radius = cvRound(c[2]);

    // 동전 라벨링
    // LINE_AA: 부드럽게 그리기 위한 옵션
    cv::circle(src, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);

    std::cout << radius << std::endl; //반지름 크기를 확인하기 위한 코드

    if (radius / 10 == 4)
    {
      money += 500;
    }
    else if (radius / 10 == 3)
    {
      money += 100;
    }
    else if (radius / 10 == 2)
    {
      money += 10;
    }
  }

  std::cout << "money: " << money << std::endl;

  cv::imshow("Image", src);


  cv::waitKey(0);  // 키 입력 대기 후 창 닫기
  return 0;
}
