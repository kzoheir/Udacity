#PID Controller Project
##Khaled Zoheir



### Tunning PID parameters:

**Method:** Try and Error
 Started with the parmeters given by Sebastian and tried the following:
 
* pid.Init(0.2, 0.004, 3.0);   Oscillating and touch the yellow line: Increase 'd'
* pid.Init(0.2, 0.004, 5.0); max_throttle = 0.3;// Still Oscillating and touch the yellow line whrn i_error is high specially -ve: Increase 'd'and lower 'i';
* pid.Init(0.2, 0.001, 6.0); max_throttle = 0.3; // less oscillation and touchs the line. Increase 'p'
* pid.Init(0.3, 0.001, 6.0); max_throttle = 0.3; // Oscillation and do not touchs the line. Increase 'd'
* pid.Init(0.3, 0.001, 7.0); max_throttle = 0.3; // Almost touched the line once. Increase 'd'
* pid.Init(0.4, 0.001, 7.0); max_throttle = 0.3; // still oscillating. There is no point of incresing the 'd' go back to 5.5
* pid.Init(0.5, 0.001, 5.5); max_throttle = 0.3; // Although it didn't touch any line. But high oscillation and big error to the left. Likely the road was large!
* pid.Init(0.5, 0.001, 8.0); max_throttle = 0.3; // Acceptable. Try much higher 'p'
* pid.Init(0.5, 0.001, 20.0); max_throttle = 0.3; // Acceptable.Min CTE: -0.8106 Max CTE: 1.0175. i_error seems to be stable -> good Ki
* pid.Init(0.5, 0.001, 40.0); max_throttle = 0.35; // Oscillating. Even near boarder -> 'd' is too high .Min CTE: -2.3 Max CTE: 1.17
*  pid.Init(0.55, 0.001, 10.0); // max_throttle = 0.35; // Acceptable Oscillating. Min CTE: -1.2535 Max CTE: 2.025. Note: Speed increses with less 'p' even with less throttle (0.3)
*  pid.Init(0.7, 0.001, 8.0); // max_throttle = 0.35; // Acceptable Oscillating. Min CTE: -1.7992 Max CTE: 1.7404
* The log shows a sudden decrease if the 'd' is causing the highest error. Decrease 'p' so that 'd' do not decrease tht much
		/*
		CTE:	0.9647	Min	CTE:	-1.7401	Max	CTE:	1.2642	Steering	Value:	-2.90436				
		42["steer",{"steering_angle":-2.9043626,"throttle":0.3}]														
			count:	792	cte:	1.1898	speed:	13.946	angle:	-25	total	error:	-2.67352			
			Kp:	0.7	p_error:	1.1898	Kd:	8	d_error:	0.2251	Ki:	0.001	i_error:	39.8624	total	error:
			0.83286				1.8008				0.0398624		2.6735224	-2.67352		
		CTE:	1.1898	Min	CTE:	-1.7401	Max	CTE:	1.2642	Steering	Value:	-2.67352				
		42["steer",{"steering_angle":-2.6735224,"throttle":0.3}]														
			count:	793	cte:	1.2913	speed:	13.6138	angle:	-25	total	error:	-1.75706			
			Kp:	0.7	p_error:	1.2913	Kd:	8	d_error:	0.1015	Ki:	0.001	i_error:	41.1537	total	error:
			0.90391				0.812				0.0411537		1.7570637	-1.75706		
		*/
**Finally I choose the following parameters:
pid.Init(0.6, 0.0005, 8.0); // max_throttle = 0.35; // Acceptable Oscillating. Min CTE: -1.7992 Max CTE: 1.7404 **

There are 2 attachements: Video: Udacity/Self-Driving Car Engineer Nanodegree Program/ComputerVisionAndDeepLearning/Term2/CarND-PID-Control-Project/**Videos/Proj4-1-wmv.wmv** and a log file I use to debug and try to understand the impact. Udacity/Self-Driving Car Engineer Nanodegree Program/ComputerVisionAndDeepLearning/Term2/CarND-PID-Control-Project/src/**log.txt**

**Impact of Kp:**: This is the proportional part. It's needed to keep the car on track and avoid getting off the road. However, increasing it causes the car to oscillate around the center (0 error)

**Impact of Kd:**: This is the differential  part. It's purpose is to avoid oscillation (overshooting). However, increasing it too much would result in oversooting near the sides of the road. And accordingly getting off the road.

**Impact of Ki**: This is the integration part. This is needed if the car is not fully symetric. (e.g.: Wheel bias). This usually is kept small and it should stabilize at a certain value. The last log shows it stabiles around 100. ANd with a Ki of 0.0005 this means: 0.05 to throtle to the left direction (-Ki e_i = -0.05 means to the left)

I recorder the max errocs (CTE) on both sides: They are** Min CTE: -1.6226 Max CTE: 1.6927**

**Future work**
* Implement Twiddle algorithm. To better tune the controller.
* IMplement a Speed PID to allow the car to go faster. I.e.: For the car to follow the throttlr.



