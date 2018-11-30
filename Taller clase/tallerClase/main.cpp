#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/cv.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat src = imread( "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller clase\\tallerClase\\imagenes\\taller_clase.png", CV_LOAD_IMAGE_GRAYSCALE );
    imshow("Imagen Original", src);

    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    Mat  edge, draw;

    Canny( src, edge, 50, 150, 3);
    Vec3b green(0, 255, 0);
    edge.convertTo(draw, CV_8U);
    namedWindow("Solo Bordes", CV_WINDOW_AUTOSIZE);
    imshow("Solo bordes", draw);

    QCoreApplication a(argc, argv);

    return a.exec();
}
