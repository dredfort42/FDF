#include "fdf.h"

void	ft_free_map(t_mlx *mlx)
{
	int	y;

	y = 0;
	while (y < mlx->map_height)
	{
		free(mlx->map[y]);
		y++;
	}
	free(mlx->map);
}

void	ft_reset_mlx(t_mlx *mlx)
{
	mlx->scale = 30;
	mlx->z_scale = 30;
	mlx->tilt = 0.523599;
	mlx->shift_x = WIN_WIDTH / 2.5;
	mlx->shift_y = WIN_HEIGHT / 3.5;
	mlx->tilt_status = 1;
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static short	ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*phaystack;
	size_t	charnum;
	size_t	i;
	size_t	ndllen;

	phaystack = (char *)haystack;
	ndllen = ft_strlen(needle);
	if (ndllen == 0 || haystack == needle)
		return (0);
	charnum = 0;
	while (phaystack[charnum] && charnum < len)
	{
		i = 0;
		while (phaystack[charnum + i] && needle[i]
			   && phaystack[charnum + i] == needle[i] && charnum + i < len)
			i++;
		if (i == ndllen)
			return (1);
		charnum++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2
		|| !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1]))
		|| open(argv[1], O_RDONLY) < 0)
		return (0);
	ft_read_map(argv[1], &mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp,
			&mlx.img.size_l, &mlx.img.endian);
	ft_reset_mlx(&mlx);
	ft_draw_map(&mlx);
	mlx_key_hook(mlx.win_ptr, control_keys, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
