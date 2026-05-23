#include <unistd.h>
#include <stdlib.h>

int check_first_char(char *str);
int check_invalid_input(int argc, char *argv);

int	main(int argc, char **argv)
{
	check_invalid_input(argc, argv[1]);
	check_first_char(argv[1]);
	return (0);
}
