#include "fdf.h"

static float 	ft_abs(float num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

static float	ft_maximal(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	ft_line_coordinates(t_line *ab, t_mlx *mlx)
{
	ab->z0 = mlx->map[(int)ab->y0][(int)ab->x0];
	if ((int)ab->y1 < mlx->map_height
		&& (int)ab->x1 < mlx->map_width)
		ab->z1 = mlx->map[(int)ab->y1][(int)ab->x1];
	else
		ab->z1 = ab->z0;
	ab->z0 *= mlx->z_scale / 15;
	ab->z1 *= mlx->z_scale / 15;
}

static void	ft_prepare_line(t_line *ab, t_mlx *mlx)
{
	ft_line_coordinates(ab, mlx);
	ft_color(ab, mlx);
	ft_scale(ab, mlx);
	ft_tilt(ab, mlx);
	ft_shift(ab, mlx);
}

void	ft_draw_line(t_line *ab, t_mlx *mlx)
{
	float	abs_delta_x;
	float	abs_delta_y;
	float	rasterization;

	ft_prepare_line(ab, mlx);
	abs_delta_x = ab->x1 - ab->x0;
	abs_delta_y = ab->y1 - ab->y0;
	rasterization = ft_maximal(ft_abs(abs_delta_x), ft_abs(abs_delta_y)) + 1;
	abs_delta_x /= rasterization;
	abs_delta_y /= rasterization;
	while ((int)(ab->x1 - ab->x0) || (int)(ab->y1 - ab->y0))
	{
		if ((int)ab->y0 * WIN_WIDTH + (int)ab->x0 <= WIN_HEIGHT * WIN_WIDTH)
			mlx->img.data[(int)ab->y0 * WIN_WIDTH + (int)ab->x0] = mlx->color;
		ab->y0 += abs_delta_y;
		ab->x0 += abs_delta_x;
		if (ab->x0 > WIN_WIDTH || ab->y0 > WIN_HEIGHT
			|| ab->y0 < 0 || ab->x0 < 0)
			break ;
	}
}
