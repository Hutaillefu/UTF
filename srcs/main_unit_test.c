#include <stdio.h>
#include <stdlib.h>

#include "../includes/unit_test.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int i;
	t_group_tests *group_tests;

	i = 0;
	group_tests = get_tests();
	if (!group_tests)
		return (0);

	i = 0;
	while (i < group_tests->nb_tests)
	{
		printf("test %i : %d\n", i, group_tests->tests[i]->test());
		i++;
	}

	return (0);
}

