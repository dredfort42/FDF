#include "fdf.h"

static void	ft_reset_line(t_line *ab)
{
	ab->x0 = 0;
	ab->y0 = 0;
	ab->z0 = 0;
	ab->x1 = 0;
	ab->y1 = 0;
	ab->z1 = 0;
}

static void	ft_draw_polygon(int y, int x, t_mlx *mlx)
{
	t_line	ab;

	ft_reset_line(&ab);
	if (x + 1 < WIN_WIDTH && x + 1 < mlx->map_width)
	{
		ab.x0 = x;
		ab.y0 = y;
		ab.x1 = x + 1;
		ab.y1 = y;
		ft_draw_line(&ab, mlx);
	}
	ft_reset_line(&ab);
	if (y + 1 < WIN_HEIGHT && y + 1 < mlx->map_height)
	{
		ab.x0 = x;
		ab.y0 = y;
		ab.x1 = x;
		ab.y1 = y + 1;
		ft_draw_line(&ab, mlx);
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			ft_draw_polygon(y, x, mlx);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
