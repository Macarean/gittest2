#include<iostream>
#include<errno.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdlib.h>
#include<string>
using namespace std;

int main(int argc,char*argv[]){
//cout<<"hello"<<endl;
int fd=shm_open("buffer",O_CREAT|O_EXCL|O_RDWR,0600);
if(fd<0){
cout<<"ERROR"<<endl;
perror("shm_open()");
return EXIT_FAILURE;
}
ftruncate(fd,sizeof(int)*7);
int *ptr;
ptr=(int*)mmap(0,sizeof(int)*7,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

cout<<"<"<<"player1"<<" ";
int m=atoi(argv[1]);
cout<<m<<endl;
srand(m);
int p=rand()%100+1;
cout<<"Answer: "<<p<<endl;
ptr[0]=1;
int num=0;

ptr[0]=1;//change
ptr[1]=p;//answer
ptr[3]=100;//range max
ptr[4]=1;//range min
ptr[5]=0;//turn
ptr[6]=0;

while(1){
if(ptr[0]==0){
  cout<<"player1: ";
  if(ptr[2]==ptr[1]&&ptr[6]==0){
    ptr[6]=1;
    cout<<"Bingo! It took you ";
    cout<<ptr[5];
    cout<<" turns!"<<endl;
  }
  else if(ptr[2]==ptr[1]&&ptr[6]==2){
    cout<<"See you!"<<endl;
    break;
  }
  else if(ptr[2]<ptr[1]){
  cout<<"Miss.Too low."<<endl;
  }
  else if(ptr[2]>ptr[1]){
  cout<<"Miss.Too high."<<endl;
  }
  ptr[0]=1;
}
}




munmap (ptr,sizeof(int)*7);
close(fd);
return EXIT_SUCCESS;
}
