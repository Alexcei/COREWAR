#include "corewar.h"

void	count_coursor(t_main *main)
{
	t_cursor	*cursor;
	
	cursor = main->cursor;
	main->cursors = 0;
	while (cursor)
	{
		main->cursors++;
		ft_printf("%d\n", cursor->pos);
		main->cell[cursor->pos].cursor = 1;
		cursor = cursor->next;
	}
}

int				lem_loop_key_hook(t_main *main)
{
	char		*str;
	static int 		i;
	
	str = "RUN";
	i > main->speed ? i = 0 : i++;
	if ((!i && main->pause == 1) || main->one_step)
	{
		main->one_step = 0;
		while (main->i-- > 0 && main->cursor && main->cycle_to_die > 0)
		{
			game_exec(main);
			count_coursor(main);
			render(main);
		}
	}
	//render(main);
	if (main->pause == 0)
		str = "PAUSE";
	mlx_string_put(main->mlx, main->win,
					   WIDTH - 350, 50, TEXT_COLOR, str);
	return (0);
}