//============================================================================
// Name        : KMeansDemo.cpp
// Author      : Pavan chaudhary
//============================================================================
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

/*****************************************************************************************************************************/
//Namespaces
using namespace cv;
using namespace std;
/*****************************************************************************************************************************/
//Global Variables
const unsigned int SLIDER_MAX = 25;
const std::string WINDOW_NAME = "KMeans demo";
const std::string TRACKBAR_NAME = "Clusters";
int MAX_ITERATIONS = 2;
Mat image;

/*****************************************************************************************************************************/
/**
    Returns the processed image using cv::kmeans

    @param const Mat& source The image to be processed.
    @return A reduced color image with (sliderValue) colors
*/
Mat applyKMeans(const Mat& source,int k);

/*****************************************************************************************************************************/

int main (int argc,const char* argv[]) {
	image = imread(argv[1], IMREAD_COLOR);
	long k=strtol(argv[2],NULL,10);
	if (!image.data){
		cout << "Image contains no data" << endl;
		destroyAllWindows();
		return EXIT_FAILURE;
	}
	namedWindow(WINDOW_NAME,WINDOW_NORMAL);
	Mat modImage=applyKMeans(image,k);
	string clus=argv[2];
	imwrite("/home/pavan/Major/pictures/sid_"+clus+".jpg",modImage);
	imshow(WINDOW_NAME,modImage);
	waitKey(0);
	destroyAllWindows();
	return EXIT_SUCCESS;
}

/*****************************************************************************************************************************/

Mat applyKMeans(const Mat& source,int k){

	chrono::high_resolution_clock::time_point start,end; // for time measurement
	chrono::duration<double> elapsedTime;			 	  // for time measurement
	start =chrono::high_resolution_clock::now();
	const unsigned int singleLineSize = source.rows * source.cols;
	Mat data = source.reshape(1, singleLineSize);
	data.convertTo(data, CV_32F);
	vector<int> labels;
	Mat1f colors;
	kmeans(data,k,labels,cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.),MAX_ITERATIONS,cv::KMEANS_PP_CENTERS,colors);
	for (unsigned int i = 0 ; i < singleLineSize ; i++ ){
				data.at<float>(i, 0) = colors(labels[i], 0);
		        data.at<float>(i, 1) = colors(labels[i], 1);
		        data.at<float>(i, 2) = colors(labels[i], 2);
	}

	Mat outputImage = data.reshape(3, source.rows);
	outputImage.convertTo(outputImage, CV_8U);
	end = std::chrono::high_resolution_clock::now();
	elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	std::cout<< "Elapsed time for processing with " << k <<" clusters " << elapsedTime.count() << "s" << std::endl;
	return outputImage;
}

/*****************************************************************************************************************************/



/*****************************************************************************************************************************/
