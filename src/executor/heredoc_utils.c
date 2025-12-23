#include "../../includes/minishell.h"

static int	should_copy_char(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		else
			return (1);
		return (0);
	}
	return (1);
}

void	restore_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

void	setup_heredoc_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old_int);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, old_quit);
}

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (should_copy_char(str[i], &quote))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
