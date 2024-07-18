#include "../include/minishell.h"

//Error function, print error message and exit
void	ft_error(char *error)
{
	write(2, "Error:\n", 8);
	write(2, error, ft_strlen(error));
	exit(1);
}

//Free un tableau. Exit si un message est ajouter. Sinon, mettre "NULL"
void	ft_free(char **to_free, char *exit)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	if (exit)
		ft_error(exit);
}
