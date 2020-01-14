#include "corewar.h"

int				lem_loop_key_hook(t_main *main)
{
	char		*str;
	static int 		i;
	
	i > main->speed ? i = 0 : i++;
	if ((!i && main->pause == 1) || main->one_step)
	{
		main->one_step = 0;
		render(main);     // add one_inst
	}
	//render(main);
	if (main->pause == 0)
	{
		str = "PAUSE";
		mlx_string_put(main->mlx, main->win,
					   (WIDTH / 5) - 10, (HEIGHT / 2) - 10, 0x0FFFFFF, str);
	}
	return (0);
}