# gcc -g -fsanitize=address main.c -L. -lft && ./a.out
gcc -O3 main.c -L. -lft && ./a.out
# gcc -O3 test.c -L. -lft && ./a.out
