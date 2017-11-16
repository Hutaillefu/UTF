#ifndef UNIT_TEST_H
# define UNIT_TEST_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>


# define RED "\x1b[31m"
# define RESET "\x1b[0m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"




typedef int (*func_test)(void);

typedef struct		s_test
{
	func_test 	test;
	int		status; // -1 not done, 0 fail, 1 success
}			t_test;

typedef struct		s_group_tests
{
	char		*func_name;
	int		nb_tests;
	t_test		**tests;
}			t_group_tests;

t_test		*new_fresh_test(void);
t_test		*new_test(func_test test);
t_group_tests	*new_fresh_group_tests(void);
t_group_tests	*new_group_tests(char *func_name, func_test *tests);

// To implement in test_func_to_test.c
t_group_tests	*get_tests(void);
#endif
