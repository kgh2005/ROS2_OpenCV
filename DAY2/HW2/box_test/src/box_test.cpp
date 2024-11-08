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
  cv::inRange(hsv, cv::Scalar(90, 70, 50), cv::Scalar(130, 255, 255), mask_blue);

  // 모폴로지 연산을 위한 커널 생성
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(21, 21));

  // 각 마스크에 대해 Opening과 Closing 연산 수행
  cv::Mat red_processed, green_processed, blue_processed;
  colorMorphology(mask_red, red_processed, kernel);
  colorMorphology(mask_green, green_processed, kernel);
  colorMorphology(mask_blue, blue_processed, kernel);

  // 각 색상에 대한 연결된 구성 요소 찾기 (Connected Components)
  cv::Mat labels_red, stats_red, centroids_red;
  int num_red = cv::connectedComponentsWithStats(red_processed, labels_red, stats_red, centroids_red, 8, CV_32S);

  cv::Mat labels_green, stats_green, centroids_green;
  int num_green = cv::connectedComponentsWithStats(green_processed, labels_green, stats_green, centroids_green, 8, CV_32S);

  cv::Mat labels_blue, stats_blue, centroids_blue;
  int num_blue = cv::connectedComponentsWithStats(blue_processed, labels_blue, stats_blue, centroids_blue, 8, CV_32S);

  // 결과 이미지를 원본 이미지로 초기화
  cv::Mat result_image = image.clone();

  for (int i = 0; i < num_red; i++)
  {
    int red_x = stats_red.at<int>(1, 0); // x 좌표
    int red_y = stats_red.at<int>(1, 1); // y 좌표
    int red_width = stats_red.at<int>(1, 2); // 너비
    int red_height = stats_red.at<int>(1, 3); // 높이
    int red_area = stats_red.at<int>(1, 4);   // 면적

    if (red_area > 100)
    {
      // 빨간색 바운딩 박스를 그리기
      cv::Rect red_box(red_x, red_y, red_width, red_height);
      cv::rectangle(result_image, red_box, cv::Scalar(0, 0, 255), 2); // 빨간색 (BGR)

    }

  }

  for (int i = 0; i < num_green; i++)
  {
    int green_x = stats_green.at<int>(1, 0); // x 좌표
    int green_y = stats_green.at<int>(1, 1); // y 좌표
    int green_width = stats_green.at<int>(1, 2); // 너비
    int green_height = stats_green.at<int>(1, 3); // 높이
    int green_area = stats_red.at<int>(1, 4);   // 면적

    if (green_area > 100)
    {
      // 초록색 바운딩 박스를 그리기
      cv::Rect green_box(green_x, green_y, green_width, green_height);
      cv::rectangle(result_image, green_box, cv::Scalar(0, 255, 0), 2); // 초록색 (BGR)
    }
  }

  for (int i = 0; i < num_blue; i++)
  {
    int blue_x = stats_blue.at<int>(1, 0); // x 좌표
    int blue_y = stats_blue.at<int>(1, 1); // y 좌표
    int blue_width = stats_blue.at<int>(1, 2); // 너비
    int blue_height = stats_blue.at<int>(1, 3); // 높이
    int blue_area = stats_red.at<int>(1, 4);   // 면적

    if (blue_area > 100)
    {
      // 파란색 바운딩 박스를 그리기
      cv::Rect blue_box(blue_x, blue_y, blue_width, blue_height);
      cv::rectangle(result_image, blue_box, cv::Scalar(255, 0, 0), 2); // 파란색 (BGR)
    }

  }


  // 결과 이미지 출력
  cv::imshow("Result", result_image);
  cv::waitKey(0);
  return 0;
}
