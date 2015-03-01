//#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <xmmintrin.h> //xmm bug
//#include <emmintrin.h> //MMX function use
#include <limits.h>
#include <pmmintrin.h>
//#include <stdlib.h>
//#include <time.h>
#include <sched.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#define M 10
#define N 20


//void writedata();
typedef float sseVector __attribute__((__vector_size__(16),__may_alias__));
typedef unsigned long long ticks;

float  Y[N],Taps[M],X[N] __attribute__((aligned(16)));

sseVector a,b,c;


static inline ticks getticks(void){

unsigned a,b;
asm("cpuid");
asm volatile("rdtsc" : "=a" (a), "=b" (b));

return (((ticks)a) | (((ticks)b) << 32));

}







int main(){

ticks tick,tick1;
unsigned time = 0;

register __m128 mmTaps,mmX,mmX1,mmX2,mmY;
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
mmY= _mm_setzero_ps();//midenizoume to mmY tis eksodou

for(t=0;t!=100;t++){
tick = getticks();

for (i=0;i!=N;i+=4){

//mmX1 =_mm_load_ps(X + i);//kanoume load ta 4 stoixia eisodou
mmY =_mm_load_ps(Y + i );//kanoume load ta 4 stoixia eksodou

for (j=0;j!=M;j++){
k=i+j;
mmX1 =_mm_load_ps(X + k);//kanoume load ta 4 stoixia eisodou
	mmTaps = _mm_load_ps(Taps + j);//kamoume load ta 4 taps
	//prokimenou apoktisi se ka8e epanalipsi ta swsta x(i),x(i+1),x(i+2),x(i+3)
//mmX = _mm_alignr_epi8(mmX2,mmX1,j)); 
mmX = _mm_shuffle_ps(mmX1,mmX1,_MM_SHUFFLE(3,2,1,0));

//mmX = _mm_set1_ps(X[i]);
	//antigrafoume ta swsta taps ka8e fora 
	mmTaps = _mm_shuffle_ps(mmTaps,mmTaps,_MM_SHUFFLE(j,j,j,j));//antigrafume to idio tap 
	
	mmX = _mm_mul_ps(mmX,mmTaps);
	mmY = _mm_add_ps(mmY,mmX);
}


_mm_store_ps((float *)Y , mmY);
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

/*
void writedata(){
int l,i,j,acc;
FILE *fp;

fp=fopen("data2.txt","w");

for (l=0;l<M;l++)
fprintf(fp,"%.3f  ",Y[l]);

fclose(fp);


acc=0;



fp=fopen("data1.txt","w");

for (l=0;l<N;l++)
Y[l] = 0;

 X[] = {
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,
0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f}

Taps[] ={
0.1f,
0.2f,
0.3f,
0.4f,
0.5f,
0.6f,
0.7f,
0.8f,
0.9f,
1.0f,
1.0f,
1.0f,
1.0f,
1.0f,
1.0f,
1.0f}

for (i=0;i<N;i++)
	acc=0.0;
for (j=0;j<M;j++){ 
indx=n-m;
if(index >= 0)
acc+=Taps[j]*X[index];
}
Y[i]=accum;

//printf("\n %.1f   %.1f %.1f",Y[i],A[i+M*j], X[j]);
}

for (l=0;l<N;l++)
fprintf(fp,"%.3f  ",Y[l]);

fclose(fp);


}
*/


