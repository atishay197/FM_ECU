# ECU Code for the Formula Manipal Electric Car

The Electronic Control Unit (ECU) in automobile are used for safety, performance and milage improvement purposes. Correct mapping of the vehicle to optimize its performance is really difficult due to changing external conditions and limitations of the ECU to understand these changing conditions. In case of a racecar, improving the performance of the car is very important. Manual mapping techniques are time taking and consume a lot of resources. The proposed approach is to design an ECU such that it continuously monitors the rear wheel slip of the car and modify the map while the car is running based on the given slip values. Vehicle state is also determined using neural network at specific time intervals keeping track of the output torque and the previous state of the vehicle. This state tracking also allows us to modify the map based on different states of the car.

The following is the high level design for the ECU: [Link](https://drive.google.com/file/d/1Ek29i5EYJSvtTnkKLyYv8Y_lLNgcHCPF/view?usp=sharing)

## Introduction

Unlike driverless electric vehicle where performance is the main issue, in an electric vehicle driven by a semi-professional/professional driver on a racetrack performance is one of the main concerns here. In the proposed approach of map modification and vehicle state monitoring using machine learning vehicle state is continuously kept track of via convolutional neural networks and continuous slip monitoring is done which is used as a multiplier for instantaneous output torque calculation but is also stored, clustered and used for map modification to decrease the fraction decrease in multiplier as more and more slip data is collected and clustered. Other parameters in the ECU include a 5 dimensional map which considers the throttle position, wheel load, steering angle, wheel slip, and vehicle velocity. Each of these dimensions have 10 divisions either linearly, logarithmically or polynomially depending on its needs. This map data is continually being modified by the algorithm to give better torque output preventing slip and improving performance of the car with time.

## Objective
The main aim of this project is to design an ECU which will adapt to changing conditions and improve performance of an electric car with time using clustering and convolutional neural networks.

## Methodology
The ECU has been modularized into many components adn run through a series of calculations and data stores to finally receive the value from the 5-D map. The clustering module and Neural Network help in map modification.

## Results
One of the most important aspects of this code was to allow it to be used with the desired motor controller at 100Hz. After doing a small simulation of 450s and then measuring the time taken by the code loop to run for 15s, it was seen that the minimum Frequency of the running code was 2.03kHz. And we started with a linear map initially and allowed the algorithm to change this map depending on the input data from the sensors, and there were some changes seen in the map. 

## Conclusion
The developed code can not only help us generate output torque for both the rear right and the rear left wheel on time, it can also help us improve the torque map of the car given ample amount of testing is done before the main race events. 

## Scope of Future Work
The current design of the ECU limits its usage to 2 wheel drive only. This can be extended to 4 wheel drives allowing us not only greater control of the car but also allowing the electric car to maintain the desired pitch, wheel loads and slip necessary for improving its performance. Also with development of custom ECU boards a lot of parameters can be calculated on a different processor and multiprocessor architecture can be used for state determination and storage thus removing the time and space constraint from the code.

## References:
1. V. Wouk, “Hybrids: Then and now,” IEEE Spectr., vol. 32, no. 7, pp. 16–21, Jul. 1995.
2. C. C. Chan, “An overview of electric vehicle technology,” Proc. IEEE,vol. 81, no. 9, pp. 1202–1213, Sep. 1993.
3. F. A. Wyczalek, “Hybrid electric vehicles: Year 2000 status,” IEEE Aerosp. Electron. Syst. Mag., vol. 16, no. 3, pp. 15–25, Mar. 2001.
4. C. C. Chan, “The state of the art of electric and hybrid vehicles,” Proc.IEEE, vol. 90, no. 2, pp. 247–275, Feb. 2002.
5. P. K. Wong, "Compensation Map Calibration of Engine Management Systems Using Least-Squares Support Vector Committee Machine and Evolutionary Optimization." Vehicle Engineering (VE) 1.1 (2013): Vehicle Engineering.
6. Y. J. Zhai and D. L. Yu. 2007. A Neural Network Model Based MPC of Engine AFR with Single-Dimensional Optimization. In Proceedings of the 4th international symposium on Neural Networks: Advances in Neural Networks (ISNN '07), Springer- Verlag, Berlin, Heidelberg, 339-348.
