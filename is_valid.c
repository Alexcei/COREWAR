#include "corewar.h"

int				is_number(int count_args, char *params[], int i)
{
	return (++i == count_args || !ft_isdigit(params[i][0]) ? 0 : 1);
}

void			valid_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		help();
	if (ft_strcmp(filename + (len - 4), ".cor"))
		help();
}

int				valid_number(char *str)
{
	int		number;

	if ((number = ft_atoi(str)) <= 0)
		help();
	return (number);
}

void			valid_file_size(char *str, int size)
{
	int		res;

	(void)str;
	res = PROG_NAME_LENGTH + COMMENT_LENGTH + HEADER_VAR;
	if (size < res)
		die("Content from file so small");
	if (size > res + CHAMP_MAX_SIZE)
		die("Content from file too long");
}
