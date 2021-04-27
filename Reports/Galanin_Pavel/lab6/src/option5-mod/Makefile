all:
	mkdir -p bin
	make compile_producer
	make compile_consumer

clean:
	rm -rfv bin

run:
	make run_producer
	make run_consumer

compile_producer:
	cd bin; gcc ./../src/producer.c -lrt -o producer.out

run_producer:
	cd bin; ./producer.out

compile_consumer:
	cd bin; gcc ./../src/consumer.c -lrt -o consumer.out

run_consumer:
	cd bin; ./consumer.out
