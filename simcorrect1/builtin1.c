#include "shell.h"

/**
 * my_exit - custom exit handler function.
 * @info: Pointer to a structure containing relevant information.
 *
 *  Return: 0: If the exit argument is not provided
 *          -2: If the exit argument is successfully converted.
 */
int my_exit(info_t *info)
{
	int check;

	if (info->argv[1])  /* If  an exit arguement exists*/
	{
		check = my_atoi(info->argv[1]);
		if (check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			/*_eputchar('\n'); */
			write_stdout("\n");
			return (1);
		}
		info->err_num = check;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes current directory in shell
 * @info: Structure that has pssible arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *z, *dr, buffer[1024];
	int chdir_ret;

	z = getcwd(buffer, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			chdir_ret = /* TODO: what should it be? */
				chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(z);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should it be? */
			chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes cirrent directory
 * @info: Structure tht has potential arguments.maintains
 * constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts(" Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* Temp att_unused  */
	return (0);
}

/**
 * my_history - functions displays history list, .
 * @inf: Structure containing potential arguments. maintains
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(info_t *inf)
{
	print_list(inf->history);
	return (0);
}
