#include "corewar.h"

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
			put_player_in_sell(main, i * constant, size, i + 1);
		}
		++i;
	}
}

void			init_cursors(t_main *main)
{
	t_cursor	*cursor;
	int			constant;
	int			i;

	i = 0;
	constant = MEM_SIZE / main->players;
	while (i < main->players)
	{
		cursor = (t_cursor*)smart_malloc(sizeof(t_cursor));
		cursor->pos = i * constant;
		cursor->reg[0] = main->player[i].id;
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

static int			cor_close(void *main)
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
	
	main->ch = 0;
	
	if (main->flag_v)
	{
		mlx_key_hook(main->win, lem_hook_keydown, main);
		mlx_hook(main->win, 17, 0, cor_close, main);
		mlx_loop_hook(main->mlx, lem_loop_key_hook, main);
		mlx_loop(main->mlx);
	}
	else
	{
		while (main->i-- > 0 && main->cursor && main->cycle_to_die > 0)
			game_exec(main);
	}
	//print_memory(main->area, MEM_SIZE);
	return (0);
}