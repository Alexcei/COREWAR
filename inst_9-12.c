#include "corewar.h"

void	zjmp(t_main *main, t_cursor *cursor, char *area)
{
	uint16_t	addr;

	(void)main;
	memory_read(area, cursor->pos + 2, &addr, 2);
	rev_endian(&addr, 2);
	if (cursor->carry)
		cursor->pos += addr % IDX_MOD;
}

void	ldi(t_main *main, t_cursor *cursor, char *area)
{
	uint8_t		regnum;
	uint16_t	addr;

	(void)main;
	if (cursor->types[0] == T_DIR_CODE)
	{
		memory_read(area, cursor->pos + 6, &regnum, 1);
		if (regnum > 16)
			return ;
		memory_read(area, cursor->pos + 2, &cursor->reg[regnum - 1], 4);
		return ;
	}
	memory_read(area, cursor->pos + 2, &addr, 2);
	rev_endian(&addr, 2);
	memory_read(area, cursor->pos + 4, &regnum, 1);
	memory_read(area, cursor->pos + addr % IDX_MOD,
				&cursor->reg[regnum - 1], 4);
}

void	sti(t_main *main, t_cursor *cursor, char *area)
{
	uint8_t		regnum1;
	uint8_t		regnum2;
	uint16_t	addr;

	(void)main;
	memory_read(area, cursor->pos + 2, &regnum1, 1);
	if (cursor->types[2] == T_REG_CODE)
	{
		memory_read(area, cursor->pos + 3, &regnum2, 1);
		if (regnum1 > 16 || regnum2 > 16)
			return ;
		cursor->reg[regnum2 - 1] = cursor->reg[regnum1 - 1];
		return ;
	}
	memory_read(area, cursor->pos + 3, &addr, 2);
	rev_endian(&addr, 2);
	memory_write(area, cursor->pos + addr % IDX_MOD,
				 &cursor->reg[regnum1 - 1], 2);
}

void	op_fork(t_main *main, t_cursor *cursor, char *area)
{

}