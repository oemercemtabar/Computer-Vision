//
//  main.cpp
//  Part 2 of Computer Vision Lab 2 Homework
//  Computer Vision Lab 2 Part 2
//
//  Created by Cem Tabar
//

/*
Some Personal Notes For Later:
 
Smoothing, also called blurring, is a simple and frequently used image processing operation.

 There are many reasons for smoothing. In this homework part we will focus on smoothing in order to reduce noise on the country image
 
 To perform a smoothing operation we will apply a filter to our image. The most common type of filters are linear, in which an output pixel's value (i.e. g(i,j)) is determined as a weighted sum of input pixel values (i.e. f(i+k,j+l)). Weightes sum is calculated as g(i,j) = cumsum(f(i+k,j+l)*h(1,k)) for k,1 where h(k,1) is called the kernel, which is nothing more than the coefficients of the filter.
 
 Above operation helps to visualize a filter as a window of coefficients sliding across the image.There are many types of filters that can be applied to the images in order to reduce the noise.
 
 Gauissian Filter: Probably the most useful filter (although not the fastest). Gaussian filtering is done by convolving each point in the input array with a Gaussian kernel and then summing them all to produce the output array.
 
 Median Filter: The median filter run through each element of the signal (in this case the image) and replace each pixel with the median of its neighboring pixels (located in a square neighborhood around the evaluated pixel).
 
 Bilateral Filter: Some filtering alogirthms does not only dissolve the noise but also smoothes the edges.To avoid edge smoothening we can use bilateral filter.

 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*This function calls the medianBlur() filtering function of opencv with the kernel size taken as an integer argument and displays the resulting denoised version of the original image
*/
void MedianBlurFilter(Mat original_image, int kernel_size_median_filter) {
    
    //Define a new matrix for the new filtered image
    Mat filtered_image;
    
    //Call the openCV medianBlur() function with passed parameters
    medianBlur(original_image, filtered_image, kernel_size_median_filter);
    
    //Show the filtered image to the user
    imshow("Median BlurFiltered Image", filtered_image);
    
    //Write the image into your local repository
    //Most of the time it requires to define a path of your local repository
    //If it is not working please define a path
    //In my case my path is: "/Users/cemtabarmacbook/Desktop/ComputerVisionLab2Part2/ComputerVisionLab2Part2/MedianBlurFilteredImage.jpg"
    //Write the new image for report purposes
    //You can uncomment the below code to obtain the output in your local
    //imwrite("MedianBlurFilteredImage.jpg", filtered_image);
}

/*This function calls the gaussianBlur() filtering function of opencv with the kernel size and sigma taken as integer arguments and displays the denoised version of the original image
*/
void GaussianBlurFilter(Mat original_image, int kernel_size_gaussian_filter, int sigma_gaussian_filter) {
    //Define a new matrix for the new filtered image
    Mat filtered_image;
    
    //Call the openCV GaussianBlur() function with passed parameters
    //Since sigma(x) = sigma(y) we are passing the same sigma value to the function
    //Define the size as Size() == kernel_size_gaussian_filter ** 2
    GaussianBlur(original_image, filtered_image, Size(kernel_size_gaussian_filter, kernel_size_gaussian_filter), sigma_gaussian_filter, sigma_gaussian_filter);
    
    //Show the filtered image to the user
    imshow("Gaussian Blur Filtered Image", filtered_image);
    
    //Write the image into your local repository
    //Most of the time it requires to define a path of your local repository
    //If it is not working please define a path
    //In my case my path is: "/Users/cemtabarmacbook/Desktop/ComputerVisionLab2Part2/ComputerVisionLab2Part2/GaussianBlurFilteredImage.jpg"
    //Write the new image for report purposes
    //You can uncomment the below code to obtain the output in your local
    //imwrite("GaussianBlurFilteredImage.jpg", filtered_image);
}

/*This function calls the bilateralFilter() filtering function of opencv with the sigma sigma_r_bilateral_filter and sigma sigma_s_bilateral_filter taken as integer arguments and displays the denoised version of the original image
 Kernel size will be defined according to 6*sigma(s) rule
*/
void BilateralFilter(Mat original_image, int sigma_r_bilateral_filter, int sigma_s_bilateral_filter) {
    
    //Define a new matrix for the new filtered image
    Mat filtered_image;
    
    //Call the openCV GaussianBlur() function with passed parameters
    //Pass the sigma(r) and sigma(s) values accordingly
    //Kernel size is chosen as 6 times sigma(s) according to the rule but you can also give another kernel size parameter if you wish
    bilateralFilter(original_image, filtered_image, 6 * sigma_s_bilateral_filter, sigma_r_bilateral_filter, sigma_s_bilateral_filter);
    
    //Show the filtered image to the user
    imshow("Bilateral Filtered Image", filtered_image);
    
    //Write the image into your local repository
    //Most of the time it requires to define a path of your local repository
    //If it is not working please define a path
    //In my case my path is: "/Users/cemtabarmacbook/Desktop/ComputerVisionLab2Part2/ComputerVisionLab2Part2/GaussianBlurFilteredImage.jpg"
    
    //Write the new image for report purposes
    //You can uncomment the below code to obtain the output in your local
    //imwrite("BilateralFilteredImage.jpg", filtered_image);
}


int main(int argc, const char * argv[]) {
    
    //There is no steps as given in the previous parts but you can follow the steps in some sense at below
    //In the question part it is given that there are three types of filters that needs to be applied on the original image in order to get the denoised version of the image.
    //As explained above some filtering algorithms are preferred for this purpose. You can follow the each GaussianFilter, MedianFilter and BilateralFilter operations below.
    //Each algorithm requires some type of parameters for denoising operation. So while changin the algorithm effects and results in a better denoised image also chosen parameters affects the performence of the applied filter algorithm
    
    //MedianBlur filter only takes kernel size as the parameter
    //GaussianBlur filter takes kernel size and sigma value(assume that sigma(x) == sigma(y))
    //Bilateral filter takes sigma(r) and sigma(s). Kernel size is fixed (assume it is 6 times sigma(s))
    
    //Application of these filter will be handled by individual functions
    //Each filter is defined as a function above the main
    //So whenever we use the filter function will be called with the required parameters
    
    //Within the main parameters are defined and passed it to the filter functions accordingly
    
    //Loading the noisy "portello-noisy.png" image to a Matrix as given in the assignment instructions and deining as input_image
    //Since we are doing denoising operation we need to pass a noisy image
    //There are 2 options within the LAB2 data folder. You can either use "poretllo-nosiy.png" or "dei-noise.jpg"
    //In some cases only giving the name of image does not work, that is why you need to define the path of the image too.
    //Path for the image: /Users/cemtabarmacbook/Desktop/Homework1_Omer_Cem_Tabar_2081169/ComputerVisionLab2Part2/ComputerVisionLab2Part2/portello-noisy.png
    Mat original_image = imread("/Users/cemtabarmacbook/Desktop/COMVIS/Homework1_Omer_Cem_Tabar_2081169/ComputerVisionLab2Part2/ComputerVisionLab2Part2/portello-noisy.png");
    
    //Assigning the required parameters for the filter functions
    //Try different values in order to get better results
    
    //Parameters tried as 5,5,5,80,50 in order
    
    int kernel_size_median_filter = 5;
    int kernel_size_gaussian_filter = 5;
    int sigma_gaussian_filter = 5;
    int sigma_r_bilateral_filter = 80;
    int sigma_s_bilateral_filter = 50;
    
    
    //Call the filter functions with given parameters
    //Each functions outputs the denoised version of the original image after the denoising operation
    MedianBlurFilter(original_image, kernel_size_median_filter);
    GaussianBlurFilter(original_image, kernel_size_gaussian_filter,sigma_gaussian_filter);
    BilateralFilter(original_image, sigma_r_bilateral_filter, sigma_s_bilateral_filter);
    
    
    waitKey(0);
    return 0;
    
}
