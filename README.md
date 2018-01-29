# CarND Term 2 MPC Project - Model Predictive Control
Self-Driving Car Engineer Nanodegree Program Term 2
---
## MPC

Model Predictive Control is a method to model a vehicle's state and inputs (actuators) to determine the most efficient path through a given set of waypoints.  The state is described by position (x,y), orientation (psi) and velocity (v).  We also add in the actuators, steering angle (delta) and acceleration (a).  Given a time interval (delta t, or dt), we can model the vehicle's motion over a given timestep using update equations (modeled in the code, I won't repeat them here).

Using MPC, we then give a cost to the cross-track error (cte) and steering angle (epsi), and then try to minimize that cost.  We can also add additional costs to our model to penalize or encourage other behaviors in the model, such as speed targets, smooth steering and accleration changes, etc.  Additionally, we can add constraints that will keep values within a certain range.

The Ipopt methods then find the closest 3rd order polynomial equation which will match our waypoints, given costs and constraints.

#### Timestep and Duration

Timestep length (N) and elapsed duration (dt) are two other parameters that we can change.  N is the number of steps we take, or how far forward in time we're estimating, while dt is the increment of time we use.  I chose N = 15 and a timestep of 0.15s which equates to 2.25 total secs.  An extremely large N (I tried values from 10 to 25), would attempt to predict too far out in the future, which might take too much computing resources and be extremely error-prone; while a very small N would possibly not give a good enough prediction.  A too large dt might not be able to change our actuators quickly enough, while one too small would force more calculations and require greater computing resources.

#### MPC Preprocessing and Polynomial Fitting

We had a couple issues to overcome before we could fit the polynomial.  First, we were dealing with two sets of coordinates, the map coordinates and local vehicle coordinates.  Since the waypoints were given in map coordinates, we had to transform those to vehicle coordinates.  Second, the latency also required additional processing, as the model's predictions would be too late if actuators could not act in time.

I decided to tackle the latency first, by using the state equations to predict where the vehicle would be in 100ms (time of latency).  Then I used those coordinates as the initial state of the vehicle and transformed the waypoints into vehicle coordinates from that initial point.  This data was then fed into the model and the polynomial fitted.

#### Summary
Weighting of the cost function elements were additional parameters that we could change.  I tried several different speeds and weights, but ultimately I found the original weights to be fine for the chosen speed of 60 mph.
