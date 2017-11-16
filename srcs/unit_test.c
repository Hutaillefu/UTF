#include "../includes/unit_test.h"

/*
	Generate a new empty fresh test,
	status is set to -1 'not done',
	test is set to NULL
*/
t_test	*new_fresh_test(void){
	t_test	*tmp;
	
	tmp = malloc(sizeof(t_test));
	if (!tmp)
		return (NULL);
	tmp->status = -1;
	tmp->test = NULL;
	return (tmp);
}

/*
	Generate a new test,
	status is set to -1 'not done',
	test is set to test.
	Return NULL if test is NULL
*/
t_test	*new_test(func_test test)
{
	t_test *tmp;

	tmp = new_fresh_test();
	if (!tmp || !test)
		return (NULL);
	tmp->test = test;
	return (tmp);
}

/*
	Generate a new empty fresh group_tests,
	nb_tests is set to 0,
	tests is set to NULL
*/
t_group_tests	*new_fresh_group_tests(void)
{
	t_group_tests *tmp;
	
	tmp = malloc(sizeof(t_group_tests));
	if (!tmp)
		return (NULL);
	tmp->nb_tests = 0;
	tmp->tests = NULL;
	return (tmp);	
}

t_group_tests	*new_group_tests(char *func_name, func_test *tests)
{
	t_group_tests	*tmp;
	int		nb_tests;
	int		i;

	tmp = new_fresh_group_tests();
	if (!tmp || !tests)
		return (NULL);

	i = 0;
	while (tests[i])
		i++;
	nb_tests = i;
	tmp->nb_tests = nb_tests;

	tmp->tests = (t_test **)malloc(sizeof(t_test *) * nb_tests);
	if (!(tmp->tests))
		return (NULL);

	i = 0;
	while (i < nb_tests)
	{
		tmp->tests[i] = new_test(tests[i]);
		if (func_name)
			tmp->func_name = func_name;
		else
			tmp->func_name = "undefined func";
		if (!(tmp->tests[i]))
			return (NULL);
		i++;
	}

	return (tmp);
}
