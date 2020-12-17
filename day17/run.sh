# gcc -g -fsanitize=address main.c hash.c list.c util.c -L. -lft && time ./a.out
gcc -O3 main.c hash.c list.c util.c -L. -lft && time ./a.out
