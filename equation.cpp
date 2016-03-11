#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;


// Function to solve linear equation with three variables
// ax + by + cz + d = 0 
// lx + my + nz + k = 0 
// px + qy + rz + s = 0 

vector<double> solve_linear (double a,double b,double c,double d,double l,double m,double n,double k,double p,double q,double r,double s) {
double D,x,y,z;

 D = (a*m*r+b*p*n+c*l*q)-(a*n*q+b*l*r+c*m*p);
 x = ((b*r*k+c*m*s+d*n*q)-(b*n*s+c*q*k+d*m*r))/D;
 y = ((a*n*s+c*p*k+d*l*r)-(a*r*k+c*l*s+d*n*p))/D;
 z = ((a*q*k+b*l*s+d*m*p)-(a*m*s+b*p*k+d*l*q))/D;

vector<double> result;
result.push_back(x);
result.push_back(y);
result.push_back(z);

return result;
}
