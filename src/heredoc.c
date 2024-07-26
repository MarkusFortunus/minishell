#include "minishell.h"

// static char *get_eof(char *cmd)
// {
//     int i = 0;
//     while(cmd[i])
//     {
//         if (!strncmp(&cmd[i], "<<", 2) && i++) // pas sur
//         {
//             while (cmd[i] == ' ')
//                 i++;
//             return ft_strdup(&cmd[i]);
//         }
// 		i++;
//     }
//     return NULL;
// }

// bool heredoc(pipe_cmd_t *p_data, t_data *data)
// {
//     char *eof;
//     char *newline;
//     int read_size;
//     size_t len = 0;
// 	fprintf(stderr, "Debugging information: Child process running\n");
//     if (!(eof = get_eof(p_data->cmd))) // mettre un message derreur;
//         return false;
//     if (dup2(p_data->fd[1], 1) == -1 || close(p_data->fd[0]) == -1) //doije ferme aussi 1?
//         return false;
//     while ((read_size = getline(&newline, &len, stdin)) != -1) // readline
//     {
//         if (!strncmp(newline, eof, strlen(eof)) && newline[strlen(eof)] == '\n')
//             break ;
//         // verifier pour les $var
//             //to do
//         write(p_data->fd[1], newline, read_size);
//     }
//     free(newline);
//     // execute la commande
//     // in_between_cmd(p_data, data);
//     return true;
// }