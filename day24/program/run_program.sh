# gcc -g -fsanitize=address *.c -L. -lft -lvect && time ./a.out
gcc -O3 *.c -L. -lft -lvect && time ./a.out