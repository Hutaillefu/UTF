#include <stdio.h>
#include <stdlib.h>

#include "../includes/unit_test.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

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
	printf("-- %s --\n", group_tests->func_name);
	while (i < group_tests->nb_tests)
	{
		group_tests->tests[i]->status = group_tests->tests[i]->test();
		if (group_tests->tests[i]->status == 0)
			printf("%stest %i : %d%s\n", RED, i, group_tests->tests[i]->status ,RESET);
		else if (group_tests->tests[i]->status == 1)
			printf("%stest %i : %d\n%s", GREEN, i, 	group_tests->tests[i]->status , RESET);
		i++;
	}
	printf("\n");
	return (0);
}

