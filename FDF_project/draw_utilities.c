#include "fdf.h"

void	ft_color(t_line *ab, t_mlx *mlx)
{
	if (mlx->map[(int)ab->y0][(int)ab->x0] > 0
		|| ((int)ab->y1 < mlx->map_height && (int)ab->x1 < mlx->map_width
			&& mlx->map[(int)ab->y1][(int)ab->x1] > 0))
		mlx->color = 0xFF0000;
	else if (mlx->map[(int)ab->y0][(int)ab->x0] < 0
			 || ((int)ab->y1 < mlx->map_height && (int)ab->x1 < mlx->map_width
				 && mlx->map[(int)ab->y1][(int)ab->x1] < 0))
		mlx->color = 0x0000FF;
	else
		mlx->color = 0xFFFF00;
}

void	ft_scale(t_line *ab, t_mlx *mlx)
{
	ab->x0 *= mlx->scale;
	ab->y0 *= mlx->scale;
	ab->x1 *= mlx->scale;
	ab->y1 *= mlx->scale;
}

void 	ft_tilt(t_line *ab, t_mlx *mlx)
{
	float	tx0;
	float	ty0;
	float	tx1;
	float	ty1;

	tx0 = ab->x0;
	ty0 = ab->y0;
	tx1 = ab->x1;
	ty1 = ab->y1;
	if (mlx->tilt_status > 0)
	{
		ab->x0 = (tx0 - ty0) * cos(mlx->tilt);
		ab->y0 = (tx0 + ty0) * sin(mlx->tilt) - ab->z0;
		ab->x1 = (tx1 - ty1) * cos(mlx->tilt);
		ab->y1 = (tx1 + ty1) * sin(mlx->tilt) - ab->z1;
	}
}

void 	ft_shift(t_line *ab, t_mlx *mlx)
{
	ab->x0 += mlx->shift_x;
	ab->y0 += mlx->shift_y;
	ab->x1 += mlx->shift_x;
	ab->y1 += mlx->shift_y;
}
