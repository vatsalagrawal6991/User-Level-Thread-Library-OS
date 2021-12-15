Made By Vatsal Agrawal

**************************HOW TO MAKE EXECUTABLE AND RUN PROGRAMME******************************
1) Unzip File at location x
2) Open Terminal and change directory to that location x
3) Now enter command make.
This will create Executables
4) Enter Command make run to run the executables bounded buffer
and matrix and make runTest to run all the test
5) Alternatively, you can type
export LD_LIBRARY_PATH=${pwd} //give the path of the present working directory.
export LD_LIBRARY_PATH=/home/baadalvm/CLionProjects/Lab3_main
6) Then type executable name with the arguments
7) For plot, type make plot


Problem Question

In this assignment, you will create a user level thread level library which implies that it is supported above the kernel in user space and are managed without kernel support.
Do NOT use the PTHREADS library in any way in this assignment.
These are some of the functions that need to be implemented in this are
myThread_create (thread,attr,start_routine,arg)
myThread_exit (status)
myThread_cancel (thread)
myThread_attr_init (attr)
myThread_attr_destroy (attr)
myThread_t pthread_self(void);
myThread_yield(void)
myThread_join(int tid)
Once multiple threads are running, you will need a way of switching between different threads. To do this, you could use the library functions setjmp and longjmp. In a nutshell, setjmp saves the current state of a thread into a jmp_buf structure. longjmp uses this structure to restore (jump back) to a previously saved state. You will find these functions very useful, since they do exactly what is needed when switching from one thread to another and later resuming this thread's execution. More precisely, you can have the currently executing thread call setjmp and save the result in the thread's TCB. Then, your thread subsystem can pick another thread, and use the saved jmp_buf of that thread together with longjmp to resume the execution of the new thread.
The process of picking another thread is called scheduling. In our system, all scheduling queues should be FIFO. This includes the ready queue and the queue of threads waiting for a signal.
Now we need to force the thread of a program to call setjmp every once in a while (and thus, giving up control of the CPU). In particular, application developers do not need to know about your thread implementation, so it is unlikely that they will periodically call setjmp and allow your scheduler to switch to a new process. To solve this issue, we can make use of signals and alarms. More precisely, we can use the ualarm or the setitimer function to set up a periodic timer that sends a SIGALRM signal every X milliseconds (for this project, we choose X to be 50ms). Whenever the alarm goes of, the operating system will invoke the signal handler for SIGALRM. So, you can install your own, custom signal handler that performs the scheduling (switching between threads) for you. For installing this signal handler, you should use sigaction with the SA_NODEFER flag (read the man page for sigaction for details).
Note that we require that your thread system supports thread preemption and switches between multiple threads that are ready. It is not okay to run each individual thread to completion before giving the next one a chance to execute.
To ensure atomicity of multiple operations, users will use locks that you provide. To implement those locks, you COULD use the "compare and swap" routine provided by the x86.
This gives you the background to implement the myThreadswitch() function which does the scheduling for you.
Tests
• Single thread: A program that creates and thread (which prints something out) and then waits for it to complete.
• Multiple threads: creates multiple threads and then waits for all of them to complete. The threads should be run in FIFO order. There may be a large number of these, too -- which could stress whether you clean up the thread stack when done.
• Multiple threads + yield: creates multiple threads which frequently yield to each other. Testing whether yield works and FIFO ordering is preserved.
• Multiple threads + lock: creates threads and has them call lock/unlock on a single lock around a critical section.
• Multiple threads + lock + yield: creates threads, which grab lock then yield. Makes sure that lock is still held properly across yielding. Also makes sure that lock queue is managed in FIFO order.
• Multiple threads + condition variable: creates two threads which use a condition variable to wait/signal each other.
• Multiple threads + condition variable + yield: creates threads which use condition variables and locks to test whether condition variable queues are managed in FIFO order.
You will test your implementations using the following application programs:
• Multi threaded Matrix Multiplication with N threads
o Plot a graph with respect to time taken versus N (=1 to 40)
o Calculate the average context switch overhead with our thread library
o Repeat the experiment with pThreads and compare the average context switch overheads inboth cases.
• Bounded Buffer (Producer Consumer) with N containers, M producers and M Consumers (M<N)
o In this simulation, you should make each producer and consumer print when it acquires a container or deposits a container.
o You must also maintain a shared buffer that tracks and prints how many containers have been produced and consumed. The producers and consumers should each stop after 10*N items have been either produced or consumed.
Your thread library needs to be built into a dynamically-linked shared library.
Building a dynamically-linked library
Your thread library needs to be built into a dynamically-linked shared library. The library should be called libmyOwnthread.so
There are two basic steps to building a dynamically-linked shared library:
• Compile each .c file
• For each .c file that comprises your library (e.g., userthread.c), you should compile as follows:
o gcc -Wall -fpic -c userthread.c
▪ Here, the -Wall flag prints all warnings, as usual; the -fpic flag tells the compiler to use "position-independent" code, which is good to use when building shared libraries; finally, the -c flag tells the compiler to create an object file (in this case, userthread.o).
• Link the object files together to create a shared library
o Once you've built all your .o files, you need to make the shared library:
▪ gcc -o libuserthread.so userthread.o -shared
• Linking a program with your library
o Let's say you have a program, test.c, that wants to use this thread library. First, test.c should include the header file "userthread.h"
o To build test, you need to link it with your library (assuming all of your code is in the same directory):
▪ gcc -o test test.c -L. -lmyOwnthread
• Of course for the assignment, you must use these commands in the Makefile context and have the library in its proper place.
What do you turn in:
When we look at your your code, we will expect to see the following files in your repository (there may be more):
• myOwnthread.h, the header file that defines the functions exported by your library
• The multiple source code and header files that implement the functionality exported by userthread.h
• A Makefile to build your code. Typing make should build libmyOwnThread.so.
• libmyOwnThread.so should be compiled with the following flags: -Wall -fpic
• The application src codes
• The makefile should have multiple targets
o make matrix
o make boundedBuffer
o make all
o make clean
• A file called README which includes any additional nodes on your program that you think are important.
• You should not turn in any binary or .o files. Only turn in source code and header files


***************************ESSENTIAL POINTS*****************************************

1) We are working on the concept that the scheduler is one thread.
2) The scheduler's work is to be in the ready queue and run only when a context switch is needed. In the case of RR, it runs when quantum ends.
3) States of a process are denoted by Running, Ready, Terminated, Scheduler, Blocked, Finished
4) When the first time thread create is called, a scheduler is also initialized with all the queues it needs.
5) Pointer of TCB of every thread is kept in rdy (ready) queue, and the finished process is kept in ft queue.
6) When every thread in the ready queue is ended, it waits for 50ms to 100ms before deleting thread data. Note, thus join condition must be called in this time only. This feature time can be extended or can be turned off also.
7) Our programme works on a large number of threads ranging more than 10K in most of cases, given the constraint that memory does not overflow.
8) Our programme runs on the RR scheduler. Every time a Context switch is done, a thread context is saved, and a new thread context is restored. This is done with the help of siglongjmp and sigsetjmp and jmp_buf
9) A timer is maintained, which counts the time of CPU execution(not real-time) and give SIGVTALRM when the timer cranks.
10) Each TCB has its tid, its state, its JMP_buf, which store SP and PC, also it has function and arguments and attributes related to the thread.
11) Note, a programme jmp_buffer is protected and encrypted in Linux, so when we store new PC and SP in it manually, so we also have to encrypt them. 
12) Encryption is done with the help of the assembly inline function, which is based on AT&T. In this, operands are reversed; that is, the result comes in the end.
13)We use
asm volatile("xor %%fs:0x30,%0\n""rol $0x11,%0\n": "=g"(ret): "0" (addr));
In this volatile means do not compiler optimization (do not change position and always use it)
%% fs is register to hold special data structure of OS %%fs:0x30 = fs[0x30] is used to indicate process environment block. Rol is rotating on the left with carry bits, =g denoting result can be register, memory, etc., and 0 denotes input operand %0 as
register. Note encrypting feature is called mangle
14) Jmp_buffer is an integer array that holds at position six from 0 a stack pointer and the position seven a PC in x86; the Base pointer is stored at position 1
15) The lock is guaranteed with the help of an ASM code
asm volatile("lock; cmpxchg %2, %0 \n":"+m" (*original), "+a"(old) :"r"(new));
cmpxchg compare %2 with a series register like EAX, AX, AL and
if equal %0 is stored in %2; if not equal %2 is loaded in eax(made non 0), +a is used to store old in eax, +m is used to take original as memory address which read then write and r is register for read
16) Thcount is used in our programme to maintain thread count, Schfun is sigacation struct , itime in time interval struct, inCpu stores running thread TCB information.
17) MyThreadSwitch initializes timer and other things.
18) CS is a function that gains attention when a timer is called, and it calls context switch and ContextSwitch help in context switch and stopping the timer when rdy length is 0.
19) Rest functions are the same as pthread. 
20) Get is to get a lock, and leave is to leave the lock.
21) Note, the lock is a mutex, i.e. the person get mutex, can only leave it; otherwise, deadlock can occur 
22) MythreadJoin work on tid while other functions work on thread pointer
23) Wrap is a function that passes an argument to function and call myThreadExit automatically when the function ends.
24) All the test cases are working fine
Test 1-Single thread
Test 2-Multiple thread
Test 3- Multiple thread+yield
Test 4- Multiple thread+lock
Test 5- Multiple thread+lock+yield
Test 6- Multiple thread+CV
Test 7- Multiple thread+CV+yield
25) NODEFER has no particular use in our programme but can be used in case of some other signal is triggered
26) We have used a setitimer for alarm function.
27) We have used the ConsumerProducer problem in which many producers and consumers are sharing N buffer and stop when n buffers are produced
28) We have also used matrix multiplication, in which the number of rows is divided for threads
29) We have created a shared dynamic library of user-level thread
30) We are calculating Average context switch time in my thread matrix multiplication by formula
𝑚𝑦 𝑡ℎ𝑟𝑒𝑎𝑑 𝑡𝑖𝑚𝑒 − 𝑜𝑟𝑖𝑔𝑖𝑛𝑎𝑙 𝑡𝑖𝑚𝑒/((𝑚𝑦 𝑡ℎ𝑟𝑒𝑎𝑑 𝑡𝑖𝑚𝑒/𝑞𝑢𝑎𝑛𝑡𝑢𝑚 𝑡𝑖𝑚𝑒)+1)
We are calculating Average context switch time in pthread –by scheduling them in FIFO order in matrix multiplication by formula
pthread time - original time/no of threads
31) We have found the average context switch time as 0.03s in my thread when there is no thread deletion and 0.005s when there is thread deletion, and 0.0003s in pthread.
32) We have used a value of n=128 and a thread value of t=16 for this
33) We have found that our thread library performs best at thread count = 16
34) This has been seen that alarming timer after all thread completion to delete threads will be better in performance when there is load in comparison to not deleting threads
35) Our thread library performs as better as pthread when there is less load.

