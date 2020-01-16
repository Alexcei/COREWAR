#include "corewar.h"

void	zjmp(t_main *main, t_cursor *cursor, char *area)
{
	uint16_t	addr;

	(void)main;
	memory_read(area, cursor->pos + 1, &addr, 2);
	rev_endian(&addr, 2);
	if (cursor->carry)
		cursor->pos += addr % IDX_MOD;
	main->move = 2;
}

void	ldi(t_main *main, t_cursor *cursor, char *area)
{

}

void	sti(t_main *main, t_cursor *cursor, char *area)
{

}

void	lldi(t_main *main, t_cursor *cursor, char *area)
{

}