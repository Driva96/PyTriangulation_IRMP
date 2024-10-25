# triangulation_IRMP

This repo contains an implementation of the Iteratively Reweighted MidPoint method (IRMP) for fast multiple view triangulation.  It also contains a comparsion between the IRMP method and doing multiple view triangulation using Ceres. The corresponding paper is now available at [IEEE Xplore](https://ieeexplore.ieee.org/document/8611369).

If you use this code in an academic context, please cite the following paper:

```
@ARTICLE{yangkui_irmp,
author={K. Yang and W. Fang and Y. Zhao and N. Deng},
journal={IEEE Robotics and Automation Letters},
title={Iteratively Reweighted Midpoint Method for Fast Multiple View Triangulation},
year={2019},
volume={4},
number={2},
pages={708-715},
doi={10.1109/LRA.2019.2893022},
ISSN={2377-3766},
month={April},}
```

## Dependencies 
* Ceres 
* Eigen

## Build
```bash
mkdir build
cd build 
cmake -DCMAKE_PREFIX_PATH=/home/dueding/micromamba/envs/adet_3_12 -DCMAKE_INCLUDE_PATH=/home/dueding/micromamba/envs/adet_3_12/include -DCMAKE_LIBRARY_PATH=/home/dueding/micromamba/envs/adet_3_12/lib ..
make # -j4 for parralel build jobs
```

## Run:
```
./triangulation
```

## Import and Use in Python 
```
import triangulation_module as tri # make sure module is in path otherwhise use sys.path and append the directory

triangulation = tri.TriangulationIRMP() # construct Triangulation object 
cam1
triangulation.init(list([]))
```
