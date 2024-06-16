#include <mlx.h>
#include <stdlib.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_tex
{
	char	*path;
	int		*texture;
	double	width;
	double	height;
}	t_tex;

typedef struct s_info
{
	t_tex	tex[4];
	t_mlx	*mlx;
	t_img	*img;
}	t_info;

int	*load_image_malloc(t_info *info, char *path, t_img *img, int i)
{
	int	col;
	int	row;
	int	*result;

	img->img = mlx_xpm_file_to_image(info->mlx->mlx, path, &img->width, &img->height);
	if (!img->img)
		exit(EXIT_FAILURE);
	info->tex[i].width = img->width;
	info->tex[i].height = img->height;
	result = malloc(sizeof(int) * (img->width * img->height));
	for(row = 0;row < img->height; row++)
	{
		for (col = 0; col < img->width; col++)
			result[img->width * row + col] = img->data[img->width * row + col];
	}
	mlx_destroy_image(info->mlx->mlx, img->img);
	return (result);
}

void	load_texture(t_info *info)
{
	int		i;
	t_img	img;

	i = 0;
	while (i < 4)
	{
		info->tex[i].texture = load_image_malloc(info, info->tex[i].path, &img, i);
		i++;
	}
}

int	find_color(t_info *info, int col, int row)
{
	int	color;
	int height = info->tex[0].height;
	int	width = info->tex[0].width;
	int	result_row = height * row / 1920;
	int	result_col = width * col / 1080;

	color = info->tex[0].texture[width * result_row + result_col];
	return (color);
}

int	main()
{
	t_info	info;

	info.mlx = malloc(sizeof(t_mlx));
	info.mlx->mlx = mlx_init();
	if (!info.mlx->mlx)
		exit(EXIT_FAILURE);
	info.mlx->win = mlx_new_window(info.mlx->mlx, 1920, 1080, "test");
	if (!info.mlx->win)
		exit(EXIT_FAILURE);
	info.img = malloc(sizeof(t_img));
	info.img->img = mlx_new_image(info.mlx->mlx, 1920, 1080);
	info.img->data = (int *)mlx_get_data_addr(info.img->img, &info.img->bpp, &info.img->line, &info.img->endian);
	info.tex[0].path = "../elem/north.xpm";
	info.tex[1].path = "../elem/south.xpm";
	info.tex[2].path = "../elem/west.xpm";
	info.tex[3].path = "../elem/east.xpm";
	load_texture(&info);
	for (int row = 0; row < info.tex[0].height; row++)
	{
		for (int col = 0; col < info.tex[0].width; col++)
			info.img->data[(int)info.tex[0].height * row + col] = find_color(&info, col, row);
	}
	mlx_put_image_to_window(info.mlx->mlx, info.mlx->win, info.img->img, 0, 0);
	mlx_loop(info.mlx->mlx);
}