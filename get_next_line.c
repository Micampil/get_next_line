/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Micampil <micampil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:20 by Micampil          #+#    #+#             */
/*   Updated: 2025/08/12 20:31:08 by Micampil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result;
	int			bytes_read;

	result = NULL;
	bytes_read = 1;
	if (!buffer[0])
		bytes_read = -2;
	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	return (get_next_line_cont(fd, buffer, result, bytes_read));
}
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		line_number;

// 	line_number = 1;
// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <file>\n", argv[0]);
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	printf("Line %d: %s", line_number, line);
// 	free(line);
// 	line_number++;
// 	close(fd);
// 	return (0);
// }

// // int	main(int argc, char **argv)
// // {
// // 	int		fd;
// // 	char	*result;
// // 	int		i;

// // 	i = 1;
// // 	if (argc > 1)
// // 	{
// // 		fd = open(argv[1], O_RDONLY);
// // 		result = get_next_line(fd);
// // 		while (result != NULL)
// // 		{
// // 			printf("call #%d: %s", i, result);
// // 			free(result);
// // 			result = get_next_line(fd);
// // 			i++;
// // 		}
// // 		free(result);
// // 		if (fd != -1)
// // 			close(fd);
// // 	}
// // }
