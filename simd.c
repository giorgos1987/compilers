#include <math.h>
#include <stdio.h>
#include <emmintrin.h> //MMX function use//emmin
#include <limits.h>
#include <pmmintrin.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>  //for cpu_set_t 
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#define M 10
#define N 20


void writedata();
typedef double sseVector __attribute__((__vector_size__(32),__may_alias__));
typedef unsigned long long ticks;

double  Y[N],Taps[M],X[N] __attribute__((aligned(32)));

sseVector a,b,c;


static __inline__ ticks getticks(void)
{
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));

	return (((ticks)a) | (((ticks)d) << 32));
}







int main(){

ticks tick,tick1;
unsigned time = 0;

register __m128d mmTaps,mmX,mmX1,mmX2,mmY;
int i,j,k,t;


cpu_set_t mask;







CPU_ZERO(&mask);
CPU_SET(0,&mask);

if(sched_setaffinity(0,sizeof(mask),&mask) == -1)
       printf("WARNING: Could not set CPU Affinity, continuing...\n");


/*
N= sizeof(X)/sizeof(float);
M= sizeof(Taps)/sizeof(float);
*/
t=0;//mean of time
mmY= _mm_setzero_pd();//midenizoume to mmY tis eksodou

for(t=0;t!=100;t++){
tick = getticks();

for (i=0;i!=N;i+=2){

//mmX1 =_mm_load_ps(X + i);//kanoume load ta 4 stoixia eisodou
mmY =_mm_load_pd(Y + i );//kanoume load ta 4 stoixia eksodou

for (j=0;j!=M;j++){
k=i+j;
mmX =_mm_load_pd(X + k);//kanoume load ta 4 stoixia eisodou
	mmTaps = _mm_load_pd(Taps + j);//kamoume load ta 4 taps
	//prokimenou apoktisi se ka8e epanalipsi ta swsta x(i),x(i+1),x(i+2),x(i+3)
 //mmX = _mm_alignr_epi8(mmX2,mmX1,j);
//mmX = _mm_alignr_epi8(cvtss2si(mmX2),cvtss2si(mmX1),j)
//mmX = _mm_shuffle_pd(mmX1,mmX1,MM_SHUFFLE(3,2,1,0));

	//antigrafoume ta swsta taps ka8e fora 
	mmTaps = _mm_shuffle_pd(mmTaps,mmTaps,_MM_SHUFFLE(j,j,j,j));//antigrafume to idio tap 
	
	mmX = _mm_mul_pd(mmX,mmTaps);
	mmY = _mm_add_pd(mmY,mmX);
}


_mm_store_pd(Y+i , mmY);
_mm_empty();

}

tick1 = getticks();

time = (unsigned)((tick1 - tick)/1662543);
t+=time;
}



printf("\n time in MS %u \n",t/100);

//writedata();


return 0;
}


void writedata(){
int l,i,j,acc,index;

FILE *fp;

fp=fopen("data2.txt","w");

for (l=0;l<M;l++)
fprintf(fp,"%.3f  ",Y[l]);

fclose(fp);


acc=0;



fp=fopen("data1.txt","w");

for (l=0;l<N;l++)
Y[l] = 0.0f;

for(i=0;i<N;i++){
for (l=0;l<10;l++){
X[i] = (float)l;}}


for(i=0;i<M;i++){
Taps[i] =  (float)i;}



for (i=0;i<N;i++){
	acc=0.0;
	for (j=0;j<M;j++){ 
	index=i-j;
	if(index >= 0)
   acc+=Taps[j]*X[index];
}
Y[i]=acc;

//printf("\n %.1f   %.1f %.1f",Y[i],A[i+M*j], X[j]);
}

for (l=0;l<N;l++)
fprintf(fp,"%.3f  ",Y[l]);

fclose(fp);


}



