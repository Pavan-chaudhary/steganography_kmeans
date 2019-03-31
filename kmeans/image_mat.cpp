#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main( int argc, char* argv[] )
{
    //Mat image(7,7,CV_8UC3,Scalar(0,0,0));
    Mat image=imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    Mat image1;
	image.copyTo(image1);
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
	//randu(image,Scalar::all(0),Scalar::all(150));   //random color filling function
    cout<<"image.row"<<image.rows<<endl;
    cout<<"image.col"<<image.cols<<endl;
	//cout << "Matrix for image: "<< image << endl;
	
//-------------for pixel access using ptr row---------------------	
	for (int row = 0; row < image.rows; ++row)
    {
    //const uchar *ptr = image.ptr(row);
    for (int col = 0; col < image.cols; col++)
     {
        Vec3b intensity = image.at<Vec3b>(row,col);
		/*int inpR,inpG,inpB;
		cout<<"row = "<<row<<" col= "<<col<<": ";
		cin>>inpR>>inpG>>inpB;*/
		int a=intensity.val[0];
		int b=intensity.val[1];
		int c=intensity.val[2];
		
		a-50<0?image.at<Vec3b>(row,col)[0]=0:image.at<Vec3b>(row,col)[0]-=50;
		b-50<0?image.at<Vec3b>(row,col)[1]=0:image.at<Vec3b>(row,col)[1]-=50;
		c-50<0?image.at<Vec3b>(row,col)[2]=0:image.at<Vec3b>(row,col)[2]-=50;
		
		//cout<<"Red: "<<c<<", Green: "<<b<<" ,Blue: "<<a<<endl;*/

		/*c>50?image.at<Vec3b>(row,col)[0]-=50:image.at<Vec3b>(row,col)[0]=c;
		b>50?image.at<Vec3b>(row,col)[1]-=50:image.at<Vec3b>(row,col)[1]=b;
		a>50?image.at<Vec3b>(row,col)[2]-=50:image.at<Vec3b>(row,col)[2]=a;*/ 
     }
    }
//-----------------------------------------------------------
	
/*------------------------kmeans----------------------------------
	const unsigned int singleLineSize = image.rows * image.cols;
	const unsigned int K = 3;
	Mat data = image.reshape(1, singleLineSize);
	data.convertTo(data, CV_32F);
	vector<int> labels;
	Mat1f colors;
	int MAX_ITERATIONS=20;
	kmeans(data, K ,labels,TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.),MAX_ITERATIONS,KMEANS_PP_CENTERS,colors);
*///----------------------------------------------------------------
    namedWindow("Display previous",WINDOW_NORMAL);
    namedWindow( "Display window", WINDOW_NORMAL);// Create a window for display.
    imshow( "Display window", image);                   // Show our image inside it.
    imshow("Display previous",image1);
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
