
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc,char *argv[]){

  int rank, size;
  int numberOfPoints= 10000000;
  int localCount=0;
  int totalCount=0;
  double startTime,endTime;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  //start timer
  startTime=MPI_Wtime();

  int pointPerProcess= numberOfPoints/size;
  //Random Seed
  srand(time(NULL)+rank);

  for(int i=0;i<pointPerProcess;i++){

    double x= (double)rand()/RAND_MAX;
    double y= (double)rand()/RAND_MAX;

    if(x*x+y*y<1){
      localCount++;
    }

  }
  MPI_Reduce(&localCount,&totalCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  if(rank==0){
    double pi= 4.0*totalCount/numberOfPoints;
    printf("Pi is %f\n",pi);
  }
 endTime=MPI_Wtime();
  if(rank==0){
    printf("Time taken %f\n",endTime-startTime);
  }
  MPI_Finalize();
  return 0;


}
