Commande simple : ls -la → 1 commande, 2 args

Pipe : cmd1 | cmd2 → 2 commandes liées

Redirection sortie : cmd > file → redir TRUNC

Redirection entrée : cmd < file → redir INPUT

Append : cmd >> file → redir APPEND

Heredoc : cmd << EOF → redir HEREDOC

Variables : echo $HOME → token VAR

Quotes : echo "hello" → token WORD avec quotes

Erreurs syntaxiques : ls > → message d'erreur
