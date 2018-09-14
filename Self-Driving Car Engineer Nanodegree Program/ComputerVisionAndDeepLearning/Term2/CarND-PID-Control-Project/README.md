# CarND-Controls-PID

Started with Sebastian's numbers. I had to lower the throttle to 0.1
Also, I add few lines for debug. This would help to see the impact of speed and angle.

# Output:
Successfully ran the file within the road for about 15 minutes (if the inputs are coming every second - the log-video is 960 seconds = 15 minutes)

# Attachments:
Video: 0-2_0-004_ 3-0_0-1.mp4 that includes both the simulator and the terminal output.

# Possible enhancements:
* Car is oscillating:
* * This suggests that the "differential" needs to be increased with respect to "proportional"
* Turns: Sometimes steering wrong way:
* * Screen shot: 0-2_0-004_ 3-0_0-1_min16.png we can clearly see that the "integration" part is causing this behavior. The integrator part needs to be lowered
* Driving at a higher speed:
* * The higher the speed the less turns you need. So, considering lowering the 3 parameters
* Varying speed:
* * The speed could be inversely proportion to the erro "cte".
* Twiddle:
* * Twiddle on low speed (0.1) to get better values, then increase the speed (0.2) re-twiddle, increase the speed  and so on.
