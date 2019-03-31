#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

static bool pixel_equal(const Vec3b &a, const Vec3b &b)
{   return a == b;   } //"exact match"
// {   return norm(a,b) < 32;   } //more tolerant


int main( int argc, char** argv )
{
    Mat im = imread(argv[1],IMREAD_COLOR);

    Vec3b *p = im.ptr<Vec3b>();
    vector<Vec3b> pix(p, p+im.total());

    vector<int> labels;
    int unique = partition(pix, labels, pixel_equal);

    Mat lm = Mat(labels).reshape(1,im.rows);
    cerr << im << endl;
    cerr << lm << endl;
    cerr << unique << " unique colors" << endl;
    return 0;
}