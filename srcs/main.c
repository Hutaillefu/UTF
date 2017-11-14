#include "../includes/unit_test.h"

int	string_array_len(char **tab)
{
	int i;
	int y;
	int res;

	i = 0;
	res = 0;
	while (tab[i])
	{
		y = 0;
		while (tab[i][y])
			y++;
		res += y;
		i++;
	}
	return (res);
}

char	*get_command(char **strings)
{
	char 	*res;
	int	i;

	res = (char *)malloc(sizeof(char) * (string_array_len(strings) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (strings[i])
	{
		strcat(res, strings[i]);
		i++;
	}
	return (res);
}

int	file_exists(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	delete_file(char *file_name)
{
	char *params[] = {"rm -f ", file_name};
	char *command;

	if (file_exists(file_name) == 1)
	{
		command = get_command(params);
		if (!command)
			return ;
		printf("delete_file(%s)\n", command);
		system(command);
	}
}


char	*srcs_to_build_command(char **srcs)
{
	char	*res;
	int	total_len;
	int	i;

	i = 0;
	total_len = 0;
	while (srcs[i])
	{
		total_len += strlen(srcs[i]) + 1;
		i++;
	}

	res = (char *)malloc(sizeof(char) * total_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	total_len = 0;
	while (srcs[i])
	{
		total_len += strlen(srcs[i]);
		strcat(res, srcs[i]);
		res[total_len] = ' ';
		total_len++;
		i++;
	}
	res[total_len] = '\0';
	return (res);
}

int	compile_srcs(char **srcs)
{
	char *src;
	char command_build[] = "gcc -o src.o -c ";
	char *command;

	src = srcs_to_build_command(srcs);
	command = (char *)malloc(sizeof(char) * strlen(src) + strlen(command_build));
	strcat(command, command_build);
	strcat(command, src);
	printf("%s\n", command);
	return (system(command));
}

int	compile_test(char *test)
{
	char command_build[] = "gcc -o unit_test main_unit_test.c unit_test.c src.o ";
	char *command;
	
	command = (char *)malloc(sizeof(char) * strlen(test) + strlen(command_build));
	strcat(command, command_build);
	strcat(command, test);
	printf("%s\n", command);
	return (system(command));
}



/*
	Return 1 if the string match "-{option}", else return 0,
	if option is joker {*}, match any option., 
*/
int	is_args_option(char *str, char option)
{
	if (strlen(str) == 2 && str[0] == '-')
	{
		if (option == '*')
			return (1);
		if (option == str[1])
			return (1);
		return (0);
	}
	return (0);
}

/*
	Return the number of args in argv with option -option,
	Argv must be passed without prog_name,
	If option -option is is define more than once, only the first is used.
*/
int	count_args_with_option(char **argv, char option)
{
	int res;
	int args;
	int i;

	args = 0;
	i = 0;
	res = 0;

	while (argv[i])
	{
		if (is_args_option(argv[i], '*') == 1 && args == 1)
			return (res);
		if (is_args_option(argv[i], option) == 1)
			args = 1;
		else if (args == 1)
			res++;	
		i++;
	}
	return (res);
}


/*
	find each args in argv with option -option and puts it in srcs,
	Argv must be passed without prog_name,
	If option -option is is define more than once, only the first is used.
*/
void	take_args_with_option(char **srcs, char **argv, char option)
{
	int args;
	int i;
	int y;

	args = 0;
	i = 0;
	y = 0;

	while (argv[i])
	{
		if (is_args_option(argv[i], '*') == 1 && args == 1)
			return ;
		if (is_args_option(argv[i], option) == 1)
			args = 1;
		else if (args == 1)
		{
			srcs[y] = (char *)malloc(sizeof(char) * strlen(argv[i]));
			strcpy(srcs[y], argv[i]);
			printf("param with option -%c :  %s\n", option, srcs[y]);
			y++;
		}
		i++;
	}
	srcs[y] = '\0';
}



void	process_tests(char **tests)
{
	int i;

	 i = 0;
	 while (tests[i])
	 {
		 if (compile_test(tests[i]) == 0)
			system("./unit_test");
		i++;
	 }
}

int	main(int argc, char **argv)
{
	int	nb_srcs;
	int	nb_tests;
	
	char	**srcs;
	char	**tests;

	int	src_compiled;

	if (argc == 1)
		return (0);

	argv++; // pass prog_name

	nb_srcs = count_args_with_option(argv, 's');
	nb_tests = count_args_with_option(argv, 't');

	printf("%i\n", nb_srcs);
	printf("%i\n", nb_tests);

	if ((srcs = (char **)malloc(sizeof(char *) * nb_srcs + 1)) == NULL)
		return (0);
	if ((tests = (char **)malloc(sizeof(char *) * nb_tests + 1)) == NULL)
		return (0);

	take_args_with_option(srcs, argv, 's');
	take_args_with_option(tests, argv, 't');

	src_compiled = compile_srcs(srcs);
	printf("result of compile : %i\n", src_compiled);

	if (src_compiled != 0)
		return (0);

	process_tests(tests);	

	return (0);
}
