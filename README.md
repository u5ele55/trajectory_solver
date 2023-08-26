# trajectory_solver
Determine parameters of cannon to shoot through certain point. This repo contains modeling of a ballisctic trajectory and different methods to find its parameters so that cannonball passes through a given point (target). 

## Approaches

### Gradient descent
Using gradient descent we will minimize function of two variables - start velocity of an object. Function will map velocity to distance from object to target point. Then we can numericacally calculate gradient of such function to minimize it. Also this method can get beyond given boundaries and find the best solution. 
#### Result:
On all tests fixed step size was used. Function values never exceeded 0.1. 
<br>

| m=5.5; r=0.11 | m=148.5; r=0.32 |
| ------------- | ------------- |
|![image](https://github.com/u5ele55/trajectory_solver/assets/99137907/90fee44e-b1f5-4358-91d1-bec57bde9c97)|![image](https://github.com/u5ele55/trajectory_solver/assets/99137907/b1c306ef-0fd5-41fb-9a87-1b3c68720309)|
| distance = 4.6e-7 | distance = 5.5e-6 |
<br>

<hr>

### Random Search
Just choose random parameters from search space a couple of times (few tens or hundreds) and choose the best out of them. If search space is out of real parameters, this method will imply very bad results. 
#### Result:
Results vary dractically and really depend on given boundaries.

| m=148.5; r=0.32 | m=148.5; r=0.32 |
| ------------- | ------------- |
|![image](https://github.com/u5ele55/trajectory_solver/assets/99137907/677835c8-ae0b-4865-aab5-660d848192b2) | ![image](https://github.com/u5ele55/trajectory_solver/assets/99137907/325e4bf5-4594-436c-b7ea-76624ee42593)|

