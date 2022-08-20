#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "./minilibx_macos/mlx.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_line
{
	float		x0;
	float		y0;
	float		z0;
	float		x1;
	float		y1;
	float		z1;
}				t_line;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	int			map_height;
	int			map_width;
	int			**map;
	int			color;
	int			tilt_status;
	float		shift_x;
	float		shift_y;
	float		scale;
	float		z_scale;
	double		tilt;
}				t_mlx;

typedef struct s_point
{
	int		x;
	int		y;
	short	sign;
	short	space_flag;
}	t_point;

void	ft_read_map(char *file, t_mlx *map);
void	ft_free_map(t_mlx *mlx);
void	ft_reset_mlx(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_draw_line(t_line *ab, t_mlx *mlx);
void	ft_color(t_line *ab, t_mlx *mlx);
void	ft_scale(t_line *ab, t_mlx *mlx);
void	ft_tilt(t_line *ab, t_mlx *mlx);
void	ft_shift(t_line *ab, t_mlx *mlx);
int		control_keys(int key, t_mlx *mlx);

#endif
