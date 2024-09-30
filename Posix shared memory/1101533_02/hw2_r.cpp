#include<iostream>
#include<errno.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<stdlib.h>
#include<string>
using namespace std;
int main(int argc,char*argv[]){

int fd=shm_open("buffer",O_EXCL|O_RDWR,0666);
if(fd<0){
cout<<"ERROR"<<endl;
perror("shm_open()");
return EXIT_FAILURE;
}

int *ptr;
ptr=(int*)mmap(0,sizeof(int)*7,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);




while(1){
  if(ptr[0]==1 && ptr[6]==0 && ptr[5]==0){
    cout<<"<"<<"player2"<<" ";
    int n=atoi(argv[1]);
    cout<<n<<endl;
    srand(n);
    int q=rand()%100+1;
    ptr[2]=q;//player seed
    cout<<"player2: ";
    cout<<"Guess ";
    cout<<ptr[2]<<endl;
    ptr[0]=0;
    ptr[5]+=1;
  }
  else if(ptr[0]==1 && ptr[6]==0){ 
    
    if(ptr[2]<ptr[1]){
      ptr[4]=ptr[2]+1;
      //ptr[2]=(ptr[2]+1+ptr[3])/2;
      ptr[2]=(ptr[2]+1+ptr[3]);
    }
    else if(ptr[2]>ptr[1]){
      ptr[3]=ptr[2]-1;
      ptr[2]=(ptr[2]-1+ptr[4]);
    }
    if(ptr[2]%2==1){
      ptr[2]=ptr[2]/2;
      ptr[2]+=1;
    }else{
      ptr[2]=ptr[2]/2;
    }
    cout<<"player2: ";
    cout<<"Guess ";
    cout<<ptr[2]<<endl;
    ptr[0]=0;
    ptr[5]+=1;
  }
  if(ptr[0]==1 && ptr[6]==1){
    cout<<"player2: ";
    cout<<"Bye!"<<endl;
    ptr[0]=0;
    ptr[6]=2;
    break;
  }
}


munmap (ptr,sizeof(int)*7);
close(fd);
shm_unlink("buffer");
return EXIT_SUCCESS;
}
