#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char** argv)
{
    pid_t child_pid;
    child_pid = fork();           //parent forks a child
    if (child_pid < 0)                  //error occurred
    {
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }

    else if (child_pid == 0)           //ONLY run in child
    {
        pid_t grand_child_pid;
        grand_child_pid = fork();             //child forks a grandchild
        printf("This is process %d\n", getpid());
        wait(NULL);
        if (grand_child_pid == 0) {
          printf("This is process %d\n", getpid());
          FILE *fp;
          fp = popen("/usr/bin/firefox", "r");         //grandchild turns into Mozilla Firefox
          execlp("/bin/ls", "ls", NULL);        //grandchild destroys its own code
        }
    }
    printf("This is process %d\n", getpid());
    wait(NULL);
    return 0;
}




/*Write a C program grand_child.c where a parent creates a child process, the child creates its
 own child technically a grandchild of the original parent.
The grandchild should be able to destroy its own code and
turn into a Mozilla Firefox process (open a Firefox browser).

You can use code from the examples (fork.c etc.) from Canvas.*/
