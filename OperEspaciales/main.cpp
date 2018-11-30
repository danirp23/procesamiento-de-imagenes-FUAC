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
    char *archivo1 = "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\OperEspaciales\\imagenes\\testF1.png";
    char *archivo2 = "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\OperEspaciales\\imagenes\\testF2.png";
    //SEGUNDO PUNTO
    Mat src = imread(archivo1, CV_LOAD_IMAGE_GRAYSCALE);

    Mat dst;
    Mat kernel = (Mat_<char>(3, 3) << 0,  0, 0,
                                      2, 0, -2,
                                      0,  0, 0);
    cv::filter2D(src, dst, src.depth(), kernel);
    imshow("Imagen sin nada", src);
    imshow("Imagen con filtro SEGUNDO PUNTO", dst);

    //TERCER PUNTO
    src = imread(archivo1, CV_LOAD_IMAGE_GRAYSCALE);
    kernel = (Mat_<char>(5, 5) << 1, 1, 1, 1, 1,
                                  1, 3, 3, 3, 1,
                                  1, 3, 8, 3, 1,
                                  1, 3, 3, 3, 1,
                                  1, 1, 1, 1, 1);
    cv::filter2D(src, dst, src.depth(), kernel);
    imshow("Imagen con filtro TERCER PUNTO", dst);

    IplImage *imagen1 = NULL;
    IplImage *imagen2 = NULL;
    IplImage *imagen3 = NULL;
    imagen1 = cvLoadImage(archivo1,CV_LOAD_IMAGE_GRAYSCALE);
    imagen2 = cvLoadImage(archivo2,CV_LOAD_IMAGE_GRAYSCALE);
    imagen3 = cvCreateImage(cvSize(imagen1->width,imagen1->height),IPL_DEPTH_8U,1);
    cvAbsDiff(imagen1,imagen2,imagen3);
    cvNamedWindow("Imagen 1",0);
    cvShowImage("Imagen 1",imagen1);
    cvNamedWindow("Imagen 2",0);
    cvShowImage("Imagen 2",imagen2);
    cvNamedWindow("Resultado",0);
    cvShowImage("Resultado",imagen3);
    cvWaitKey(0);
    cvReleaseImage(&imagen1);
    cvReleaseImage(&imagen2);
    cvReleaseImage(&imagen3);



    QCoreApplication a(argc, argv);

    return a.exec();
}
