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

