all:
	mkdir -p bin
	cd bin; gcc ./../src/main.c -o app

clean:
	rm -rfv bin

run:
	cd bin; ./app

test1:
	cd bin; ps | ./app

test2:
	cd bin; ps | sort | ./app

test3:
	cd bin; ps | head -n 4 | ./app

test4:
	cd bin; ps | tail -n 4 | ./app