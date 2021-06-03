#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

// 0112233
// 1234567

// if0
//  if1
//      if2
//          if4
//          if5
//      if3
//          if6
//          if7

int main()
{
    pid_t pid;

    // print 0
    printf("start pr 0 PID = %d PPID = %d\n", getpid(), getppid());
    //1
    if ((pid = fork()) == -1) printf("Err\n");
    else if(pid == 0)
    {
        //print 1
        printf("\tstart pr 1 PID = %d PPID = %d\n", getpid(), getppid());
        //2
        if ((pid = fork()) == -1) printf("Err\n");
        else if (pid == 0)
        {
            //print 2
            printf("\t\tstart pr 2 PID = %d PPID = %d\n", getpid(), getppid());
            //4
            if ((pid = fork()) == -1) printf("Err\n");
            else if (pid == 0)
            {
                //print 4
                printf("\t\t\tstart pr 4 PID = %d PPID = %d\n", getpid(), getppid());
                printf("\t\t\tend pr 4\n");
                exit(0);
            } else sleep(1);
            //5
            if ((pid = fork()) == -1) printf("Err\n");
            else if (pid == 0)
            {
                //print 5
                printf("\t\t\tstart pr 5 PID = %d PPID = %d\n", getpid(), getppid());
                printf("\t\tend and exec(df) pr 5\n");
                    printf("\n");
                    printf("\t\t\t\t= = = = = run $df\n");
                    execl("/bin/df","df",NULL);
            } else sleep(1);
        exit(0);
        }
        else sleep(3);
        //3
        if ((pid = fork()) == -1) printf("Err\n");
        else if (pid == 0)
        {
            //print 3
            printf("\t\tstart pr 3 PID = %d PPID = %d\n", getpid(), getppid());
            //6
            if ((pid = fork()) == -1) printf("Err\n");
            else if (pid == 0)
            {
                //print 6
                printf("\t\t\tstart pr 6 PID = %d PPID = %d\n", getpid(), getppid());
                printf("\t\t\tend pr 6\n");
                exit(0);
            } else sleep(1);

            //7
            if ((pid = fork()) == -1) printf("Err\n");
            else if (pid == 0)
            {
                //print 7
                printf("\t\t\tstart pr 7 PID = %d PPID = %d\n", getpid(), getppid());
                printf("\t\t\tend pr 7\n");
                exit(0);
            } else sleep(1);

            printf("\t\tend pr 3\n");
            exit(0);
        }
        else sleep(3);
        printf("\tend pr 1\n");
        exit(0);
    }
    else sleep(10);

    printf("End program...\n");
    return 0;
}
