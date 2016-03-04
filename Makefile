run: a.out
	./a.out
a.out: testing.c
	gcc testing.c

clean:
	rm -fr a.out
	
