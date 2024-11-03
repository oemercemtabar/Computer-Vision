//
//  part1.cpp
//  Part 1 of Computer Vision Lab 2 Homework
//  Computer Vision Lab 2 Part 1
//
//  Created by Cem Tabar
//

/*
Some Personal Notes For Later:
 
Histogram is a graphical representation of the intensity distribution of an image. In simple terms, it represents the number of pixels for each intensity value considered.
 
 In general sense if the image is gray-scale, x-axis represents the tonal scale (black at the left and white at the right), and y-axis represents the number of pixels in the image. The resultant histogram will show the number of pixels for each brightness level (from black to white if the image in gray-scale), and when there are more pixels, the peak at the certain brightness level is higher.
 
 On the other hand, if we are processing image with color, Red-Green-Blue histogram representation will be represented. In this case in each histogram, x-asix wiil represent the tonal scale(according to red,green or blue from dark to light), and y-axis represents the number of pixels in the image. As stated above, histograms will show the number of pixels for each brightness level for each color, and when there are more pixels, the peak at the certain brightness level is higher.
 
 Histogram Equalization is a technique in computer image processing for improving contrast in images. It works as spreading out the most frequent intensity values. By this method, generally we are increasing the global contrast of the image when its usable data is represented by close contrast values. This allows for areas of lower local contrast to gain a higher contrast.
 
 As a side note:
 A color histogram of an image represents the number of pixels in each type of color component. Histogram equalization cannot be applied separately to the Red, Green and Blue components of the image as it leads to dramatic changes in the images color balance. However, if the image is first converted to another color space then the histogram equalization algorithm can be applied to the luminance or value channel without resulting in changes to the hue and saturation of the image.
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

//This is an external fucntion that takes the histograms and displays to the user
//Note that you should pass the histograms together not indiviudally
void showHistogram(vector<Mat>& hists)
{
    // Min/Max computation
    double hmax[3] = { 0,0,0 };
    double min;
    minMaxLoc(hists[0], &min, &hmax[0]);
    minMaxLoc(hists[1], &min, &hmax[1]);
    minMaxLoc(hists[2], &min, &hmax[2]);

    string wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0),
                             Scalar(0,0,255) };

    vector<Mat> canvas(hists.size());

    // Display each histogram in a canvas
    for (int i = 0, end = hists.size(); i < end; i++)
    {
        canvas[i] = Mat::ones(125, hists[0].rows, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < hists[0].rows - 1; j++)
        {
            line(
                canvas[i],
                Point(j, rows),
                Point(j, rows - (hists[i].at<float>(j) * rows / hmax[i])),
                hists.size() == 1 ? Scalar(200, 200, 200) : colors[i],
                1, 8, 0
            );
        }

        imshow(hists.size() == 1 ? "value" : wname[i], canvas[i]);
    }
}


int main(int argc, char** argv) {
    
    //Step 1: Loads an image (e.g., one of the provided images like “barbecue.jpg” or “countryside.jpg”, or any custom image you would like to use)
    
    //Loading the "countryside.jpg" image to a Matrix as given in the assignment instructions and deining as input_image
    //In some cases only giving the name of image does not work, that is why you need to define the path of the image too.
    //Path for the image: /Users/cemtabarmacbook/Desktop/Homework1_Omer_Cem_Tabar_2081169/ComputerVisionLab2Part1/ComputerVisionLab2Part1/countryside.jpg
    Mat original_image = imread("/Users/cemtabarmacbook/Desktop/COMVIS/Homework1_Omer_Cem_Tabar_2081169/ComputerVisionLab2Part1/ComputerVisionLab2Part1/countryside.jpg");
    
    
    //You can put the previous image into comment and uncomment this image to try on other image
    //As stated above, again in some cases only giving the name of the image does not work, that is why you need to give the path of the image.
    //Mat input_image = imread("barbecue.jpg");
    
    //Show the image to the user as Original Image
    imshow("Original Image", original_image);
    
    //Step 2: Prints the histograms of the image. You must compute 3 histograms, one for each channel (i.e., R, G and B) with 256 bins and [0, 255] as range. Notice that you need to use the calcHist() function separately on the 3 channels. You can use the provided function (in the “show_histogram_function.cpp” file) to visualize the data.
    
    //Since we have colored image, lets split the image into three channels
    //Channels represent the Red, Green and Blue pixels within the image
    
    //Seperation of the image into 3 channels as R,G and B
    //Define a matrix that takes the channels after the split operation as color_channels.
    Mat color_channels[3];
    
    //Split the image to the color channels and put it into color_channels matrix.
    split(original_image, color_channels);
    
    //COMPUTATION OF THE HISTOGRAMS
    //Each histogram will have 256 bins
    //Each histogram will have a range [0...255] for x-axis
    
    //Defining a matrices which will keep the calculated histograms
    Mat original_blue_histogram, original_green_histogram, original_red_histogram;
    
    //Setting the bin size
    int bins = 256;
    
    //Setting the range of histogram on x-axis
    float range[] = { 0, 256 };
    const float* histogram_range[] = { range };
    
    //Set uniform parameter to true in order to set each size of the bins same in the histogram
    bool uniform = true;
    
    //Set accumulate to false in order to clean the histograms in the beginning of each run
    bool accumulate = false;
    
    //We defined the above parameters in order to calculate hsitogram for each channel
    //We will use this parameters in the calcHist() function
    //Calculation of each histogram with calcHist() function and adding it to the original_histogram matrix
    
    //Calculate the histogram for Blue channel
    calcHist(&color_channels[0], 1, 0, Mat(), original_blue_histogram, 1, &bins, histogram_range, uniform, accumulate);
    //Calculate the histogram for Green channel
    calcHist(&color_channels[1], 1, 0, Mat(), original_green_histogram, 1, &bins, histogram_range, uniform, accumulate);
    //Calculate the histogram for Red channel
    calcHist(&color_channels[2], 1, 0, Mat(), original_red_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Putting the resultant histograms into vector for the visualization purposes
    //Since above showHistogram() function requires(takes as parameter) a vector of histograms
    vector<Mat> original_histograms{ original_blue_histogram, original_green_histogram, original_red_histogram };
    
    //Call showHistogram() fucntion and observe the original histograms
    showHistogram(original_histograms);
    
    //Step 3: Equalizes separately the R, G and B channels by using cv::equalizeHist().
    
    //Define a matrix to keep the reconsturcted equalized image
    Mat equalized_image;
    
    //Define a matrix that keeps the equalized image color channels
    Mat equalized_image_channels[3];
    
    //Equalize the channels using the equalizeHist() function
    //Pass the original image channels and put the equalized versions in the equalized_image_channels matrix
    
    //Pass the original blue image channel, equalize it and output as equalized_image_channel[0] (states blue)
    equalizeHist(color_channels[0], equalized_image_channels[0]);
    //Pass the original green image channel, equalize it and output as equalized_image_channel[1] (states green)
    equalizeHist(color_channels[1], equalized_image_channels[1]);
    //Pass the original red image channel, equalize it and output as equalized_image_channel[2] (states red)
    equalizeHist(color_channels[2], equalized_image_channels[2]);
    
    //Define individual matrices to keep equalized histograms
    //These histograms will be obtained after the calcHist() function.
    Mat equalized_blue_histogram, equalized_green_histogram, equalized_red_histogram;
    
    //Calculate the histogram for equalized Blue channel
    calcHist(&equalized_image_channels[0], 1, 0, Mat(), equalized_blue_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Calculate the histogram for equalized Green channel
    calcHist(&equalized_image_channels[1], 1, 0, Mat(), equalized_green_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Calculate the histogram for equalized Red channel
    calcHist(&equalized_image_channels[2], 1, 0, Mat(), equalized_red_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Put the equalized image histograms in a vector in order to pass it to the showHistogram() function
    vector<Mat> equalized_image_histograms{ equalized_blue_histogram, equalized_green_histogram, equalized_red_histogram};
    
    //Step 4: Shows the equalized image and the histogram of its channels.
    
    //We need to merge new values in order to reconstruct the new equalized image
    //Think it as it is a reverse operation of split at then beginning
    //We are just combining the equalized image channels with the image
    
    //Combine them in a vector
    vector<Mat> combined_equalized_image_channels{ equalized_image_channels[0], equalized_image_channels[1], equalized_image_channels[2] };
    
    //As we defined above, just merge the combined_equalized_image channels with equalized_image
    merge(combined_equalized_image_channels, equalized_image);
    
    //Visualized the Equalized image
    imshow("Equalized Image", equalized_image);
    
    //Show the equalized histograms
    showHistogram(equalized_image_histograms);
    
    //Write the new image for report purposes
    //You can uncomment the below code to optain the output in your local
    //Define a path for writing the resultant image to your local repository
    //In my case my path is: "/Users/cemtabarmacbook/Desktop/ComputerVisionLab2Part1/ComputerVisionLab2Part1/Outputs Part1/BGREqualizedImage.jpg"
    //imwrite("BGREqualizedImage.jpg", equalized_image);
    
    //Step 5: Notice the artifacts produced by this approach. To obtain a better equalization than the one of point 4, convert the image to a different color space, e.g. Lab (use cv::cvtColor() with COLOR_BGR2Lab as color space conversion code), and equalize only the luminance (L) channel.
    
    //In order to obtain a better euqalization we are converting the original image to another color space
    //Color space conversion code given as COLOR_BGR2Lab
    
    //Define new matrix for the new color space converted image
    Mat converted_image;
    
    //Define a new matrix for the new color space converted and equalized image
    Mat converted_equalized_image;
    
    //Converting the original image into another color space
    //Side Note: COLOR_BGR2LAB: This code is used to change the BGR color space to LAB color space
    /*
     LAB Color Space
     Lab Color is a more accurate color space. It uses three values (L, a, and b) to specify colors.
     Lab Color works more like the human eye. t specifies a color using a 3-axis system. The a-axis (green to red), b-axis (blue to yellow) and Luminance axis.
     */
    cvtColor(original_image, converted_image, COLOR_BGR2Lab);
    
    //Define the color channel matrix for the converted image
    Mat converted_image_channels[3];
    
    //Obtaining the channels from the converted image by split function
    split(converted_image, converted_image_channels);
    
    //Since it is given in the step 4 that we will only equalize the luminance channel
    
    //Define new matrix to keep eqaulized Luminance channel
    Mat equalized_luminance_channel;
    
    //Equalize the luminance channel and set it as equalized_luminance_channel
    //First channel is Luminance, second channel is "a" and third channel is "b"
    equalizeHist(converted_image_channels[0], equalized_luminance_channel);
    
    //Merge the channels again in order to construct the converted image again
    vector<Mat> merged_converted_equalized_channels{ equalized_luminance_channel, converted_image_channels[1], converted_image_channels[2] };
    
    //Merge the channels to obtain the new converted image with equalized luminance channel
    merge(merged_converted_equalized_channels, converted_equalized_image);
    
    //Convert back to the original color space (From LAB color space to RGB color space)
    cvtColor(converted_equalized_image, converted_equalized_image, COLOR_Lab2BGR);
    
    //Calculate the new histograms
    
    //Define new matrices to keep converted equalized histograms
    Mat converted_blue_equalized_histogram, converted_green_equalized_histogram, converted_red_equalized_histogram;
    
    //Define new matrix for the channels of the converted image after the luminance equalization
    //Again index:0 represents blu channel, index:1 represents green channel and index:2 represents the red channel
    Mat converted_equalized_color_channels[3];
    
    //Split the reconstructed image into the new color channels
    split(converted_equalized_image, converted_equalized_color_channels);
    
    
    //Calculate the Blue channel histogram after the luminance equalization
    calcHist(&converted_equalized_color_channels[0], 1, 0, Mat(), converted_blue_equalized_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Calculate the Green channel histogram after the luminance equalization
    calcHist(&converted_equalized_color_channels[1], 1, 0, Mat(), converted_green_equalized_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Calculate the Red channel histogram after the luminance equalization
    calcHist(&converted_equalized_color_channels[2], 1, 0, Mat(), converted_red_equalized_histogram, 1, &bins, histogram_range, uniform, accumulate);
    
    //Define a new vector to keep the histograms since showHistogram() function takes histogram parameters as a vector
    vector<Mat> converted_luminance_equalized_histograms{ converted_blue_equalized_histogram, converted_green_equalized_histogram, converted_red_equalized_histogram };
    
    //Print out the Luminance Equalized Image
    imshow("Luminance Equalized Image", converted_equalized_image);
    
    //Write the Luminance Equalized Image for report purposes
    //You can uncomment the below code to optain the output in your local
    //Define a path for writing the resultant image to your local repository
    //In my case my path is: "/Users/cemtabarmacbook/Desktop/ComputerVisionLab2Part1/ComputerVisionLab2Part1/Outputs Part1/LuminanceEqualizedImage.jpg"
    //imwrite("LuminanceEqualizedImage.jpg", converted_equalized_image);
    
    //Show the histograms after the luminance equalization
    showHistogram(converted_luminance_equalized_histograms);
    
    //In order to see the previous histogram you need to comment other unwanted showHistogram() lines
    //Uncommented showHistogram() line will be shown to the user
    
    waitKey(0);
    return 0;
}
