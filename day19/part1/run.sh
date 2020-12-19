# gcc -O3 *.c -L. -lft && time ./a.out
gcc -g -fsanitize=address *.c -L. -lft && time ./a.out