# CarND-Controls-MPC
Self-Driving Car Engineer Nanodegree Program
###Khaled Zoheir
---

## Model
A simple Kinematic model (ignores tire forces, gravity, mass, etc) was used for the Controller.


	x_[t+1] = x[t] + v[t] * cos(psi[t]) * dt
	y_[t+1] = y[t] + v[t] * sin(psi[t]) * dt
	psi_[t+1] = psi[t] + v[t] / Lf * delta[t] * dt
	v_[t+1] = v[t] + a[t-1] * dt
	cte[t+1] = f(x[t]) - y[t] + v[t] * sin(epsi[t]) * dt
	epsi[t+1] = psi[t] - psides[t] + v[t] * delta[t-1] / Lf * dt

## Timestep Length and Elapsed Duration (N & dt)
Timestep length (N) is chosen to be 8, and timestep frequency (dt) 0.1. Originally N was 10 to give 1 sec ahead. Now, less than 1 sec.

dt: 
	Small for better solution
	Large for less computation (response time)
	Chosen 0.1 to match the actuators delay. Less than this will have ne meaning.

N: 
	Small for less computation. With same dt, this means less way ahead
	Large for better solution. 
	Started with 10. It almost hit the sideroads. Worked much better with 8. May be because my PC is old 
	
## Polynomial Fitting and MPC Preprocessing

 * Transform the given x and y coordinates of the waypoints car frame. The assumption is that the car moves in the (x) direction w.r.t the car. I better model (not tried) is use the delta and LR to get the car heading with respect to the car. Then decompose in x and y w.r.t car.
 * Use polyfit to fit a 3rd order polynomial to the given x and y coordinates representing waypoints.
 * Use polyeval to get both cte and epsi from fit.

 * Cost values were roughtly selected to normalize the cost. I.e.: If cte is between 0-1 and velocity between 100 - 0, having the same cost coefficient means that the cte is almost not been taken into consideration. 
 * More print out to see the real values of the different cost components would give better results
 * After normalization, favoring some costs over the others would be possible.
 * I put more weight on 'cte' and 'epsi' to ensure the car will follow the track sacrifising comfort.

## Model Predictive Control with Latency

Instead of feading the current state to the solver, we predicted the state to be after the latency and feed it to the solver.
