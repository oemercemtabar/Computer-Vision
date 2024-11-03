//
//  main.cpp
//  ComputerVisionLab4
//
//  Created by Cem Tabar on 10.06.2023.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <tuple>
#include <iostream>
using namespace cv;
using namespace std;

std::vector<Mat> Images() {
    
    //Defining paths for the corrupted image and pathces
    string corrupted_image_path = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/image_to_complete.jpg";
    string patches[8];
    patches[0] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_0.jpg";
    patches[1] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_1.jpg";
    patches[2] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_2.jpg";
    patches[3] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_3.jpg";
    patches[4] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_t_0.jpg";
    patches[5] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_t_1.jpg";
    patches[6] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_t_2.jpg";
    patches[7] = "/Users/cemtabarmacbook/Desktop/ComputerVisionLab4/international/patch_t_3.jpg";
    //Loading the corrupted image
    Mat corrupted_image = imread(corrupted_image_path);
    //Collect the patches in a vector
    std::vector<Mat> image_and_patches;
    image_and_patches.push_back(corrupted_image);
    //Loading the patches for corrupted image
    Mat patch_0 = imread(patches[0]);
    image_and_patches.push_back(patch_0);
    Mat patch_1 = imread(patches[1]);
    image_and_patches.push_back(patch_1);
    Mat patch_2 = imread(patches[2]);
    image_and_patches.push_back(patch_2);
    Mat patch_3 = imread(patches[3]);
    image_and_patches.push_back(patch_3);
    //Loading the patches it is transformed for the corrupted image
    Mat patch_t_0 = imread(patches[4]);
    image_and_patches.push_back(patch_t_0);
    Mat patch_t_1 = imread(patches[5]);
    image_and_patches.push_back(patch_t_1);
    Mat patch_t_2 = imread(patches[6]);
    image_and_patches.push_back(patch_t_2);
    Mat patch_t_3 = imread(patches[7]);
    image_and_patches.push_back(patch_t_3);
    //Return the readed corrupted image and patches as a whole
    return image_and_patches;
}

void imageAndPatchShow(std::vector<Mat>images) {
    //Show the user all readed corrupted image and patches
    imshow("Corrupted Image", images[0]);
    imshow("Image Patch Number 0", images[1]);
    imshow("Image Patch Number 1", images[2]);
    imshow("Image Patch Number 2", images[3]);
    imshow("Image Patch Number 3", images[4]);
    imshow("Image Patch Transformed Number 0", images[5]);
    imshow("Image Patch Transformed Number 1", images[6]);
    imshow("Image Patch Transformed Number 2", images[7]);
    imshow("Image Patch Transformed Number 3", images[8]);
}

//////////////////////////////////////////////// SIFT for Corrupted Image and Patches /////////////////////////////////////////////////////////

std::tuple<std::vector<KeyPoint>, Mat> siftReturner(Ptr<SIFT> sift,std::vector<Mat> images, int index) {
    //Create keypoints vector for the keypoints in the corrupted image
    std::vector<KeyPoint> keypoints;
    //Create Descriptor matrix for the features within the corrupted image
    Mat descriptors;
    // LEARNED IN THE LAB04 AND REFERENCED FROM THE lab04_2023_slides.pdf -> Feature2D Class detectAndCompute() implementation.
    sift -> detectAndCompute( images[index], noArray(), keypoints, descriptors );
    return {keypoints,descriptors};
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void visualizeKeypoints(std::vector<Mat> images,int index, std::vector<KeyPoint> keyPnts){
    //Implementation crosschecked from https://docs.opencv.org/4.x/da/df5/tutorial_py_sift_intro.html
    Mat OutputImage;
    drawKeypoints(images[index], keyPnts, OutputImage);
    imshow("Image with index" + to_string(index) + " ", OutputImage);
}

void drawMatchPoints(std::vector<Mat> images,int indexImage,int indexPatch, std::vector<KeyPoint> keyPntsImg,std::vector<KeyPoint> keyPntsPatch,std::vector<DMatch> matches){
    Mat MatchesBetween;
    //Crosschecked the implementation from "https://docs.opencv.org/3.4/d4/d5d/group__features2d__draw.html#ga7d77c42960a2916217ddf202173f9ed2"
    drawMatches(images[indexImage],keyPntsImg,images[indexPatch],keyPntsPatch,matches,MatchesBetween);
    imshow("SIFT Matches Between Corrupted Image and Patch",MatchesBetween);
}

float getMinimumDistance(std::vector<DMatch>matches){
    float min_distance = matches[0].distance;
    for (int i = 0; i < matches.size(); i++)
    {
        if(matches[i].distance <= min_distance){
            min_distance = matches[i].distance;
        }
        else{
            min_distance = min_distance;
        }
    }
    return min_distance;
}


int main(int argc, const char * argv[]) {
    
    /// /////////////////////////////////////////////////////////////////////////////////////// STEP 1 //////////////////////////////////////////////////////////////////////////////////////////////
    //STEP 1 : Load the corrupted image and the patches from one of the provided datasets.
    std::vector<Mat>imageCollector = Images();
    
    //Check whether all required images and patches can be loaded correctly
    if(imageCollector.size() != 9){
        cout << "There is a problem while loading the images!!!" << endl;
    }
    //You can uncomment this part whenever you need the visualization of the original images before processing them
    //imageAndPatchShow(imageCollector);
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    
    
    /// /////////////////////////////////////////////////////////////////////////////////////////// STEP 2 /////////////////////////////////////////////////////////////////////////////////////////////
    //STEP 2: Extract SIFT features from the image
    //My OpenCV version is 4.7.0
    
    
    //Initiate the SIFT detector
    // LEARNED FROM THE lab04_2023_slides.pdf -> SIFT() implementation.
    static Ptr<SIFT> sift = cv::SIFT::create();
    Mat lastImage = imageCollector[0].clone();
    //Call siftReturner function for keypoints and descriptors
    auto [keyPointsCorruptedImage, DescriptorsCorruptedImage] = siftReturner(sift, imageCollector, 0);
    
    //You can uncomment the below part in order to visualize keypoints
    //visualizeKeypoints(imageCollector, 0, keyPointsCorruptedImage);
    
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    /// /////////////////////////////////////////////////////////////////////////////////////////// STEP 3 /////////////////////////////////////////////////////////////////////////////////////////////
    //STEP 3: Extract SIFT features from the patches (SIFT features requires OpenCV≥4.4)
    //Since we have collected all the patches in a vector, instead of applying sift one-by-one in a long way iterate on the patches array with loop then apply sift each of the patch.
    
    std::vector<Mat> refinedPatchesCollector;
    //Since there are 8 patches in total loop 8 times
    for (int i = 1; i <= 8; i++){
        //Call siftReturner function for keypoints and descriptors
        auto [patchKeyPoints, patchDescriptors] = siftReturner(sift, imageCollector, i);
        //You can uncomment the below part in order to visualize keypoints
        //visualizeKeypoints(imageCollector, i, patchKeyPoints);
    /// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    ////////////////////////////////////////////////////////////////////////////////// STEP 4 ///////////////////////////////////////////////////////////////////////////////////////////////////////
        //STEP 4-a: For each patch, compute the match between the image and patch features extracted in (2). For this, OpenCV offers you the cv::BFMatcher class. Remember to use L2 distance for SIFT (the Hamming distance is good for ORB).
        //Define a vector for collecting the matches
        std::vector<DMatch> matchesAll;
        //Create BF Matcher pointer
        static Ptr<BFMatcher> bf_matcher = cv::BFMatcher::create(NORM_L2,true);
        //Find the match between patches and corrupted image
        bf_matcher -> match(DescriptorsCorruptedImage,patchDescriptors,matchesAll);
        
        //STEP 4-b: For each patch, refine the matches found above by selecting the matches with distance less than ratio * min_distance, where ratio is a user-defined threshold and min_distance is the minimum distance found among the matches.
        //Collect the best matches according to the distance
        //Resultant values are 2.64575, 4.3589, 2.82243, 2.23607, 43.3128, 76.7984, 68.374, 45.6508
        //Calculate the minimum distance from the matches
        float minimum_distance = getMinimumDistance(matchesAll);
        std::vector<DMatch> bestMatches;
        for (int i =0; i < matchesAll.size(); i++)
        {
            if (matchesAll[i].distance < 0.7f * matchesAll[0].distance)
            {
                bestMatches.push_back(matchesAll[i]);
            }
        }
        
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    ////////////////////////////////////////////////////////////////////////////////// STEP 5 ///////////////////////////////////////////////////////////////////////////////////////////////////////
        
    //STEP 5: You can assume the images and patches are linked together by an affine transform, using the refined matches, find the transformation between the images. To this end, you can use the RANSAC algorithm. The set of inliers can be computed by using the findHomography() function, with CV_RANSAC as the third parameter (hint: the inliers can be retrieved by using the mask argument).
        //Detect the points according to the best matches that is returned from th BFMatcher
        std::vector<Point2f> pointsMatchedCorruptedImage;
        std::vector<Point2f> pointsMatchedPatch;
        
        for (int i = 0; i < bestMatches.size(); i++)
        {
            //Since descriptors of the corrupted image first passed to the BFMatcher queryIdx will be considered
            //Since descriptors of the patch secondly passed to the BFMatcher trainIdx will be considered
            cv::Point2f corruptedImagePoint = keyPointsCorruptedImage[bestMatches[i].queryIdx].pt;
            cv::Point2f patchImagePoint = patchKeyPoints[bestMatches[i].trainIdx].pt;
            //Collect the points in the Point2f vectors
            pointsMatchedCorruptedImage.push_back(corruptedImagePoint);
            pointsMatchedPatch.push_back(patchImagePoint);
        
        }
        //drawMatchPoints(imageCollector,0,i,keyPointsCorruptedImage,patchKeyPoints,bestMatches);
        Mat findHomographyObject;
        //Check whether the size is bigger than 4 since we are looking for corners, we need at least 4 values as it is stated in the documentation of findHomography()
        if (pointsMatchedCorruptedImage.size() >= 4 && pointsMatchedPatch.size() >= 4)
        {
            // LEARNED IN THE LAB04 AND REFERENCED FROM THE lab04_2023_slides.pdf -> findHomography() implementation.
            //Look for the transformation between patch and corrupted image
            findHomographyObject = findHomography(pointsMatchedPatch, pointsMatchedCorruptedImage, RANSAC);
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
        
    ////////////////////////////////////////////////////////////////////////////////// STEP 6 ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///STEP 6: Using the found homographies overlay the patches over the image in order to fix the corrupted regions.
        Mat resultedImage;
        //In order ot avoid empty findHomogoraphy object, it is safe to check before proceeding.
        //It avoids crushing the program if something went wrong
        if (!findHomographyObject.empty())
        {
            //Warp perspective implementation learned from https://docs.opencv.org/4.x/da/d54/group__imgproc__transform.html
            warpPerspective(imageCollector[i], resultedImage, findHomographyObject, imageCollector[0].size());
            resultedImage.copyTo(imageCollector[0], resultedImage);
            
        }
    }
    // Display the final result
    imshow("After fixation the resultant image", imageCollector[0]);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    
    
    waitKey(0);
    return 0;
}
