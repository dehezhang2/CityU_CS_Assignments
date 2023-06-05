# Assignment 1: A Process Manager (PMan)

This assignment implements a process manager terminal application, which supports following commands:

* The command `bgkill pid` will send the `TERM ` signal to the background process with process ID `pid ` to terminate that process.
* The command `bgstop pid` will send the `STOP` signal to the background process with process ID `pid` to stop (temporarily) that process.
* The command `bgstart pid` will send the `CONT` signal to the background process with process ID `pid` to re-start that process (which has been previously stopped).
* The command `exit` will execute `bgkill pid`, if there is any background process, and then exit.

## All possible Outputs of the Program

1. Normal case:
    PMan: >  

2. "bg <...> <...> <...>"

    * If there is a child process which is not a zombine:
      
      ```bash
      Error: There is a background process already.
      ```
      
    * If the input file name is null:
      
         ```bash
         Error: Name is null.
         ```
         
    * `fork()` to create a child process:

      * success

        * Parent process: 

          ```bash
          bg: Create new process: childpid
          ```

    		
    		* Child process(if execvp is failed):
    		
    		  ```bash
    		  Error: execvp() failed(may be caused by invalid file name).
    		  ```
    	
    	* fail
    	
    	  ```bash
    	  Error: fork() failed!
    	  ```

3. If the input is not equal to the pid stored in the program
   
   ```
   Error: The pid is not a valid process id of a background process.
   ```
   
4. "bgkill <PID>"

    * If the status is not 1(running) or 2(stop):
    
   ```
     Error: No background process to kill.
   ```
   
    * Kill the process:
   
     * success
   
       ```
       PID has been killed
       ```
   
     * fail
   
       ```
       Error: kill() is failed.
       ```
   
5. "bgstop <PID>"

    * If the status is not 1(running)

      ```
       Error: No running background process to stop
      ```

    * Stop the process:

      * success

        ```
        PID has been stopped
        ```

      * fail

        ```
        Error: bgstop() is failed.
        ```
6. "bgstart <PID>"

    *  If the status is not 2(stop):

      ```
      Error: No stopped background process to start.
      ```

    * Restart the process:

      * success

        ```
        PID has been started
        ```

      * fail

        ```
        Error: bgstart() is failed.
        ```
5. "exit"

    * If the status is 1(running) or 2(stop): run `bgkill <PID>`; output is same as bgkill

8. Input is unknown command:

   ```
   PMan: > cmd command not found
   ```

## Description

1. Since the length of the input is unknown, I use 100 as the maximum input length, but the maximum input length can be changed by change the `#define MAX 100`
   
1. Since it is possible that execvp() is failed, parent process cannot output next `PMan >`, before child process output the error message. Thus, parent should sleep `WAITTIME` msec after fork
   
1. The program provides 2 modes of bg
   
   * with path: `bg ./demo running 2 20`
   
   * without path: ` bg demo running 2 20`
   
   To run the second mode, you need to compile the program by type `g++ PMan.cpp -o PMan -D WITHOUTPATH`. And you cannot call command line programs such as`bg ls -al`. 
   
1. For the following test case:
   
   ```
   PMan: > bg ./demo running 1 1
   bg: Create new process: PID 
   PMan: > bgstop PID    // after it finished
   ```
   
   The process is automatically finished and becomes a zombine, if the PMan do not collect it by calling `waitpid()` and change the status, `bgstop` will be successfully executed, which is a bug. To deal with this situation, I collect zombine process after accept the input of user's input line for each iteration.
