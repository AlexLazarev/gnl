#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **av)
{
	int fd1;
	int	fd2;
	char *line;
	int	res;

	if (argc > 1)
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
		
		res = get_next_line(fd1, &line);
		printf("re: %s  %d\n", line, res);   
		res = get_next_line(fd2, &line);
		printf("re: %s  %d\n", line, res);   
		res = get_next_line(fd1, &line);
		printf("re: %s  %d\n", line, res);
		res = get_next_line(fd2, &line);
		printf("re: %s  %d\n", line, res); 
		res = get_next_line(fd1, &line);
		printf("re: %s  %d\n", line, res);  
		res = get_next_line(fd2, &line);
		printf("re: %s  %d\n", line, res); 
		res = get_next_line(fd1, &line);
		printf("re: %s  %d\n", line, res);
}
    return (0);
}
