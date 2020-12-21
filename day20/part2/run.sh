# gcc -g -fsanitize=address main.c read_p2.c get_map.c -L. -lft -lvect && ./a.out 2> output.txt
gcc -O3 main.c read_p2.c get_map.c -L. -lft -lvect && ./a.out 2> output.txt

gcc -O3 read_dragons.c -L. -lft -lvect && ./a.out