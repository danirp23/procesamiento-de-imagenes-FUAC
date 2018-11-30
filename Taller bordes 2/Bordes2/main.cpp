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

Mat orientacion(const cv::Mat& mag, const cv::Mat& ori, double thresh = 1.0)
{
    Mat oriMap = Mat::zeros(ori.size(), CV_8UC3);
    Vec3b red(10, 10, 10);
    Vec3b yellow(0, 255, 255);
    for(int i = 0; i < mag.rows*mag.cols; i++)
    {
        float* magPixel = reinterpret_cast<float*>(mag.data + i*sizeof(float));
        if(*magPixel > thresh)
        {
            float* oriPixel = reinterpret_cast<float*>(ori.data + i*sizeof(float));
            Vec3b* mapPixel = reinterpret_cast<Vec3b*>(oriMap.data + i*3*sizeof(char));
            if(*oriPixel <= 100)
                *mapPixel = red;
            else *mapPixel = yellow;
        }
    }
    return oriMap;
}
int main(int argc, char *argv[])
{

    Mat image1 = imread( "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller bordes 2\\Bordes2\\imagenes\\testD1.png", CV_LOAD_IMAGE_GRAYSCALE );
    Mat image2 = imread( "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller bordes 2\\Bordes2\\imagenes\\testD2.png", CV_LOAD_IMAGE_GRAYSCALE );

    imshow("original 1", image1);
    imshow("original 2", image2);

    image1=mat2gray(image1);
    image2=mat2gray(image2);

    Mat Sx1;
    Mat Sx2;
    Sobel(image1, Sx1, CV_32F, 1, 0, 3);
    Sobel(image2, Sx2, CV_32F, 1, 0, 3);

    Mat Sy1;
    Mat Sy2;
    Sobel(image1, Sy1, CV_32F, 0, 1, 3);
    Sobel(image2, Sy2, CV_32F, 0, 1, 3);


    Mat mag1,mag2,ori1, ori2;
    magnitude(Sx1, Sy1, mag1);
    phase(Sx1, Sy1, ori1, true);
    magnitude(Sx2, Sy2, mag2);
    phase(Sx2, Sy2, ori2, true);

    Mat imge1 = orientacion(mag1, ori1, 1.0);
    Mat imge2 = orientacion(mag2, ori2, 1.0);

    imshow("Imagen 1 orientacion", imge1);
    imshow("Imagen 2 orientacion", imge2);
    waitKey(0);

    QCoreApplication a(argc, argv);

    return a.exec();
}

