gcc -O0 -g -fsanitize=address part2.c permute_mask.c -L. -lft && ./a.out
# gcc -O3 part2.c permute_mask.c -L. -lft && ./a.out
# gcc -O0 -g -fsanitize=address permute_mask.c -L. -lft && ./a.out