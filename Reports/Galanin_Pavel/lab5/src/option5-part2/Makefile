all:
	mkdir -p bin; cd bin; gcc ./../src/main.c -o app

clean:
	rm -rfv bin

run:
	cd bin; ./app

test1:
	cd bin; ls -l | ps | ./app

test2:
	cd bin; ls -l | ps | sort | ./app

test3:
	cd bin; ls -l | ps | head -n 3 | ./app

test4:
	cd bin; ls -l | ps | tail -n 3 | ./app