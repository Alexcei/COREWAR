#include "corewar.h"

void		render_background(t_main *main)
{
	int		i;
	
	i = 0;
	ft_bzero(main->data_addr, sizeof(char) * SIZE);
	while (i < SIZE)
		((int*)(main->data_addr))[i++] = BACKGROUND;
}

void	drow_sqw(t_main *main, int x, int y)
{
	int 	w;
	int 	h;
	int			i;
	
	h = 16;
	while (h)
	{
		w = 8;
		while (w)
		{
			i = x + w + (y + h) * WIDTH;
			if (0 < x + w && x + w < WIDTH && 0 < y + h && y + h < HEIGHT)
				((int *)(main->data_addr))[i] = SQW;
			w--;
		}
		h--;
	}
}

void	render_background_code(t_main *main)
{
	unsigned long	i;
	int x;
	int y;
	
	i = 0;
	x = 30;
	y = 30;
	while (i < MEM_SIZE)
	{
		drow_sqw(main, x, y);
		x += 10;
		drow_sqw(main, x, y);
		i ++;
		x += 10;
		if (i && i % 2 == 0)
			x += 10;
		if (i && i % 98 == 0)
		{
			y += 25;
			x = 30;
		}
	}
}

static void		render_code(t_main *main)
{
	char			s[] = "0123456789abcdef";
	char 			str[2];
	unsigned char	*tab;
	unsigned long	i;
	int x;
	int y;
	
	i = 0;
	x = 30;
	y = 30;
	str[1] = '\0';
	tab = (unsigned char*)main->area;
	while (i < MEM_SIZE)
	{
		str[0] = *(s + tab[i] / 16);
		mlx_string_put(main->mlx, main->win, x, y,
					   TEXT_COLOR, str);
		str[0] = *(s + tab[i] % 16);
		mlx_string_put(main->mlx, main->win, x += 10, y,
					   TEXT_COLOR, str);
		i ++;
		x += 10;
		if (i && i % 2 == 0)
			x += 10;
		if (i && i % 98 == 0)
		{
			y += 25;
			x = 30;
		}
	}
}

static void		render_menu(t_main *main)
{
	mlx_string_put(main->mlx, main->win, 85, 20,
				   TEXT_COLOR, "MENU");
	mlx_string_put(main->mlx, main->win, 65, 60,
				   TEXT_COLOR, "Run / Pause - \"P\"");
	mlx_string_put(main->mlx, main->win, 65, 100,
				   TEXT_COLOR, "Move one step - \"Space\"");
	mlx_string_put(main->mlx, main->win, 65, 140,
				   TEXT_COLOR, "Speed - Press +/-");
	mlx_string_put(main->mlx, main->win, 65, 180,
				   TEXT_COLOR, "Reset - \"R\"");
}

void			render(t_main *main)
{
	render_background(main);
	render_background_code(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img, 0, 0);
	render_code(main);
	//render_menu(main);
}