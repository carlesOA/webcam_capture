#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) 
{
	//OpenCV video capture object
    cv::VideoCapture camera;
	
	//OpenCV image object
    cv::Mat image;
	
	//camera id . Associated to device number in /dev/videoX
	int cam_id; 
	
	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;  
			break; 
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break; 
		default: 
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	//advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) ) 
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it
        if(!camera.read(image)) 
		{
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }
       
      // change the 16 neigbors of the central pixel to the color black
	for(int x =318; x < 322; x++){
		for(int y = 238; y < 242; y ++){
			image.at<cv::Vec3b>(y,x)[0] = 0;  
			image.at<cv::Vec3b>(y,x)[1] = 0;  
			image.at<cv::Vec3b>(y,x)[2] = 0;  
		} 
	}

	//show image in a window
	cv::imshow("Output Window", image);

	//print image dimensions
		std::cout << "image size is: " << image.rows << "x" << image.cols << std::endl;

	//print the central pixel
		std::cout <<"the value of the central pixel is:" << (image.rows/2) << ":" << (image.cols/2) << std::endl;
	
	//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }   
}
