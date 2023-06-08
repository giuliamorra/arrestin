#include <stdio.h>
#include <math.h>
#include <stdlib.h>
main()

{

int i,  k, l, mu, nu, end_frame;
float  x1[3], x2[3], y;
float alpha, phi, psi, norm, norm1, phi0;
float  omega[3], omega_abs;
float  U[3][3], Uinv[3][3], vec[3], x[1500][3], r[1500][3], t[1500][3];
 FILE *fp, *fp2;

 fp = fopen("axis.dir.dat","r");
 fscanf(fp,"%f %f %f  %f %f %f",&x1[0],&x1[1],&x1[2],&x2[0],&x2[1],&x2[2] );
 fclose(fp);
 /*printf("%lf   %lf\n", x1[0], x1[1]);*/
 /* we calculate the normalized direction of the new axis */

 norm=sqrt((x1[0]-x2[0])*(x1[0]-x2[0]) +(x1[1]-x2[1])*(x1[1]-x2[1]) +(x1[2]-x2[2])*(x1[2]-x2[2]));
 vec[0]= (x1[0]-x2[0])/norm ;
 vec[1]= (x1[1]-x2[1])/norm ;
 vec[2]= (x1[2]-x2[2])/norm ;



 omega_abs = sqrt(vec[0]*vec[0] + vec[1]*vec[1]);

  omega[0] = vec[1]/omega_abs;
  omega[1] = - vec[0]/omega_abs;
  omega[2] = 0.;

  /*  n normalized */
  omega_abs = atan2(omega_abs,vec[2]);
  
 /* we calculate the rotation angle of the new system, given by direction of vec */

 printf("%lf   %lf  %lf  %lf\n", omega_abs, omega[0], omega[1], omega[2]);


 /* read time series of point */

  printf("how many frames? ");
  scanf("%d",&end_frame);


  fp2 = fopen("angle.series.dat","r");
  for(l=0;l<end_frame ;l++){

  fscanf(fp2,"%f %f %f ",&x[l][0],&x[l][1],&x[l][2]);}


 /*translation of reference system*/


  for(l=0;l<end_frame ;l++){
for(mu = 0; mu < 3; mu++)
        {

          t[l][mu] = x[l][mu] - x1[mu];
          }

 /*rotation of reference system */
 construct_rotation_matrix(omega, omega_abs, U);


 for(mu = 0; mu < 3; mu++)
        { y=0.;
         for( k=0; k < 3; k++)
          {

          y += U[mu][k]*t[l][k];

          }
          r[l][mu]=y;
          }

 /*phi angle around z axis */

 norm1=sqrt((r[l][0]*r[l][0]) +(r[l][1]*r[l][1]) +(r[l][2]*r[l][2]));
 /*phi=acos(r[l][0]/norm1); */
 phi=atan2(r[l][1],r[l][0]);
 phi0=atan2(r[0][1],r[0][0]);
 printf("%d   %lf  \n", l,   (phi-phi0)*180/(3.14) );
 }

 }

void construct_rotation_matrix(float axis[3], float psi, float rot_matrix[3][3])
{

  int k, mu;
  float  q[4], norma;

 norma= sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2]);

 if( fabs(norma-1.0) > 0.0001){
    printf("WARNING: Anomalous norm of rotation axis (%lf)\n",norma);
    for(k=0; k < 3; k++) axis[k]=axis[k]/norma;
  }
 psi=1.966846;
  /* use quaternions */
  q[0]=cos(psi/2.0);
  for(k=0; k < 3; k++) {
    q[k+1]=axis[k]*sin(psi/2);
  }


  rot_matrix[0][0]=q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3];
  rot_matrix[0][1]=2*(q[1]*q[2]-q[0]*q[3]);
  rot_matrix[0][2]=2*(q[0]*q[2]+q[1]*q[3]);

  rot_matrix[1][0]=2*(q[0]*q[3]+q[1]*q[2]);
  rot_matrix[1][1]=q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3];
  rot_matrix[1][2]=2*(q[2]*q[3]-q[0]*q[1]);


  rot_matrix[2][0]=2*(q[1]*q[3]-q[0]*q[2]);
  rot_matrix[2][1]=2*(q[0]*q[1]+q[2]*q[3]);
  rot_matrix[2][2]=q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3];




  }

