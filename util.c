#include "corewar.h"

void			*smart_malloc(size_t how_much)
{
	void	*new;

	if (!(new = ft_memalloc(how_much)))
	{
		ft_putstr("malloc() does not work\n");
		exit(1);
	}
	return (new);
}

void			die(const char *reason)
{
	int		fd;

	fd = 1;
	if (reason && reason[0])
		write(fd, reason, ft_strlen(reason));
	write(fd, "\n", 1);
	exit(1);
}