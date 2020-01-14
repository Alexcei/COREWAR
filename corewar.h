#ifndef COREWAR_H
# define COREWAR_H

# include "ft_printf/ft_printf.h"
# include <mlx.h>
# include "op.h"

# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0x0
# define SQW				0x1155ff

# define LEN		128
# define WIDTH 		LEN*20
# define HEIGHT		1200
# define SIZE 				HEIGHT * WIDTH

# define MIN_PLAYERS 2
# define DUMP "dump"
# define DUMP_LEN 4
# define HEADER_VAR 16

# define START_NAME 4
# define START_COMMENT (4 + PROG_NAME_LENGTH + 8)
# define CODE_SIZE_FILE 4
# define NULL_SIZE 4

# define T_REG_CODE 1
# define T_DIR_CODE 2
# define T_IND_CODE 3

typedef struct		s_player
{
	char			*content;
	int				file_size;
	int				code_size;
	int				id;
	char			*name;
	char			*comment;
	int 			current_lives;
}					t_player;

typedef struct		s_cursor
{
	int				reg[REG_NUMBER];
	int				pos;
	int				command;
	int				cycles;
	char			types[3];
	int				carry;
	struct s_cursor	*next;
}					t_cursor;

typedef struct			s_mouse
{
	char				put_left;
	char				put_right;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;

typedef struct			s_camera
{
	int					zoom;
	double				alpha;
	double				beta;
	double				x_offset;
	double				y_offset;
}						t_camera;

typedef struct			s_dot
{
	double				x;
	double				y;
	double				z;
}						t_dot;

typedef struct		s_main
{
	struct s_player	player[MAX_PLAYERS];
	int				players;
	struct s_cursor	*cursor;
	struct s_cursor	*last_cursor;
	char			*area;
	int				dump;
	int 			v;
	
	t_camera			*camera;
	t_mouse 			*mouse;
	int 				speed;
	int					width;
	int					height;
	int 				pause;
	int 				one_step;
	int					z_min;
	int					z_max;
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
}					t_main;

typedef struct		s_read
{
	char			*str;
	size_t			size;
}					t_read;

typedef struct		s_join
{
	char			*str;
	size_t			length;
	struct s_join	*next;
}					t_join;

void			*smart_malloc(size_t how_much);
void			die(const char *reason);
void			insert_params(t_main *main, int count_args, char *params[]);
void			init_player(t_main *main, int ch, int n);
int				is_number(int count_args, char *params[], int i);
void			help(void);
void			valid_filename(char *filename);
int				valid_number(char *str);
void			calc_ids(t_main *main);
void			memory_read(char *area, int pos, void *dst, int size);
void			memory_write(char *area, int pos, void *src, int size);
void			rev_endian(void *val, int size);
void			check_file_content(t_main *main, t_read *reader);
void			valid_file_size(char *str, int size);
void			file_get_content(t_read *new, int ch);

void			live(t_main *main, t_cursor *cursor, char *area);
void			ld(t_main *main, t_cursor *cursor, char *area);
void			st(t_main *main, t_cursor *cursor, char *area);

void			zjmp(t_main *main, t_cursor *cursor, char *area);
void			ldi(t_main *main, t_cursor *cursor, char *area);
void			sti(t_main *main, t_cursor *cursor, char *area);
void			op_fork(t_main *main, t_cursor *cursor, char *area);
void			lld(t_main *main, t_cursor *cursor, char *area);
void			lldi(t_main *main, t_cursor *cursor, char *area);
void			lfork(t_main *main, t_cursor *cursor, char *area);
void			aff(t_main *main, t_cursor *cursor, char *area);

int				lem_hook_keydown(int key, t_main *main);
int				lem_loop_key_hook(t_main *main);
void			render(t_main *main);
void			print_memory(const void *addr, size_t size);

# define MAIN_PAD_ESC		53
# define MAIN_PAD_R			15
# define MAIN_PAD_P			35
# define MAIN_PAD_SPACE		49

# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78

#endif