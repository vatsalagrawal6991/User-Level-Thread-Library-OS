arg1 =
arg2 =
arg3 =
arg4 =

all: test1 test2 test3 test4 test5 test6 test7 matrix boundedBuffer

test1: test1.out

test1.out: obj/test1.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test2: test2.out

test2.out: obj/test2.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test3: test3.out

test3.out: obj/test3.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test4: test4.out

test4.out: obj/test4.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test5: test5.out

test5.out: obj/test5.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test6: test6.out

test6.out: obj/test6.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

test7: test7.out

test7.out: obj/test7.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

matrix: matrix.out

matrix.out: obj/matmul.o obj/matrix.o obj/printMatrix.o obj/time.o obj/matrixorig.o lib_thread.so
	gcc obj/matmul.o obj/matrix.o obj/printMatrix.o obj/time.o obj/matrixorig.o -o $@ -L. -l_thread -lpthread

boundedBuffer: boundedBuffer.out

boundedBuffer.out: obj/ConsumerProducer.o lib_thread.so
	gcc $< -o $@ -L. -l_thread

obj/test1.o: src/test1.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test2.o: src/test2.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test3.o: src/test3.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test4.o: src/test4.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test5.o: src/test5.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test6.o: src/test6.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/test7.o: src/test7.c inc/thread.h
	gcc -c $< -o $@ -I./inc

obj/printMatrix.o: src/printMatrix.c
	gcc -c $< -o $@

obj/matrix.o: src/matrix.c
	gcc -c $< -o $@

obj/matrixorig.o: src/matrixorig.c
	gcc -c $< -o $@

obj/time.o: src/time.c
	gcc -c $< -o $@

obj/matmul.o: src/matmul.c inc/thread.h inc/matrixorig.h
	gcc -c -w $< -o $@ -I./inc

obj/ConsumerProducer.o: src/ConsumerProducer.c inc/thread.h
	gcc -c $< -o $@ -I./inc

lib_thread.so: obj/thread.o obj/queue.o
	gcc $^ -shared -o $@

obj/thread.o: lib/thread.c inc/queue.h inc/thread.h
	gcc -Wall -fpic -c $< -o $@ -I./inc

obj/queue.o: lib/queue.c inc/queue.h inc/thread.h
	gcc -Wall -fpic -c $< -o $@ -I./inc

clear:
	rm -f ./obj/*.o *.out *.so

run: all
	./data/run.sh

runTest: all
	./data/runTest.sh

plot:
	gnuplot ./data/plot.p