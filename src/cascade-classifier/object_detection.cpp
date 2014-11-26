#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
// void detectAndDisplay( Mat frame );

/** Global variables */
// String face_cascade_name = "haarcascade_frontalface_alt.xml";
// String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
// CascadeClassifier face_cascade;
// CascadeClassifier eyes_cascade;
// String window_name = "Capture - Face detection";

const String keys =
    "{help h usage ? |      | print this message   }"
    "{model          |      | cascade model        }"
    "{image          |      | image for detection  }"
    ;

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        parser.printMessage();
        return 1;
    }
    
    String model = parser.get<String>("model");
    String imageName = "None";
    imageName = parser.get<String>("image");

    CascadeClassifier pedestirian_cascade;
    if (!pedestirian_cascade.load(model))
    {
        parser.printMessage();
    }

    Mat img = imread(imageName);
    CV_Assert(!imageName.empty());

    std::vector<Rect> objects;
    pedestirian_cascade.detectMultiScale(img, objects);

    Mat dst;
    img.copyTo(dst);
    for (int i = 0; i < objects.size(); ++i)
    {
        rectangle(dst, objects[i], Scalar(0, 255, 0), 3);
    }

    namedWindow("Detected humans");
    imshow("Detected humans", dst);
    waitKey();
    
    return 0;
}

// void detectAndDisplay( Mat frame )
// {
//     std::vector<Rect> faces;
//     Mat frame_gray;

//     cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
//     equalizeHist( frame_gray, frame_gray );

//     //-- Detect faces
//     face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

//     for ( size_t i = 0; i < faces.size(); i++ )
//     {
//         Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
//         ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

//         Mat faceROI = frame_gray( faces[i] );
//         std::vector<Rect> eyes;

//         //-- In each face, detect eyes
//         eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

//         for ( size_t j = 0; j < eyes.size(); j++ )
//         {
//             Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
//             int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
//             circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
//         }
//     }
//     //-- Show what you got
//     imshow( window_name, frame );
// }