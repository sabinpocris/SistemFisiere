build:
	gcc main.c IO.c BinaryTree.c FileSystem.c -o tema3 -g

run:
	./tema3

clean:
	rm ./tema3