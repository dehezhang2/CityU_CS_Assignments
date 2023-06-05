#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100              // max length of the command line
#define WAITTIME 1000        // max time for parent process to wait for child process
//#define WITHOUTPATH        // if define "WITHOUTPATH", use "bg demo" instead of "bg ./demo"

char buffer[MAX];  // store the line into the buffer, cmd is the first string in the buffer
char* args[MAX];             // buffer for each line, cmd is the first string in the buffer, args is the parameter of execvp
int status=0;
bool quit = 0; 
pid_t cpid=1;

int main(int cnt, char** args){
    do{
    
        std::cout<<"PMan: > ";
        // getline must be in front of waitpid, because you need to block the system before the child process automatically finished
        std::cin.getline(buffer,MAX);
        
        // change the status for all input cases, collect zombine process(if waitpid returns the pid of zombine, change )
        status = waitpid(-1,NULL,WNOHANG)>0?0:status;

        // split the input line, continue if there is no input
        char* cmd = strtok(buffer," ");
        if(!cmd)continue;
        int argc=0;
        do{
            args[argc]=strtok(NULL," ");
            argc++;
        }while(args[argc-1]);

        // Case : bg
        if(strcmp(cmd,"bg")==0){
            // check running status and the argument
            if(status!=0){
                std::cerr<<"Error: There is a background process already.\n";
                continue;
            }
            if(!argc){
                std::cerr<<"Error: Name is null.\n";
                continue;
            }

            #ifdef WITHOUTPATH
                char file[MAX]="./";
                strcat(file,args[0]);
                args[0]=file;
            #endif


            // create a child process
            cpid = fork();
            if(cpid>0){
                // parent process:
                std::cout<<"bg: Create new process: "<<cpid<<std::endl;
                // wait for child process output error first(if any)
                usleep(WAITTIME);
                status = 1;
            } else if(cpid==0){
                // child process: call the input file 
                int success = execvp(args[0],args);
                if(success==-1){
                    std::cerr<<"Error: execvp() failed(may be caused by invalid file name).\n";
                }
            } else if(cpid<0){
                std::cerr<<"Error: fork() failed!\n";
                exit (EXIT_FAILURE);
            }
        // Other cases: just send the signal
        } else if(strcmp(cmd,"bgkill")==0){
            if(!(status==1||status==2)){
                std::cerr<<"Error: No background process to kill.\n";
                continue;
            }
            pid_t tar = atoi(args[0]);
            if(tar!=cpid) std::cerr<<"Error: The pid is not a valid process id of a background process.\n";
            else{
                int fail=kill(tar,SIGTERM);
                if(!fail){
                     std::cout<<tar<<" has been killed\n";
                     cpid = 1; status = 0;
                }
                else std::cerr<<"Error: kill() is failed.\n";
            }

        } else if(strcmp(cmd,"bgstop")==0){
            if(status!=1){
                std::cerr<<"Error: No running background process to stop.\n";
                continue;
            }
            pid_t tar = atoi(args[0]);
            if(tar!=cpid) std::cerr<<"Error: The pid is not a valid process id of a background process.\n";
            else{
                int fail = kill(tar,SIGSTOP);
                if(!fail){
                     std::cout<<tar<<" has been stopped\n";
                     status = 2;
                }
                else std::cerr<<"Error: bgstop() is failed.\n";
            }
        } else if(strcmp(cmd,"bgstart")==0){
            if(status!=2){
                std::cerr<<"Error: No stopped background process to start.\n";
                continue;
            }
            pid_t tar = atoi(args[0]);
            if(tar!=cpid) std::cerr<<"Error: The pid is not a valid process id of a background process.\n";
            else{
                int fail = kill(tar,SIGCONT);
                if(!fail){
                    std::cout<<tar<<" has been started\n";
                    status = 1;
                }
                else std::cerr<<"Error: bgstart() is failed.\n";
            }
        } else if(strcmp(cmd,"exit")==0){
            if(status==1||status==2){
                int fail = kill(cpid,SIGTERM);  // kill before exit
                if(fail) std::cerr<<"Error: kill() is failed.\n";
                else std::cout<<cpid<<" has been killed\n";
            }
            quit=1;
        } else{
            std::cout<<"PMan: > "<<cmd<<": command not found\n";
        }
    } while(!quit&&cpid!=0);
    return 0;
}
