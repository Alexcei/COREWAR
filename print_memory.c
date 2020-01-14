#include "corewar.h"

void	print_memory(const void *addr, size_t size)
{
	char			s[] = "0123456789abcdef";
	unsigned char	*tab;
	unsigned long	i;
	
	i = 0;
	tab = (unsigned char*)addr;
	while (i < size)
	{
		//ft_printf("%c", tab[i]);
		write(1, s + tab[i] / 16, 1);
		write(1, s + tab[i] % 16, 1);
		i ++;
		if (i && i % 2 == 0)
			write(1, " ", 1);
		if (i && i % 16 == 0)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}