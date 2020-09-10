#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
int main( int argc, char** argv ) {
  // Loading Images
  Mat star_map,small_area,small_area_rotated;
  star_map = imread("StarMap.png" ,IMREAD_COLOR);
  small_area = imread("Small_area.png",IMREAD_COLOR);
  small_area_rotated = imread("Small_area_rotated.png",IMREAD_COLOR);
  
  // Smoothing Images 
  Mat blurred_star_map,blurred_small_area,blurred_small_area_rotated;
  GaussianBlur(star_map,blurred_star_map,Size(5,5),0);
  GaussianBlur(small_area,blurred_small_area,Size(5,5),0);
  GaussianBlur(small_area_rotated,blurred_small_area_rotated,Size(5,5),0);

 // Gray Images 
  Mat gray_star_map,gray_small_area,gray_small_area_rotated;
  cvtColor(blurred_star_map,gray_star_map, COLOR_BGR2GRAY);
  cvtColor(blurred_small_area,gray_small_area, COLOR_BGR2GRAY);
  cvtColor(blurred_small_area_rotated,gray_small_area_rotated, COLOR_BGR2GRAY);

  
  Mat masked_image,kernel,norm_image;
  // Creating Kernel
  kernel=gray_small_area/(float)255;
  // Apply Kernel To Image
  filter2D(gray_star_map,masked_image,-1,kernel,Point(-1,-1),0,BORDER_DEFAULT  );
  // To See More Clear (It's not necessary it's optional for this image) 
  masked_image=255-masked_image;
  // To Avoid Noisy Data Applying Median Filter (Salt & Pepper filter can also used)
  medianBlur (masked_image, norm_image, 29 );
  // Show Result (Big Black Points Show Location of Image and there are more than one location for this image)
  namedWindow( "Matching Image",WINDOW_AUTOSIZE );
  imshow( "Matching Image",norm_image );
  
  waitKey(0);
  return 0;
}
