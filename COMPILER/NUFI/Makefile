all:
	bison --defines=simple.h -v -o nufi.c nufi.y
	flex -o nufi.yy.c nufi.l
	gcc nufi.yy.c nufi.c -o nufi -lfl

