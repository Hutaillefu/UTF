#include "unit_test.h"

# define RED	"\x1b[31m"
# define RESET	"\x1b[0m"

void	put_error(char *str)
{
	printf(RED "%s\n" RESET, str);
}
