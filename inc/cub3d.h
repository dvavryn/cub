/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:12:41 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 19:10:23 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                   INCLUDES                                 */
/* ************************************************************************** */

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */

# define WIN_H 600
# define WIN_W 800
# define TILE 32
# define M_PI 3.14159265358979323846
# define FOV 1.047197551
# define RAY_STEP 1
# define MAX_DIST 2000
# define NUM_RAYS WIN_W
# define MINI_SCALE 0.2
# define MINI_SIZE 150
# define MINI_OFFSET 10
# define MINIMAP_RADIUS 8

/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */

typedef struct s_player	t_player;
typedef struct s_img	t_img;
typedef struct s_dda	t_dda;
typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_config	t_config;
typedef struct s_map	t_map;

struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	angle;
};

struct s_img
{
	void	*img;
	char	*address;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
};

struct s_dda
{
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	double	dist;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	image;
	t_img	north;
	t_img	east;
	t_img	south;
	t_img	west;
};

struct s_map
{
	int		**map;
	size_t	map_x;
	size_t	map_y;
};

struct s_config
{
	char	**raw_config;

	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;

	char	*floor_color;
	int		floor_color_hex;
	char	*ceiling_color;
	int		ceiling_color_hex;

	int		player_position_x;
	int		player_position_y;
	char	player_orientation;
};

struct s_data
{
	t_mlx		mlx;
	t_player	player;
	t_dda		dda;
	t_map		map;
	t_config	config;
	// char		**map;		// <== should be an int map with sizes | inside of t_map 
	bool		key[70000];
	double		last_frame_time;
	double		delta;
};

/* ************************************************************************** */
/*                                  PROTOTYPES                                */
/* ************************************************************************** */

void			my_pixel_put(t_img *img, int x, int y, int color);
unsigned int	get_color(t_img *img, int x, int y);
void			draw_player(t_data *cub);
void			draw_minimap(t_data *cub);
void			draw_square(t_img *img, int x, int y, int size, int color);
void			key_handler(t_data *cub);
void			render(t_data *cub);
int				is_wall(int **map, double x, double y);
void			draw_line(t_img *img, double x0, double y0, double x1, double y1);
double			cast_ray(t_data *cub, double angle, double *hit_x, double *hit_y);
void			cast_rays_minimap(t_data *cub);
double			cast_ray_dda(t_data *cub, double angle, double *hitx, double *hity);
int				ray_color(double dist);
void			draw_minimap_ray(t_data *cub, double end_x, double end_y);
int				render_loop(t_data *cub);
int				key_press(int key, t_data *cub);
int				key_release(int key, t_data *cub);
void			cast_all_rays_3d(t_data *cub);
void			cast_3d_ray(t_data *cub, double angle, int col);
int				update(t_data *cub);
void			draw_circle(t_img *img, int x, int y, int r, int color);
void			get_map_dimensions(int **map, int *width, int *height);
int				get_wall_color(t_data *cub, double angle);
void			load_texture(t_data *cub, t_img *tex, char *path);
t_img			*get_wall_texture(t_data *cub, t_dda *dda);
double			get_wall_x(t_data *cub, t_dda *dda, t_img *tex);
void			draw_3d_wall(t_data *cub, int x, double dist);
void			init_player_from_map(t_data *cub);
char			**duplicate_map(char **map);
void			cub(t_data *cub);
int				ft_intlen(int *il);

void			free_data(t_data *data);
void			error_exit(char *str, t_data *data);
void			parsing(t_data *data, int argc, char **argv);

#endif
