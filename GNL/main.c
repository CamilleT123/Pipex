#include "get_next_line.h"

// int main ()
// {
// 	int		fd;
// 	char	*line;
// 	char	*cpyline;
// 	char	*buf;
// 	char	**tab;

// 	fd = open(STDIN_FILENO, O_RDONLY);
// 	if (fd < 0)
// 		// error
// 	line = ft_strdup("");
// 	buf = get_next_line(fd);
// 	while (buf != NULL)
// 	{
// 		cpyline = line;
// 		line = ft_strjoin(cpyline, buf);
// 		free(buf);
// 		free(cpyline);
// 		buf = get_next_line(fd);
// 	}
// 	close(fd);
// 	cpyline = line;
// 	line = ft_strtrim(line, "\n");
// 	free(cpyline);
// 	tab = ft_split(line, '\n');
// 	return (free(line), tab);
// }

#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*gnl;
	fd = 0;
	gnl = "l";
	while (gnl != NULL)
	{
		gnl = get_next_line(fd);
		printf("return %s \n", gnl);
		free(gnl);
	}
	close(fd);
}