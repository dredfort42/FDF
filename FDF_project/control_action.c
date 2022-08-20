#include "fdf.h"

static void	ft_scale_action(int key, t_mlx *mlx)
{
	if (key == 14)
	{
		mlx->scale *= 1.1;
		mlx->z_scale *= 1.1;
	}
	if (key == 12)
	{
		mlx->scale *= 0.9;
		mlx->z_scale *= 0.9;
	}
}

static void	ft_tilt_action(int key, t_mlx *mlx)
{
	if (key == 2)
		mlx->tilt -= 0.1;
	if (key == 0)
		mlx->tilt += 0.1;
}

static void	ft_shift_action(int key, t_mlx *mlx)
{
	if (key == 123)
		mlx->shift_x -= 10;
	if (key == 124)
		mlx->shift_x += 10;
	if (key == 126)
		mlx->shift_y -= 10;
	if (key == 125)
		mlx->shift_y += 10;
}

static void	ft_action(int key, t_mlx *mlx)
{
	if (key == 15)
		ft_reset_mlx(mlx);
	else if (key == 49)
		mlx->tilt_status *= -1;
	else
	{
		ft_scale_action(key, mlx);
		ft_tilt_action(key, mlx);
		ft_shift_action(key, mlx);
	}
}

int	control_keys(int key, t_mlx *mlx)
{
	if (key == 15 || key == 12 || key == 14 || key == 2 || key == 0
		|| key == 123 || key == 124 || key == 125 || key == 126 || key == 49)
	{
		free(mlx->img.img_ptr);
		free(mlx->img.data);
		mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
		mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr,
				&mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
		ft_action(key, mlx);
		ft_draw_map(mlx);
	}
	else if (key == 53)
	{
		free(mlx->img.img_ptr);
		free(mlx->img.data);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		ft_free_map(mlx);
		exit(0);
	}
	return (0);
}
