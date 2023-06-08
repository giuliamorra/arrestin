# rotation angle

This project involves the calculation of the rotation angle of a 3D point around a given axis. 
The rotation axis of a protein domain relative to another can be calculated in various manners.

For the arrestin project, we used the HingeFinder code of Wriggers & Schulten, Proteins 1997, 29, 1-14.

The code is myrotation.c.

Input is given by the coordinates of the axis (i.e. two 3D positions, file "axis.dir.dat" ) and by the trajectory of the point (file "angle.series.dat"). The latter can e.g. be the center of mass of a protein domain.
