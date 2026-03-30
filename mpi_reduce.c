
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]){

  int rank, size;
  int numberOfPoints=1000000;
  int localCount=0;
  int totalCount=0;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

int pointPerProcess= numberOfPoints/size;
//Random Seed
srand(time(NULL)+rank);

//Each process does it's own work 
for(int i=0; i<pointPerProcess;i++){

  double x= (double)rand()/RAND_MAX;
  double y= (double)rand()/RAND_MAX;

  if(x*x+y*y < 1){
    localCount++;
    }
}
//point to point communication
//MPI_Reduce(&localCount,&totalCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

if(rank==0){
  //own calculation
  totalCount=localCount;

  for(int i=1;i<size;i++){
    int temp;
    MPI_Recv(&temp,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    totalCount+=temp;
  }

  double pi= 4.0*totalCount/numberOfPoints;
  printf("Pi is %f\n",pi);	
}
else{
  MPI_Send(&localCount,1,MPI_INT,0,0,MPI_COMM_WORLD);
}

MPI_Finalize();
return 0;

}
