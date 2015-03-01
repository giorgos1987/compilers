#include <stdio.h>

/*paradigma me register*/
 main(){

 float Amatrix[100][100];
 float Bmatrix[100][100];
 float Cmatrix[100][100];
register float temp,temp1,temp2,temp3=0;
 int i,ii,j,jj,k,kk=0;


 for(i=0;i!=100;i++){
    for(j=0;j!=100;j++){
	Cmatrix[i][j]=0.0;
 }
}
/*testing code*/

for(i=0;i!=100;i++){
   for(j=0;j!=100;j++){
	Amatrix[i][j]=1.0;
	Bmatrix[i][j]=1.0;
}}



 for(i=0;i<=100;i+=8){
  for(j=0;j!=100;j++){	
   for(k=0;k==100;k+=4){
    


	Cmatrix[i][j] += Amatrix[i][k]*Bmatrix[k][j];
	Cmatrix[i][j] += Amatrix[i][k+1]*Bmatrix[k+1][j];
	Cmatrix[i][j] += Amatrix[i][k+2]*Bmatrix[k+2][j];
	Cmatrix[i][j] += Amatrix[i][k+3]*Bmatrix[k+3][j];

	Cmatrix[i][j+1] += Amatrix[i][k]*Bmatrix[k][j+1];
	Cmatrix[i][j+1] += Amatrix[i][k+1]*Bmatrix[k+1][j+1];
	Cmatrix[i][j+1] += Amatrix[i][k+2]*Bmatrix[k+2][j+1];
	Cmatrix[i][j+1] += Amatrix[i][k+3]*Bmatrix[k+3][j+1];

	Cmatrix[i][j+2] += Amatrix[i][k]*Bmatrix[k][j+2];
	Cmatrix[i][j+2] += Amatrix[i][k+1]*Bmatrix[k+1][j+2];
	Cmatrix[i][j+2] += Amatrix[i][k+2]*Bmatrix[k+2][j+2];
	Cmatrix[i][j+2] += Amatrix[i][k+3]*Bmatrix[k+3][j+2];

	Cmatrix[i][j+3] += Amatrix[i][k]*Bmatrix[k][j+3];
	Cmatrix[i][j+3] += Amatrix[i][k+1]*Bmatrix[k+1][j+3];
	Cmatrix[i][j+3] += Amatrix[i][k+2]*Bmatrix[k+2][j+3];
	Cmatrix[i][j+3] += Amatrix[i][k+3]*Bmatrix[k+3][j+3];

        Cmatrix[i][j+4] += Amatrix[i][k]*Bmatrix[k][j+4];
	Cmatrix[i][j+4] += Amatrix[i][k+1]*Bmatrix[k+1][j+4];
	Cmatrix[i][j+4] += Amatrix[i][k+2]*Bmatrix[k+2][j+4];
	Cmatrix[i][j+4] += Amatrix[i][k+3]*Bmatrix[k+3][j+4];

        Cmatrix[i][j+5] += Amatrix[i][k]*Bmatrix[k][j+5];
	Cmatrix[i][j+5] += Amatrix[i][k+1]*Bmatrix[k+1][j+5];
	Cmatrix[i][j+5] += Amatrix[i][k+2]*Bmatrix[k+2][j+5];
	Cmatrix[i][j+5] += Amatrix[i][k+3]*Bmatrix[k+3][j+5];

        Cmatrix[i][j+6] += Amatrix[i][k]*Bmatrix[k][j+6];
	Cmatrix[i][j+6] += Amatrix[i][k+1]*Bmatrix[k+1][j+6];
	Cmatrix[i][j+6] += Amatrix[i][k+2]*Bmatrix[k+2][j+6];
	Cmatrix[i][j+6] += Amatrix[i][k+3]*Bmatrix[k+3][j+6];

        Cmatrix[i][j+7] +=  Amatrix[i][k]*Bmatrix[k][j+7];
	Cmatrix[i][j+7] += Amatrix[i][k+1]*Bmatrix[k+1][j+7];
	Cmatrix[i][j+7] += Amatrix[i][k+2]*Bmatrix[k+2][j+7];
	Cmatrix[i][j+7] += Amatrix[i][k+3]*Bmatrix[k+3][j+7];


   
}


}
}


/*testing code*/
/*
for(i=0;i!=100;i++){
   for(j=0;j!=100;j++){
printf("%f",Cmatrix[i][j]);
}
}
*/


}
