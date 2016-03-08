run: a.out
	./a.out
a.out: main.c
	gcc main.c Set.c 

clean:
	rm -fr a.out
	
