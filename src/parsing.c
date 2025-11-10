/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:14:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/11/10 19:58:09 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void argcheck(int argc, char **argv)
{
	char	*filename;
	size_t	len;

	if (argc < 2)
		error_exit("filename missing", NULL);
	else if (argc > 2)
		error_exit("Usage: ./cub3d file.cub", NULL);
	filename = ft_strtrim(argv[1], " \t");
	if (!filename)
		error_exit("malloc error", NULL);
	len = ft_strlen(filename);
	free(filename);
	if (!len)
		error_exit("empty filename", NULL);	
	else if (len <= 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		error_exit("invalid file extension. expected '.cub'", NULL);
}

void	read_map(t_data *data, char *file)
{
	int		fd;
	char	*s;
	size_t	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(strerror(errno), data);
	s = get_next_line(fd);
	if (!s)
	{
		close(fd);
		error_exit("malloc failed", data);
	}
	i = 0;
	while (s)
	{
		data->config.raw_input = ft_realloc(data->config.raw_input, (i + 2) * sizeof(char *));
		if (!data->config.raw_input)
		{
			while (s)
			{
				free(s);
				s = get_next_line(fd);
			}
			error_exit("malloc failed", data);
		}
		data->config.raw_input[i] = s;
		s = get_next_line(fd);
		i++;
	}

}

void	parsing(t_data *data, int argc, char **argv)
{
	ft_bzero(data, sizeof(t_data));
	argcheck(argc, argv);
	read_map(data, argv[1]);
}
