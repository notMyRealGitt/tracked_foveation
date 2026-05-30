Stefan Kurćan 2026  


1 focus tracking  
1a mouse tracking  
1b eye tracking  
-- Network --  
1c eye prediction  

2 ROI  
2a simple circular  
2b look into elongated ROI based on speed and direction of tracked movement, as well as expected movement  

3 pipeline  
3a video in  
3aa video from file  
3ab video from camera  

3b ROI in

3c foveated encoding  

3d video streaming out  

-- Network --  
4 pipeline
4a video stream receiving in  
4b video display  

5 quality estimation  
5a subjective, by eye  
5b objective metrics  
5c objective metric for subjective quality  

# Task breakdown

## TODO  
- setup a video playback pipeline, taking in a local video file

- mouse tracking into coordinates
- circular ROI based on coordinates

- add ROI to video pipeline
- find good starting ROI parameters
- do initial quality comparison (subjective, objective)

- use camera feed from PS3 eye as video input

- learn about eye tracking
- add eye tracking
- create physical camera setup
- refine eye tracking calibration
- create initial mobile project setup

- learn about eye movement prediction
- add eye movement prediction
- try elongated ROI (ROI takes in a vector instead of a point)

- separate pipeline into client and server

- find good objective metric for subjective quality
- do final quality comparison
- do measurements

- refine mobile project setup


## NOW  



## NEXT  



## DONE  


