#include<stdio.h>
void main(int argc, char* argr[]){
   int pid;
   pid = fork();
   if(pid < 0) {
      //fork失敗之處理
      fprintf(stderr,"fork failed");
      exit(-1);
   }
   else if(pid == 0) {
      //child process要做的事
      printf("Child\n");
//      execlp("/bin/ls", ls, NULL);
   }
   else {
      //parent要做的事
      wait(NULL);
      printf("Child complete\n");
      exit(0);
   }
}
