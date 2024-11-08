#include <opencv2/opencv.hpp>
#include <iostream>

void colorMorphology(const cv::Mat& input_mask, cv::Mat& output_mask,const cv::Mat& kernel) {
  cv::morphologyEx(input_mask, output_mask, cv::MORPH_OPEN, kernel,
                   cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
                   cv::morphologyDefaultBorderValue());
  cv::morphologyEx(output_mask, output_mask, cv::MORPH_CLOSE, kernel,
                   cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
                   cv::morphologyDefaultBorderValue());
}

void open(const cv::Mat& input_mask, cv::Mat& output_mask,const cv::Mat& kernel) {
  cv::erode(input_mask, output_mask, kernel);
  cv::dilate(output_mask, output_mask, kernel);
}

void close(const cv::Mat& input_mask, cv::Mat& output_mask,const cv::Mat& kernel) {
  cv::dilate(input_mask, output_mask, kernel);
  cv::erode(output_mask, output_mask, kernel);
}

int main() {
  // 이미지 읽기
  cv::Mat image = cv::imread("../image/image.jpg");

  // 가우시안 필터 적용 (이미지 부드럽게 하기)
  cv::Mat blurred_image;
  cv::GaussianBlur(image, blurred_image, cv::Size(5, 5), 0);

  // BGR을 HSV로 변환
  cv::Mat hsv;
  cv::cvtColor(blurred_image, hsv, cv::COLOR_BGR2HSV);

  // 각 색상의 HSV 범위 설정
  cv::Mat mask_red1, mask_red2, mask_red;
  cv::inRange(hsv, cv::Scalar(0, 70, 50), cv::Scalar(10, 255, 255), mask_red1);
  cv::inRange(hsv, cv::Scalar(160, 70, 50), cv::Scalar(180, 255, 255), mask_red2);
  cv::bitwise_or(mask_red1, mask_red2, mask_red);

  // 초록색 마스크 (35-85)
  cv::Mat mask_green;
  cv::inRange(hsv, cv::Scalar(35, 70, 50), cv::Scalar(85, 255, 255), mask_green);

  // 파란색 마스크 (90-120)
  cv::Mat mask_blue;
  cv::inRange(hsv, cv::Scalar(90, 70, 50), cv::Scalar(120, 255, 255), mask_blue);

  // 모폴로지 연산을 위한 커널 생성
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));

  // 각 마스크에 대해 Opening과 Closing 연산 수행
  cv::Mat red_processed, green_processed, blue_processed;
  colorMorphology(mask_red, red_processed, kernel);
  colorMorphology(mask_green, green_processed, kernel);
  colorMorphology(mask_blue, blue_processed, kernel);

  cv::Mat red_open, green_open, blue_open;
  cv::Mat red_close, green_close, blue_close;
  open(mask_red, red_open, kernel);
  close(red_open, red_close, kernel);

  open(mask_green, green_open, kernel);
  close(green_open, green_close, kernel);

  open(mask_blue, blue_open, kernel);
  close(blue_open, blue_close, kernel);


  // 결과 출력
  cv::namedWindow("Red_org", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Green_org", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Blue org", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Red_custom", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Green_custom", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("Blue_custom", cv::WINDOW_AUTOSIZE);

  cv::imshow("Red_org", red_processed);
  cv::imshow("Green_org", green_processed);
  cv::imshow("Blue org", blue_processed);
  cv::imshow("Red_custom", red_close);
  cv::imshow("Green_custom", green_close);
  cv::imshow("Blue_custom", blue_close);

  cv::waitKey(0);
  return 0;
}
