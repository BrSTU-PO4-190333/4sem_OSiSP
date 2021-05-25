clean:
	rm -rfv bin

compile_app1:
	mkdir -p bin
	cd bin; gcc ./../src/app1.c ./../src/message_queue/message_queue.c ./../src/my_ftoa/my_ftoa.c ./../src/print_real_time/print_real_time.c -lrt -o app1.out

run_app1:
	cd bin; ./app1.out

compile_app2:
	mkdir -p bin
	cd bin; gcc ./../src/app2.c ./../src/message_queue/message_queue.c ./../src/my_ftoa/my_ftoa.c ./../src/print_real_time/print_real_time.c -lrt -lm -o app2.out

run_app2:
	cd bin; ./app2.out
