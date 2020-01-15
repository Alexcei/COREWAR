#include "corewar.h"

void    and(t_main *main, t_cursor *cursor, char *area)
{
	char	mem[9];
	
	memory_read(area, cursor->pos + 2, mem, 9);
	if (cursor->types[0] == T_REG_CODE)
	{
		// if (mem[0] > 16 || !mem[0])
		// 	return ;
		// and_reg(cursor, area, mem);
	}
	if (cursor->types[0] == T_DIR_CODE)
	{
	
	}
	if (cursor->types[0] == T_IND_CODE)
	{
	
	}
}

void    or(t_main *main, t_cursor *cursor, char *area)
{}

void    xor(t_main *main, t_cursor *cursor, char *area)
{}