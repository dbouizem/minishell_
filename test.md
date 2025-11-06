==================================================

Tests Phase 1:

 Compilation sans erreurs (-Wall -Wextra -Werror)
 Pas de relink inutile
 Message de bienvenue affiché
 Prompt fonctionnel
 Historique avec ↑↓
 Commande exit fonctionne
 Ctrl+D quitte proprement
 Gestion environnement vide
 Détection stdin non-terminal
 Pas de memory leaks (sauf readline)

 Test 1: Compilation
bashmake
# Vérifier : pas d'erreurs, pas de warnings
# Vérifier : pas de relink si on refait make
make
Test 2: Lancement basique
bash./minishell
# Attendu :
# - Message de bienvenue coloré avec 🐚
# - Information sur le terminal
# - Prompt "minishell$ " qui apparaît
Test 3: Environnement
bash# Dans minishell :
(vide - juste Enter)
# Attendu : nouveau prompt, pas de crash

# Test avec espaces :

(plusieurs espaces + Enter)
# Attendu : nouveau prompt, pas de crash
Test 4: Historique readline
bash# Dans minishell, taper :
hello
world
test

# Puis utiliser les flèches ↑ ↓
# Attendu : navigation dans l'historique (hello, world, test)
Test 5: Commande exit
bash# Dans minishell :
exit
# Attendu : message "Exiting minishell..." et fermeture propre
Test 6: Ctrl+D (EOF)
bash./minishell
# Appuyer sur Ctrl+D
# Attendu : sortie propre du shell
Test 7: Environnement vide
bash# Lancer sans environnement :
env -i ./minishell
# Attendu :
# - Warning "No environment, creating minimal one"
# - Shell fonctionne quand même avec PWD, SHLVL, _
Test 8: Test avec stdin non-terminal
bashecho "test" | ./minishell
# Attendu : message d'erreur "stdin is not a terminal" et exit
Test 9: Mémoire (Valgrind)
bashvalgrind --leak-check=full --show-leak-kinds=all ./minishell
# Dans minishell :
test1
test2
exit

# Attendu :
# - Pas de leaks de TON code
# - Leaks de readline() sont acceptés (indiqués dans le sujet)

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
