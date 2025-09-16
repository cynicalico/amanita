## 3DSP -- `0x33445350`

```
A   (V3a V3b -- V3)     Add two 3d vectors
B   (V3a V3b -- V3)     Subtract two 3d vectors
C   (V3a V3b -- V3)     Cross porduct of two vectors
D   (V3a V3b -- n)      Dot product of two vector
L   (V3 -- n)           Length of vector
M   (V3a V3b -- V3)     Multiply two 3d vectors
N   (V3 -- V3)          Normalize vector (sets length to 1)
P   (Vdm Vsm -- )       Copy a matrix
R   (Va axis ang -- )   Generate a rotation matrix
S   (Va V3 -- )         Generate a scale matrix
T   (Va V3 -- )         Generate a translation matrix
U   (V3 -- V3 V3)       Duplicate vector on top of stack
V   (V3 -- x y)         Map 3d point to 2d view
X   (V3 Vam -- V3)      Transform a vector using transformation matrix
Y   (Vdm Vam Vam -- )   Multiply two matrices
Z   (n V3 -- V3)        Scale a vector

    All numbers used by these functions are single precision floating point like in extension "FPSP"
    In R, ang is in degrees, axis is an integer (1=x,2=y,3=z)
    Matrices are stored in funge-space as 2-dimenstion 4x4 arrays. the address vector will point to the x1y1 cell. 
```
