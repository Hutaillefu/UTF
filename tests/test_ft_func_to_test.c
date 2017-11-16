#include "../includes/unit_test.h"

char	ft_func_to_test(void);

int	test_func1(void)
{
	return (ft_func_to_test() == 'h');
}

int	test_func2(void)
{
	return (ft_func_to_test() == 'u');
}

int	test_func3(void)
{
	return (ft_func_to_test() == 'g');
}

int	test_func4(void)
{
	return (ft_func_to_test() == 'o');
}

t_group_tests	*get_tests(void)
{
	func_test tests[] = {&test_func1, &test_func2, &test_func3, &test_func4, NULL};
	return (new_group_tests("ft_func_to_test", tests));
}
