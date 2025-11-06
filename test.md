==================================================

Tests Phase 1:

==================================================

Tests Phase 2:

==================================================

Tests Phase 3:

Commande simple : ls -la → 1 commande, 2 args
Pipe : cmd1 | cmd2 → 2 commandes liées
Redirection sortie : cmd > file → redir TRUNC
Redirection entrée : cmd < file → redir INPUT
Append : cmd >> file → redir APPEND
Heredoc : cmd << EOF → redir HEREDOC
Variables : echo $HOME → token VAR
Quotes : echo "hello" → token WORD avec quotes
Erreurs syntaxiques : ls > → message d'erreur

==================================================

Tests Phase 4:

echo $USER → djh
echo '$USER' → $USER
echo "Bonjour $USER" → Bonjour djh
echo $UNDEFINED → (ligne vide)
echo "Test:$UNDEFINED" → Test:
echo $1 → (ligne vide)
echo "User:'$USER'" → User:'djh'
echo '"$USER"' → "$USER"
echo "Bonjour"$USER"!" → Bonjourdjh!
echo "$USER est dans $PWD" → djh est dans /chemin

==================================================

Tests Phase 5:

==================================================

Tests Phase 6:

==================================================

Tests Phase 7:

==================================================

Tests Phase 8:

==================================================

Tests Phase 9:

==================================================

Tests Phase 10:

==================================================
