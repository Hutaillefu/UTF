#ifndef UNIT_TEST_H
# define UNIT_TEST_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>


# define COLOR_RED "\x1b[31m"
# define COLOR_RESET "\x1b[0m"

typedef int (*func_test)(void);

typedef struct		s_test
{
	func_test 	test;
	int		status; // -1 not done, 0 fail, 1 success
}			t_test;

typedef struct		s_group_tests
{
	int		nb_tests;
	t_test		**tests;
}			t_group_tests;

t_test		*new_fresh_test(void);
t_test		*new_test(func_test test);
t_group_tests	*new_fresh_group_tests(void);
t_group_tests	*new_group_tests(func_test *tests);

// To implement in test_func_to_test.c
t_group_tests	*get_tests(void);
#endif
