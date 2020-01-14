#include "corewar.h"

static	void	init_players(t_main *main)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		main->player[i].content = NULL;
		main->player[i].file_size = 0;
		main->player[i].code_size = 0;
		main->player[i].id = 0;
		++i;
	}
}

void	put_player_in_sell(t_main *main, int start, int len, int player)
{
	while (len--)
	{
		main->cell[start].player = player;
		start++;
	}
}

void			init_area(t_main *main)
{
	int		constant;
	int		start;
	int 	size;
	int		i;

	constant = MEM_SIZE / main->players;
	start = START_COMMENT + COMMENT_LENGTH + NULL_SIZE;
	i = 0;
	while (i < main->players)
	{
		if (main->player[i].code_size)
		{
			size = main->player[i].code_size;
			ft_memcpy(main->area + (i * constant),
					  main->player[i].content + start, size);
			ft_printf("%d\n", main->player[i].code_size);
			put_player_in_sell(main, i * constant, size, i + 1);
		}
		++i;
	}
}

int		init_mlx(t_main *main)
{
	if (!(main->mlx = mlx_init()) ||
		!(main->win = mlx_new_window(main->mlx, WIDTH, HEIGHT, "COREWAR")) ||
		!(main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT)))
		return (0);
	main->data_addr = mlx_get_data_addr(main->img, &main->bits_per_pixel,
										&main->size_line, &main->endian);
	return (1);
}

void			*init()
{
	t_main	*main;
	int 	i;
	
	i = 0;
	main = (t_main*)smart_malloc(sizeof(t_main));
	//ft_bzero(main->cell, sizeof(t_cell));
//	while (i < MEM_SIZE)
//	{
//		main->cell[i].player = 0;
//		i++;
//	}
	main->players = 0;
	main->cursor = NULL;
	main->last_cursor = NULL;
	if (!(main->area = (char*)ft_memalloc(sizeof(char) * (MEM_SIZE + 1))))
		die("malloc() does not work");
	main->area[MEM_SIZE] = 0;
	main->dump = 0;
	init_players(main);
	init_mlx(main);
	return ((void*)main);
}

void			init_cursors(t_main *main)
{
	t_cursor	*cursor;
	int			constant;
	int			i;
	int			j;

	i = 0;
	constant = MEM_SIZE / main->players;
	while (i < main->players)
	{
		cursor = (t_cursor*)smart_malloc(sizeof(t_cursor));
		cursor->pos = i * constant;
		cursor->carry = 0;
		cursor->reg[0] = main->player[i].id;
		j = 1;
		while (j < REG_NUMBER)
		{
			cursor->reg[j] = 0;
			++j;
		}
		cursor->next = main->cursor;
		main->cursor = cursor;
		++i;
	}
}

void			test(t_main *main)
{
	 int i;

	 i = 0;
	 while (i < MEM_SIZE)
	 {
	 	ft_printf("%03d", main->area[i]);
	 	if (!(i % 100))
	 		ft_printf("\n");
	 	++i;
	 }

//	t_cursor *cursor;
//
//	cursor = main->cursor;
//	while (cursor)
//	{
//		ft_printf("%d\n", cursor->registers[0]);
//		cursor = cursor->next;
//	}
}

int			lem_close(void *main)
{
	(void)main;
	exit(EXIT_SUCCESS);
}

int				main(int ac, char *av[])
{
	t_main	*main;
	
	main = init();
	insert_params(main, ac, av);
	init_area(main);
	init_cursors(main);
	main->v = 1;    // add parse v
	if (main->v)
	{
		mlx_key_hook(main->win, lem_hook_keydown, main);
		mlx_hook(main->win, 17, 0, lem_close, main);
		mlx_loop_hook(main->mlx, lem_loop_key_hook, main);
		mlx_loop(main->mlx);
	}
	else
		print_memory(main->area, MEM_SIZE);
	return (0);
}