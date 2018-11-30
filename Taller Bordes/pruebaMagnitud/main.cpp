#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


Mat mat2gray(const cv::Mat& src)
{
    Mat dst;
    normalize(src, dst, 0.0, 255.0, cv::NORM_MINMAX, CV_8U);

    return dst;
}

Mat mayorCientoVeinte(const cv::Mat& mag, const cv::Mat& ori, double thresh = 1.0)
{
    Mat oriMap = Mat::zeros(ori.size(), CV_8UC3);
    Vec3b red(0, 0, 255);
    for(int i = 0; i < mag.rows*mag.cols; i++)
    {
        float* magPixel = reinterpret_cast<float*>(mag.data + i*sizeof(float));
        if(*magPixel > thresh)
        {
            float* oriPixel = reinterpret_cast<float*>(ori.data + i*sizeof(float));
            Vec3b* mapPixel = reinterpret_cast<Vec3b*>(oriMap.data + i*3*sizeof(char));
            if(*oriPixel > 120.0)
                *mapPixel = red;
        }
    }
    return oriMap;
}
Mat entreCeroyCuarenta(const cv::Mat& mag, const cv::Mat& ori, double thresh = 1.0)
{
    Mat oriMap = Mat::zeros(ori.size(), CV_8UC3);
    Vec3b cyan(255, 255, 0);
    for(int i = 0; i < mag.rows*mag.cols; i++)
    {
        float* magPixel = reinterpret_cast<float*>(mag.data + i*sizeof(float));
        if(*magPixel > thresh)
        {
            float* oriPixel = reinterpret_cast<float*>(ori.data + i*sizeof(float));
            Vec3b* mapPixel = reinterpret_cast<Vec3b*>(oriMap.data + i*3*sizeof(char));
            if(*oriPixel >= 0 && *oriPixel < 45)
                *mapPixel = cyan;

        }
    }

    return oriMap;
}
int main(int argc, char *argv[])
{

    Mat image = imread( "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller Bordes\\Bordes\\imagenes\\testC.png", CV_LOAD_IMAGE_GRAYSCALE );

    imshow("original", image);

    Mat Sx;
    Sobel(image, Sx, CV_32F, 1, 0, 3);

    Mat Sy;
    Sobel(image, Sy, CV_32F, 0, 1, 3);

    Mat mag, ori;
    magnitude(Sx, Sy, mag);
    phase(Sx, Sy, ori, true);

    Mat mayor = mayorCientoVeinte(mag, ori, 1.0);
    Mat entre = entreCeroyCuarenta(mag, ori, 1.0);

    imshow("Mayor de 120", mayor);
    imshow("Entre o y 45", entre);
    waitKey();

        return 0;
    QCoreApplication a(argc, argv);

    return a.exec();
}
