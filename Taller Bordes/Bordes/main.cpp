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
      Mat src;
      Mat grad;
      int scale = 1;
      int delta = 0;
      int ddepth = CV_16S;

      src = imread( "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller Bordes\\Bordes\\imagenes\\testC.png", CV_LOAD_IMAGE_GRAYSCALE );
      imshow("Imagen Original", src);

      if( !src.data )
      {cout <<" No se encuentra la imagen" << endl;}

      GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
      imshow("Imagen GaussianBlur", src);

      Mat grad_x, grad_y;
      Mat abs_grad_x, abs_grad_y;

      // Derivada X
      Sobel( src, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
      convertScaleAbs( grad_x, abs_grad_x );
      imshow("Imagen Derivada X", abs_grad_x);

      // Derivada Y
      Sobel( src, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
      convertScaleAbs( grad_y, abs_grad_y );
      imshow("Imagen Derivada Y", abs_grad_y);

      // Total
      addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
      imshow( "TOTAL", grad );

      cvWaitKey(0);
      QCoreApplication a(argc, argv);

      return a.exec();
}
