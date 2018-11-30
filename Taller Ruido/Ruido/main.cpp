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
    char *archivo1 = "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller Ruido\\Ruido\\imagenes\\testB.png";

    Mat src = imread(archivo1, CV_LOAD_IMAGE_GRAYSCALE);
    Mat dst;

    bilateralFilter ( src, dst, 15, 30, 30 );
    imshow("Imagen Original", src);
    imshow("Bilateral", dst);

    blur ( src, dst, Size(3,3) );
    imshow("Blur", dst);

    GaussianBlur( src, dst, Size( 15, 15 ), 0, 0 );
    imshow( "Gausian Blur", dst );

    for (int i=1; i<8; i=i+2)
       {
          blur(src, dst, Size(i,i));
          imshow( "Blur del for", dst );
          cout << i << " Numero de filtro" << endl;

          GaussianBlur( src, dst, Size( i, i ), 0, 0 );
          imshow( "Gausian Blur For", dst );
          waitKey(3000);
       }



    QCoreApplication a(argc, argv);
    return a.exec();
}
