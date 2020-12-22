# gcc -g -fsanitize=address *.c -L. -lft -lvect && ./a.out
gcc -O3 *.c -L. -lft && ./a.out
