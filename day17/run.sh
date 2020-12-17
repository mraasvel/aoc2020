gcc -g -fsanitize=address main.c hash.c list.c -L. -lft && time ./a.out
# gcc -O3 main.c hash.c list.c -L. -lft && time ./a.out
