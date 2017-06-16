# CarND-Controls-MPC
Self-Driving Car Engineer Nanodegree Program

---

# Please update the CMake file to point to the correct location of Ipopt. The current CMakeLists.txt expect Ipopt to be installed in <source_directory>/Ipopt/Ipopt/Ipopt

## The Model
The vehicle state consists of current position in x and y coordinates, the heading direction of the vehicle and the speed of the vehicle. The actuations include the steering angle and the acceleration or throttle. Given the heading direction and velocity, the position of the vehicle at a future point in time can be calculated.
We can then estimate a cost function, which is essentially a notion of error from the reference point set. The higher the cross track error, the higher this cost function will be. Additionally we add costs for acceleration, acceleration change, steering and steering change to make the drive smoother. Also to maintain a reference velocity, we add a cost for not reaching a certain velocity.
The final problem is to find a set of steering and acceleration values which will minimize this cost function. This is done by the Ipopt solver. It finds a local minima for the cost function. The cost function itself is non-linear and is optimized by setting up several constraints and providing a function to calculate the position, cte and epsi at different time instances in the future.
The optimizer runs through this and returns the set of values that minimize the cost, and we thus get the steering angle and acceleration.

## Timestep Length and Elapsed Duration
The timestep length was chosen to be 50ms. The idea was to keep this smaller than the latency value, but not too small to have to perform too many computations. The Duration or number of timesteps was set to 15. At longer durations the 3rd order polynomial that was fit was causing unsafe responses from the vehicle as it tried to minimize the error. This could be due to overfitting. We ideally prefer a smooth response and don't need to match the reference pixel for pixel.

## Polynomial Fitting and MPC Preprocessing
A third order polynomial was fit to the reference points and then a third order polynomial was used in the optimizer to calculate the cross track error and steering error. The input reference points were provided in the frame of reference of the external world, these were transformed into the frame of reference of the vehicle, by applying a simple rotation-translation matrix using the vehicles x,y position in the world for translation and the vehicle's heading direction for the rotation.

## Latency
The code has to account for 100ms latency. This is done by doing two things, first the steering response constraint provided to the optimizer indicates that the steering value and acceleration values cannot change for the next 'n' time steps where 'n' is the number of time steps to get to 100ms. In this case 'n=2'. The second thing is to take the result from the optimizer output at 'n' timesteps from the current time. This is done because by the time we apply the actuation 'n' time steps would have passed and we would prefer to apply the actuation from the optimizer for the time step when the actuation actually takes place.
