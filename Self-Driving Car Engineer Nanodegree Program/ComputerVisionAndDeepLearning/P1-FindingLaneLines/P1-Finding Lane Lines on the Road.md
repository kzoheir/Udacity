# **Finding Lane Lines on the Road**

## Khaled Zoheir Writeup: [email:](mailto:khaled.zoheir.kz@gmail.com)

---

**Finding Lane Lines on the Road**

The goals / steps of this project are the following:
* Make a pipeline that finds lane lines on the road
* Reflect on your work in a written report


[//]: # (Image References)
![GrayScaleImage](./examples/grayscale.jpg) "Grayscale"

---

### Reflection

### 1. Describe your pipeline. As part of the description, explain how you modified the draw_lines() function.

My pipeline consisted of 5 steps. First, I converted the images to:
* grayscale [no parameters
* gaussian parameter: gaussian_kernel_sizes
** tried [3, 5, 7,9]:
* canny [canny_low_threshold, canny_high_threshold]
** tried: [50,150] to [100,300] steps [10, 30]
* mask the region of interest [ (130, 500), (450, 320), (470, 320), (900, 500)
* hough lines :
* * rhos = [1, 2, 3]
* *thetas = [1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61] degrees
* * threshold = 15 # minimum number of votes (intersections in Hough grid cell)
* * min_line_len = 2 #minimum number of pixels making up a line
* * max_line_gap = 40 # maximum gap in pixels between connectible line segments

In order to draw a single line on the left and right lanes, I modified the draw_lines() function by trying different techniques:
(Note: 2 lines will be generated. One from the lines with +ve slope (left line) and the second with the lines with -ve slope (right line). Ignore lines parallel to the y-axes: (very little diff in x)
1. Average slope and Y-Intercepts of lines (2 lines: +ve and -ve slopes)
2. Best fit of the points forming the lines (each line contribute by 2 points) [Not done. 3 is better]
3. Best fit of points along the lines. Each line contribute with at least 2 points. It could be more depending on the length of the line
4. Segments Best fit: Only consider the lines with y lies in the lower half of the region of interest

If you'd like to include images to show how the pipeline works, here is how to include an image:
All images are in the notebook!

![alt text][image1]


### 2. Identify potential shortcomings with your current pipeline


One potential shortcoming would be what would happen when ...

Another shortcoming could be ...


### 3. Suggest possible improvements to your pipeline

A possible improvement would be to ...

Another potential improvement could be to ...
