#include "../../includes/minishell.h"

static int	is_heredoc_quoted(const char *delimiter)
{
	int	i;

	if (!delimiter)
		return (0);
	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	init_heredoc_ctx(t_heredoc_ctx *ctx, t_redir *redir,
		t_shell *shell)
{
	ctx->fd = open_heredoc_tmp(ctx->tmp_filename, sizeof(ctx->tmp_filename));
	if (ctx->fd == -1)
		return (handle_file_error("heredoc"));
	reset_heredoc_fd(redir);
	g_signal = 0;
	ctx->expand = !is_heredoc_quoted(redir->file);
	ctx->term_changed = 0;
	ctx->params.fd = ctx->fd;
	ctx->params.delimiter = redir->file;
	ctx->params.expand = ctx->expand;
	ctx->params.shell = shell;
	ctx->params.manual_echo = 0;
	setup_heredoc_signals(&ctx->old_int, &ctx->old_quit);
	return (0);
}

static int	finish_heredoc(t_heredoc_ctx *ctx, t_redir *redir)
{
	restore_signals(&ctx->old_int, &ctx->old_quit);
	if (ctx->term_changed)
		restore_heredoc_term(ctx->params.shell, &ctx->saved_term);
	if (ctx->status != 0)
		return (abort_heredoc(ctx->fd, ctx->tmp_filename, ctx->status));
	return (finalize_heredoc_fd(ctx->fd, ctx->tmp_filename, redir));
}

int	handle_heredoc_redirection(t_redir *redir, t_shell *shell)
{
	t_heredoc_ctx	ctx;

	if (init_heredoc_ctx(&ctx, redir, shell) != 0)
		return (1);
	ctx.status = write_heredoc_content(&ctx.params);
	return (finish_heredoc(&ctx, redir));
}
