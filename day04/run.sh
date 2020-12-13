# gcc main.c get_next_line.c -L. -lft && ./a.out
gcc -O0 -g -fsanitize=address -fsanitize=leak main.c get_next_line.c -L. -lft && ./a.out
