# gcc -g -fsanitize=address main.c intvector.c -L. -lft && ./a.out
gcc -O3 main.c intvector.c -L. -lft && time ./a.out
