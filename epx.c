#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

size_t	ft_strend(char *line);
char	*ft_get_line(int fd, char **result);
char	*ft_line_check(int fd, char *read_res);

char	*get_next_line(int fd)
{
	char 	*result;
	int 	a;

	result = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!result)
		return (NULL);
	a = read(fd, (char *)result, BUFFER_SIZE);
	// ft_get_line(fd, &result);
	printf("\n%d\n", a);

	return (result);
}

// char	*ft_get_line(int fd, char **result)
// {
// 	char 	*read_result;


// 	read_result = (char *)malloc(BUFFER_SIZE * sizeof(char));
// 	if (!read_result)
// 		return (NULL);
// 	read(fd, (char *)read_result, BUFFER_SIZE);

// }

int	main()
{
	int i = 0;
	int	a = open("/Users/aleks/Desktop/42/get_next_line/1.txt", O_RDONLY);
	while (i < 2)
{
	char *m = get_next_line(a);
	printf("%s", m);
	i++;
}
	close(a);
	// printf("%s", m);
}