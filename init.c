#include "corewar.h"

t_op	g_instr[COUNT_TOKENS + 1] =
		{
				{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
				{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
				{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
				{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
				{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
				{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
				{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
				{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
				{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
				{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
				{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
				{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
				{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
				{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
				{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
				{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
				{0, 0, {0}, 0, 0, 0, 0, 0}
		};

t_op_func	op_arr[COUNT_TOKENS] =
		{
				live, ld, st, add,
				sub, and, or, xor,
				zjmp, ldi, sti, op_fork,
				lld, lldi, lfork, aff
		};

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
	
	main = (t_main*)smart_malloc(sizeof(t_main));
	
	main->i = 20;
	main->cycle_to_die = 50;
	main->flag_v = 1;    // add parse v
	
	ft_bzero(main->cell, sizeof(t_cell));
	main->players = 0;
	main->cursor = NULL;
	main->last_cursor = NULL;
	if (!(main->area = (char*)ft_memalloc(sizeof(char) * (MEM_SIZE + 1))))
		die("malloc() does not work");
	main->area[MEM_SIZE] = 0;
	main->dump = 0;
	init_players(main);
	if (main->flag_v)
		init_mlx(main);
	return ((void*)main);
}