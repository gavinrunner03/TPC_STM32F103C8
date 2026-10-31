# Introduction
STM32F103C8 platform baremetal (CMSIS Headers) Transmission Pressure Cable (TPC) controller for Toyota light duty trucks and SUV's that utilized the AISIN A340F transmission. Intended for use with transmission years before 2003, which is the year that Toyota and AISIN switched to a different valve body on the A340F that supported drive-by-wire to natively control transmission pressure using an electrical signal, unlike the cable driven models that this project is intended for. 

# Table of Contents
- Introduction
- Debug Setup
    - Cloning the repository
    - Running the docker image
    - Opening container in VSCode

# Debug Setup
### Cloning the Repository
To clone the repository run git clone ```ssh link or http link```. 

### Runing the Docker Image
To run the docker image you first have to build the docker image. To build the docker image run 

```
$: docker build -t stm32-dev .
```

Then run ```./docker.bash``` from the project root directory. 

### Opening the container in VSCode

To opent he container in VSCode to debug and flash the microcontroller, open VSCode with ```code .``` from the project root directory. Once in VSCode, make sure that the **Cortex Debugger** extension is installed, and (if desired) the **STM32F1** series debugger package extension. Once those are installed use the command pallete, ```ctrl + shift + p```, to search for ***Dev Containers: Attach to Running Container*** and select the container containing **stm** in the title. 