#include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <fstream>

 using namespace std;
 using namespace cv;

 /** Function Headers */
 void detectAndDisplay( Mat frame );

 /** Global variables */
 String face_cascade_name = "haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);

std::ofstream arduino;

 /** @function main */
 int main( int argc, const char** argv )
 {



        //open arduino device file (linux)
        
        arduino.open( "/dev/ttyACM0");

        //write to it
        arduino << "Hello from C++!";
        



   CvCapture* capture;
   Mat frame;

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

   //-- 2. Read the video stream
   capture = cvCaptureFromCAM( -1 );
   if( capture )
   {
     while( true )
     {
   frame = cvQueryFrame( capture );

   //-- 3. Apply the classifier to the frame
       if( !frame.empty() )
       { detectAndDisplay( frame ); }
       else
       { printf(" --(!) No captured frame -- Break!"); break; }

       int c = waitKey(10);
       if( (char)c == 'c' ) { break; }
      }
   }
   return 0;
  arduino.close();
  
  
  
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  { 
    
    string Json = "[{";
    
    int Ejex = faces[i].x + faces[i].width*0.5;
    int Ejey = faces[i].y + faces[i].height*0.5;
    int Ejez = ( faces[i].width + faces[i].height ) / 2;

    
stringstream ss;
ss << Ejex;
string StrEjex = ss.str();

stringstream cc;
cc << Ejey;
string StrEjey = cc.str();

stringstream dd;
dd << Ejez;
string StrEjez = dd.str();


	Json = Json + "\"x\":\"" + StrEjex + "\",\"y\":\"" + StrEjey + "\",\"z\":\"" + StrEjez + "\"}";

	

	
	
	
if ( faces.size() == 2)
{
    int Ejex2 = faces[2].x + faces[2].width*0.5;
    int Ejey2 = faces[2].y + faces[2].height*0.5;
    int Ejez2 = ( faces[2].width + faces[2].height ) / 2;

    
stringstream ee;
ee << Ejex2;
string StrEjex = ee.str();

stringstream ff;
ff << Ejey2;
string StrEjey = ff.str();

stringstream gg;
gg << Ejez2;
string StrEjez = gg.str();
   Json = Json + ",{\"x\":\"" + StrEjex + "\",\"y\":\"" + StrEjey + "\",\"z\":\"" + StrEjez + "\"}";
 
}



if ( faces.size() == 3)
{
    int Ejex2 = faces[3].x + faces[3].width*0.5;
    int Ejey2 = faces[3].y + faces[3].height*0.5;
    int Ejez2 = ( faces[3].width + faces[3].height ) / 2;

    
stringstream gg;
gg << Ejex2;
string StrEjex = gg.str();

stringstream ii;
ii << Ejey2;
string StrEjey = ii.str();

stringstream yy;
yy << Ejez2;
string StrEjez = yy.str();
   Json = Json + ",{\"x\":\"" + StrEjex + "\",\"y\":\"" + StrEjey + "\",\"z\":\"" + StrEjez + "\"}";
 
}	


	
	
	Json = Json + "]";
        std::cout << Json << std::endl;	
	
	
   // std::cout << "X-->" << Ejex << "      Y-->" << Ejey << "      z-->" << Ejez << std::endl;
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       // std::cout << "Cara---->" << faces[i].x << std::endl;
       // std::cout << "Ojos---->" << eyes[j].x << std::endl;
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }
  //-- Show what you got
  imshow( window_name, frame );
  
  
  
 }

