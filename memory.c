#include "corewar.h"

void	memory_read(char *area, int pos, void *dst, int size)
{
	int		i;
	char	*cdst;

	i = 0;
	cdst = (char *)dst;
	while (i < size)
	{
		cdst[i] = area[(pos + i) % MEM_SIZE];
		i++;
	}
}

void	memory_write(char *area, int pos, void *src, int size)
{
	int		i;
	char	*csrc;

	i = 0;
	csrc = (char *)src;
	while (i < size)
	{
		area[(pos + i) % MEM_SIZE] = csrc[i];
		i++;
	}
}

void	rev_endian(void *val, int size)
{
	char	*p;
	char	tmp;
	int		i;

	p = (char *)val;
	i = 0;
	while (i < size / 2)
	{
		tmp = p[size - i - 1];
		p[size - i - 1] = p[i];
		p[i] = tmp;
		i++;
	}
}