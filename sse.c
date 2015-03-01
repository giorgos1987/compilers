#include <math.h>
#include <stdio.h>
#include <emmintrin.h> //MMX function use
#include <limits.h>
#include <pmmintrin.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>  //for cpu_set_t 
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#define M 100
#define N M*M





void writedata();


//the float point array has to be aligned 16 
typedef float sseMatrix __attribute__((__vector_size__(16),__may_alias__));
typedef unsigned long long ticks;



float Amatrix[N],Bmatrix[N],Cmatrix[N] __attribute__((aligned(16)));
 sseMatrix a,b,c;

static __inline__ ticks getticks(void)
{
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));

	return (((ticks)a) | (((ticks)d) << 32));
}
 




int main(){

 ticks tick,tick1,tickh;
 unsigned time = 0;
 int i,j;
 register __m128 num0,num1,num2,num3,num4; // single precision 
 num4 = _mm_setzero_ps();// set sum to zero
 

 



 cpu_set_t mask; //each bit represents a CPU

 CPU_ZERO(&mask); //empty cpu
 CPU_SET(0,&mask); 

 if(sched_setaffinity(0,sizeof(mask),&mask) == -1)
        printf("WARNING: Could not set CPU Affinity, continuing...\n");




 tick = getticks();

printf("\n time in MS %lu\n",tick);
 for(i=0;i!=M;i+=4){
     num3= _mm_setzero_ps();
  for(j=0;j!=M;j+=4){	
	num1 = _mm_load_ps(Amatrix + i + j);// loading for single precision floating point numbers.	
	num2 = _mm_load_ps(Bmatrix + j + i);
        num3 += _mm_mul_ps(num1,num2);  //Parallel multiply single precision floating point values
  }
 _mm_store_ss((float *)Cmatrix, num4);

 }
 tick1 = getticks();

printf("\n time in MS %lu\n",tick1);
 time = (unsigned)((tick1 - tick)/1662543);
//time = __rdtsc() - time;
printf("\n time in MS %u\n",time);


 _mm_empty();

 writedata();

}







void writedata(){


   int l,i,j;
   FILE *fp;

   fp = fopen("data2.txt","w");

   for (l=0;l<N;l++){
	fprintf(fp,"%.3f  ",Cmatrix[l]);
	}
   fclose(fp);



   fp=fopen("data1.txt","w");

   for (i=0;i<N;i++){
	Amatrix[i]=i;
	Cmatrix[i]=0;}

   for (i=0;i<N;i++)
	Cmatrix[i]+=Amatrix[i]*Bmatrix[i];
//printf("\n %.1f   %.1f %.1f",Y[i],A[i+M*j], X[j]);
	

   for (i=0;i<N;i++)
	fprintf(fp,"%.3f  ",Cmatrix[i]);

	fclose(fp);


}
