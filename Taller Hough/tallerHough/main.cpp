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
    Mat dst, cdst, cdstP, USH1;
    const char* default_file = "C:\\Users\\DANIE_000\\Desktop\\ultimo semestre\\Procesamiento de Imagenes\\qt\\Taller Hough\\tallerHough\\imagenes\\testL.png";
    const char* filename = argc >=2 ? argv[1] : default_file;
    // Loads an image
    Mat src = imread( filename, IMREAD_GRAYSCALE );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", default_file);
        return -1;
    }
    // Edge detection
    Canny(src, dst, 50, 200, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    USH1 = cdst.clone();
    // Standard Hough Line Transform
    vector<Vec2f> lines; // will hold the results of the detection
    vector<Point> puntos1;
    vector<Point> puntos2;
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        puntos1.push_back(cv::Point(pt1.x, pt1.y));
        puntos2.push_back(cv::Point(pt2.x, pt2.y));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);

    }
    for( size_t i = 0; i < puntos1.size(); i++ ){
        for(size_t j = 0; j < puntos2.size(); j++){
            Point pt1, pt2;
            pt1.x = puntos1[i].x;
            pt1.y = puntos1[i].y;
            pt2.x = puntos1[j].x;
            pt2.y = puntos1[j].y;
            if(puntos1[i].x == puntos2[j].x && puntos1[i].y == puntos2[j].y){
                printf(" Si entro");
                line( USH1, pt1, pt2, Scalar(255,255,0), 3, CV_AA);
            }else{
                line( USH1, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
                printf(" Si entroX2");
            }
        }
    }
    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
    // Show results
    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
    imshow("OJALA SI U.U", USH1);
    // Wait and Exit
    waitKey();
    return 0;

    QCoreApplication a(argc, argv);

    return a.exec();
}
