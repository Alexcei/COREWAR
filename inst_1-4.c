#include "corewar.h"

void    live(t_main *main, t_cursor *cursor, char *area)
{
	int32_t	val;
	
	//ft_printf("1\n");
	memory_read(area, cursor->pos + 1, &val, 4);
	rev_endian(&val, 4);
	//ft_printf("2\n");
	//ft_printf("%d\n", val);
	if (-val <= main->players)
		main->player[-val].current_lives++;
	main->move = 4;
}

void	ld(t_main *main, t_cursor *cursor, char *area)
{
	uint8_t		regnum;
	int16_t		addr;

	if (cursor->types[0] == T_DIR_CODE)
	{
		memory_read(area, cursor->pos + 6, &regnum, 1);
		if (regnum > 16)
			return ;
		memory_read(area, cursor->pos + 2, &cursor->reg[regnum - 1], 4);
		cursor->carry = !cursor->reg[regnum - 1];
		main->move = 6;
		return ;
	}
	memory_read(area, cursor->pos + 2, &addr, 2);
	rev_endian(&addr, 2);
	memory_read(area, cursor->pos + 4, &regnum, 1);
	memory_read(area, cursor->pos + addr % IDX_MOD,
				&cursor->reg[regnum - 1], 4);
	cursor->carry = !cursor->reg[regnum - 1];
	main->move = 6;  // 4 должно быть!!!!
}

void	st(t_main *main, t_cursor *cursor, char *area)
{
	uint8_t		regnum1;
	uint8_t		regnum2;
	int16_t		addr;

	memory_read(area, cursor->pos + 2, &regnum1, 1);
	if (cursor->types[2] == T_REG_CODE)
	{
		memory_read(area, cursor->pos + 3, &regnum2, 1);
		if (regnum1 > 16 || regnum2 > 16 || !regnum1 || !regnum2)
			return ;
		cursor->reg[regnum2 - 1] = cursor->reg[regnum1 - 1];
		main->move = 3;
		return ;
	}
	if (regnum1 > 16 ||	!regnum1)
		return ;
	memory_read(area, cursor->pos + 3, &addr, 2);
	rev_endian(&addr, 2);
	memory_write(main, main->cell[cursor->pos].player, area, cursor->pos + addr % IDX_MOD,
				 &cursor->reg[regnum1 - 1], 2);
	main->move = 4;
}

void	add(t_main *main, t_cursor *cursor, char *area)
{
	int32_t		val[2];
	uint8_t		reg[3];

	memory_read(area, cursor->pos + 1, reg, 3);
	if (reg[0] > 16 || reg[1] > 16 || reg[2] > 16 ||
		!reg[0] || !reg[1] || !reg[2])
		return;
	val[0] = cursor->reg[reg[0] - 1];
	val[1] = cursor->reg[reg[1] - 1];
	rev_endian(&val[0], REG_SIZE);
	rev_endian(&val[1], REG_SIZE);
	cursor->reg[reg[2] - 1] = val[0] + val[1];
	rev_endian(&cursor->reg[reg[2] - 1], REG_SIZE);
	cursor->carry = !cursor->reg[reg[2] - 1];
}

void	sub(t_main *main, t_cursor *cursor, char *area)
{
	int32_t		val[2];
	uint8_t		reg[3];

	memory_read(area, cursor->pos + 1, reg, 3);
	if (reg[0] > 16 || reg[1] > 16 || reg[2] > 16 ||
		!reg[0] || !reg[1] || !reg[2])
		return;
	val[0] = cursor->reg[reg[0] - 1];
	val[1] = cursor->reg[reg[1] - 1];
	rev_endian(&val[0], REG_SIZE);
	rev_endian(&val[1], REG_SIZE);
	cursor->reg[reg[2] - 1] = val[0] - val[1];
	rev_endian(&cursor->reg[reg[2] - 1], REG_SIZE);
	cursor->carry = !cursor->reg[reg[2] - 1];
}