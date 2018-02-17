# **Vehicle detection**

## Khaled Zoheir - P5: [email:](mailto:khaled.zoheir.kz@gmail.com)

## Writeup


**Vehicle Detection Project**

The goals / steps of this project are the following:

* Reading dataset
* Training:
* * Features selection - Histogram of Oriented Gradients (HOG)
* * Fitting - training
* Searching:
* * Sliding window searched
* * Description
* * Examples
* video
* * False positives
* Discussion
--------------------------------
* Reading dataset:
The code for this step is contained in the cell (3) of the IPython notebook
It uses the utility functions found in cells (1 and 2)

I started by reading in all the `vehicle` and `non-vehicle` images.
example of one of each of the `vehicle` and `non-vehicle` classes:

![Original Image](./Sample_0.png)
![Original Image](./Sample_1.png)
![Original Image](./Sample_2.png)

-------------------------------
* Training:
* * Features selection - Histogram of Oriented Gradients (HOG)
* * * The code for this step (getting vehicle signature) is contained in the cells(4-8) of the IPython notebook
* * * The vehicle signature is composed of 3 components:
* * * * Spatial Features: image pixel values after resizing and flattening
* * * * Color Histogram Features: A color histogram totals the number of pixel values that fall into evenly-distributed bins for each color channel. I chose to use 16 color bins parameter .
* * * * HOG (Histogram of Oriented Gradients) Features:
* * * * * My plan was to focus on this feature.
* * * * * After visualizing the data, it seemed to me that we can mix channel and even 4 or 5 channels not only 3.
* * * * *
* * * * * Unfortunately, I didn't have enough time to explore this idea. The code was partially modified to accept a variable number of channels from different systems: This parameter is called:
* * * * * * self.`combined_channels`  (replacing `color_space`) = [['RGB',[0]],['YCrCb',[0,2]],['HSV',[0]],['LUV',[0,1]]] # 6 channels! instead of 3'RGB' #'YCrCb' [['YCrCb',[0,1,2]]] = R from RGB, Y and Cb from YCrCb, etc...
* * * * * HOG images to select the best channels (in the markdown only 1 car. In the ipynb - 5 different cars):
![Original Image](./Images/Car__1__Color_HLS__orient_8__spatial_size_16__pic_cel_8__cell_block_2.png)
![Original Image](./Car__5__Color_HSV__orient_8__pic_cel_8__cell_block_2.png) 
![Original Image](./Car__5__Color_LUV__orient_8__pic_cel_8__cell_block_2.png)
![Original Image](./Car__5__Color_HLS__orient_8__pic_cel_8__cell_block_2.png)
![Original Image](./Car__5__Color_YUV__orient_8__pic_cel_8__cell_block_2.png)
![Original Image](./Car__5__Color_YCrCb__orient_8__pic_cel_8__cell_block_2.png)

A table is made showing the acceptable channels for each car:
![Original Image](./HOG_features_visual_selection.png)

* * * * Chosen channels for the first iteration: YCr (from YCrCb) and H from (HLS)
* * * * Note 1: The code is not yet fully ready to handle different numbers of Channels than 3 (less for fast response, or more for high precision.
* * * * Note 2: There is a risk of actually getting too many false detection in case of higher number than 3.



HOG (Histogram of Oriented Gradients) Features
I extracted HOG features from the training images with Udacity course function
using the following parameters:
• orient_param=8
• pix_per_cell_param=8
• cells_per_block_param=2
And this was the result for a vehicle and non-vehicle example.

The code

* Perform a Histogram of Oriented Gradients (HOG) feature extraction on a labeled training set of images and train a classifier Linear SVM classifier
* Optionally, you can also apply a color transform and append binned color features, as well as histograms of color, to your HOG feature vector.
* Note: for those first two steps don't forget to normalize your features and randomize a selection for training and testing.
* Implement a sliding-window technique and use your trained classifier to search for vehicles in images.
* Run your pipeline on a video stream (start with the test_video.mp4 and later implement on full project_video.mp4) and create a heat map of recurring detections frame by frame to reject outliers and follow detected vehicles.
* Estimate a bounding box for vehicles detected.

[//]: # (Image References)
[image1]: ./examples/car_not_car.png
[image2]: ./examples/HOG_example.jpg
[image3]: ./examples/sliding_windows.jpg
[image4]: ./examples/sliding_window.jpg
[image5]: ./examples/bboxes_and_heat.png
[image6]: ./examples/labels_map.png
[image7]: ./examples/output_bboxes.png
[video1]: ./project_video.mp4

## [Rubric](https://review.udacity.com/#!/rubrics/513/view) Points
### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one.  You can submit your writeup as markdown or pdf.  [Here](https://github.com/udacity/CarND-Vehicle-Detection/blob/master/writeup_template.md) is a template writeup for this project you can use as a guide and a starting point.  

You're reading it!

### Histogram of Oriented Gradients (HOG)

#### 1. Explain how (and identify where in your code) you extracted HOG features from the training images.

The code for this step is contained in the first code cell of the IPython notebook (or in lines # through # of the file called `some_file.py`).  

I started by reading in all the `vehicle` and `non-vehicle` images.  Here is an example of one of each of the `vehicle` and `non-vehicle` classes:

![alt text][image1]

I then explored different color spaces and different `skimage.hog()` parameters (`orientations`, `pixels_per_cell`, and `cells_per_block`).  I grabbed random images from each of the two classes and displayed them to get a feel for what the `skimage.hog()` output looks like.

Here is an example using the `YCrCb` color space and HOG parameters of `orientations=8`, `pixels_per_cell=(8, 8)` and `cells_per_block=(2, 2)`:


![alt text][image2]

#### 2. Explain how you settled on your final choice of HOG parameters.

I tried various combinations of parameters and...

#### 3. Describe how (and identify where in your code) you trained a classifier using your selected HOG features (and color features if you used them).

I trained a linear SVM using...

### Sliding Window Search

#### 1. Describe how (and identify where in your code) you implemented a sliding window search.  How did you decide what scales to search and how much to overlap windows?

I decided to search random window positions at random scales all over the image and came up with this (ok just kidding I didn't actually ;):

![alt text][image3]

#### 2. Show some examples of test images to demonstrate how your pipeline is working.  What did you do to optimize the performance of your classifier?

Ultimately I searched on two scales using YCrCb 3-channel HOG features plus spatially binned color and histograms of color in the feature vector, which provided a nice result.  Here are some example images:

![alt text][image4]
---

### Video Implementation

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (somewhat wobbly or unstable bounding boxes are ok as long as you are identifying the vehicles most of the time with minimal false positives.)
Here's a [link to my video result](./project_video.mp4)


#### 2. Describe how (and identify where in your code) you implemented some kind of filter for false positives and some method for combining overlapping bounding boxes.

I recorded the positions of positive detections in each frame of the video.  From the positive detections I created a heatmap and then thresholded that map to identify vehicle positions.  I then used `scipy.ndimage.measurements.label()` to identify individual blobs in the heatmap.  I then assumed each blob corresponded to a vehicle.  I constructed bounding boxes to cover the area of each blob detected.  

Here's an example result showing the heatmap from a series of frames of video, the result of `scipy.ndimage.measurements.label()` and the bounding boxes then overlaid on the last frame of video:

### Here are six frames and their corresponding heatmaps:

![alt text][image5]

### Here is the output of `scipy.ndimage.measurements.label()` on the integrated heatmap from all six frames:
![alt text][image6]

### Here the resulting bounding boxes are drawn onto the last frame in the series:
![alt text][image7]



---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the pipeline might fail and how I might improve it if I were going to pursue this project further.  
