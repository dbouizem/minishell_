# 🐚 **MINISHELL – TABLEAUX DE TESTS**
*Pour voir le rendu d’un fichier ```Ctrl + Shift + V```*


# ===============================

# 🟦 **PHASE 1 — Tests de base**

Cette phase consiste à mettre en place l’ossature minimale d’un shell.
Elle valide surtout la mise en place des fondations :

✔ Objectifs

Compiler sans erreurs ni warnings (-Wall -Wextra -Werror)

Gérer l’affichage d’un prompt

Lire une ligne de commande (readline)

Ajouter la ligne à l’historique

Gérer :

Ctrl+D (EOF)

exit

un environnement vide

stdin non-interactif

Aucun crash, comportement stable

Pas de memory leaks (hors readline)

🧠 Idée globale

→ Mettre en place un shell minimal fonctionnel, capable de s’ouvrir, afficher un prompt, répondre proprement à l’utilisateur et se fermer correctement.

| Test                   | Commande / Action                                | Attendu                                       |                                              |
| ---------------------- | ------------------------------------------------ | --------------------------------------------- | -------------------------------------------- |
| **Compilation**        | `make`                                           | Aucun warning, aucune erreur, pas de relink   |                                              |
| **Relink**             | `make` après un premier make                     | Aucune recompilation                          |                                              |
| **Lancement**          | `./minishell`                                    | Message de bienvenue 🐚 + prompt `minishell$` |                                              |
| **Entrée vide**        | `<Enter>`                                        | Nouveau prompt, aucun crash                   |                                              |
| **Espaces seulement**  | `␣␣␣␣<Enter>`                                    | Nouveau prompt, aucun crash                   |                                              |
| **Historique**         | Entrer `hello`, `world`, `test`, puis flèches ↑↓ | Historique opérationnel                       |                                              |
| **exit**               | `exit`                                           | Message de sortie + fermeture propre          |                                              |
| **Ctrl+D**             | `Ctrl + D`                                       | Fermeture propre                              |                                              |
| **env vide**           | `env -i ./minishell`                             | Création PWD, SHLVL, _, warning si vide       |                                              |
| **stdin non-terminal** | `echo "ls" \| ./minishell`                            | stdin = pip -> lire, exécuter, quitter (Afficher “stdin is not a terminal” ? pas demanse a 42) |
| **Valgrind**           | `valgrind ./minishell`                           | Pas de leaks (hors readline)                  |                                              |


# ===============================

# 🟩 **PHASE 2 — Tokenizer**

Ici, tu dois transformer la ligne tapée en une liste de tokens lisibles par ton programme.

✔ Objectifs

Découper la ligne en tokens :

mots ```WORD```

espaces ```SPACES```

pipes ```|```

redirections ```<, >, <<, >>```

variables ```$USER, $?, etc.```

quotes simples ```'...'```

quotes doubles ```"..."```

Détecter les erreurs : ```quotes non fermées```

Aucun crash quelle que soit l’entrée

🧠 Idée globale

→ Le tokenizer lit la ligne caractère par caractère et identifie tous les éléments syntaxiques nécessaires à la suite.
C’est une phase pure analyse lexicale, rien n’est encore exécuté.

# Minishell – Tests du Lexer

| Catégorie                 | Commande                    | Tokens attendus (selon les règles du vrai minishell)                          |
|---------------------------|-----------------------------|-------------------------------------------------------------------------------|
| **Simple**                | `ls`                        | `WORD:'ls'`                                                                   |
| **Arguments**             | `ls -la`                    | `WORD:'ls'` / `SPACES` / `WORD:'-la'`                                         |
| **Espaces multiples**     | `ls    -la`                 | `WORD:'ls'` / `SPACES:'    '` / `WORD:'-la'`                                  |
| **Pipe**                  | `ls \| grep test`            | `WORD:'ls'` / `SPACES` / `PIPE:'\|'` / `SPACES` / `WORD:'grep'` / `SPACES` / `WORD:'test'` |
| **Redirection <**         | `cat < input.txt`           | `WORD:'cat'` / `SPACES` / `INPUT:'<'` / `SPACES` / `WORD:'input.txt'`         |
| **Redirection >**         | `echo hi > out`             | `WORD:'echo'` / `SPACES` / `WORD:'hi'` / `SPACES` / `TRUNC:'>'` / `SPACES` / `WORD:'out'` |
| **Redirection <<**        | `cat << EOF`                | `WORD:'cat'` / `SPACES` / `HEREDOC:'<<'` / `SPACES` / `WORD:'EOF'`            |
| **Redirection >>**        | `echo hi >> out`            | `WORD:'echo'` / `SPACES` / `WORD:'hi'` / `SPACES` / `APPEND:'>>'` / `SPACES` / `WORD:'out'` |
| **Variable**              | `echo $USER`                | `WORD:'echo'` / `SPACES` / `WORD:'$USER'`                                     |
| **Variable $?**           | `echo $?`                   | `WORD:'echo'` / `SPACES` / `WORD:'$?'`                                        |
| **Variables collées**     | `echo $USER$HOME`           | `WORD:'echo'` / `SPACES` / `WORD:'$USER$HOME'`                                |
| **Quotes simples**        | `echo 'hello'`              | `WORD:'echo'` / `SPACES` / `WORD:'hello'`                                     |
| **Quotes simples + $**    | `echo '$USER'`              | `WORD:'echo'` / `SPACES` / `WORD:'$USER'`                                     |
| **Quotes doubles**        | `echo "hello"`              | `WORD:'echo'` / `SPACES` / `WORD:'hello'`                                     |
| **Quotes doubles + var**  | `echo "$USER"`              | `WORD:'echo'` / `SPACES` / `WORD:'$USER'`                                     |
| **Quotes non fermées**    | `echo "hello`               | Erreur : `unclosed quote '"'"`                                                |
| **Sans espaces**          | `cat<input>out`             | `WORD:'cat'` / `INPUT:'<'` / `WORD:'input'` / `TRUNC:'>'` / `WORD:'out'`       |
| **Pipes multiples**       | `ls \| cat \| cat`            | `WORD:'ls'` / `SPACES` / `PIPE` / `SPACES` / `WORD:'cat'` / `SPACES` / `PIPE` / `SPACES` / `WORD:'cat'` |
| **Quotes contenant opérateurs** | `echo "x \| y > z"`  | `WORD:'echo'` / `SPACES` / `WORD:'x \| y > z'` *(un seul WORD)*                |
| **tokenize(NULL)**        | —                           | Retourne `NULL` sans crash                                                    |

# ===============================

# 🟧 **PHASE 3 — Parsing**

Maintenant que tu as une liste de tokens, tu dois construire une structure logique qui décrit la commande.

✔ Objectifs

Construire la liste des commandes (cmd1, cmd2…)

Gérer correctement :

arguments

pipes

redirections (entrée, sortie, append, heredoc)

Valider la syntaxe :

ls | → erreur

> sans fichier → erreur

Préparer une structure exploitable pour l’exécution

🧠 Idée globale

→ Le parsing transforme les tokens en arbre de commandes ou en structures chaînées, comme un mini interpréteur.
C’est comme traduire une phrase en grammaire C : sujet, verbe, complément.

| Catégorie             | Commande       | Attendu                            |                      |
| --------------------- | -------------- | ---------------------------------- | -------------------- |
| **Commande simple**   | `ls -la`       | 1 commande, args = ["ls", "-la"]   |                      |
| **Pipe**              | `cmd1          | cmd2`                              | 2 commandes chaînées |
| **Redirection >**     | `cmd > f`      | redirection TRUNC                  |                      |
| **Redirection <**     | `cmd < f`      | redirection INPUT                  |                      |
| **Append**            | `cmd >> f`     | redirection APPEND                 |                      |
| **Heredoc**           | `cmd << EOF`   | redirection HEREDOC                |                      |
| **Variable**          | `echo $HOME`   | token VAR                          |                      |
| **Quotes**            | `echo "hello"` | WORD `"hello"`                     |                      |
| **Erreur syntaxique** | `ls >`         | erreur de parsing (missing target) |                      |


# ===============================

# 🟨 **PHASE 4 — Expansion**

Cette phase applique les règles du shell pour remplacer certains éléments :

✔ Objectifs

Résoudre les variables :

```$USER $HOME $? $$```

Gérer les expansions à l’intérieur des quotes :

'...' : pas d’expansion "..." : expansion activée Fusionner les morceaux d’arguments

Gérer : arguments vides expansions dans les redirections (> $FILE)

🧠 Idée globale

→ Cette phase transforme ce que l'utilisateur a tapé en valeurs réelles utilisées par le shell.


| Catégorie                           | Commande                         | Résultat attendu         |
| ----------------------------------- | -------------------------------- | ------------------------ |
| **Expansion simple**                | `echo $USER`                     | djh                      |
|                                     | `echo $HOME`                     | /home/djh                |
|                                     | `echo $PATH`                     | valeur PATH              |
|                                     | `echo $PWD`                      | pwd actuel               |
| **Variable inexistante**            | `echo $NOTHING`                  | *(vide)*                 |
|                                     | `echo ABC$NOTHINGDEF`            | ABCDEF                   |
|                                     | `echo "$NOTHING"`                | ""                       |
| **Variables collées**               | `echo ABC$USERDEF`               | ABCdjhDEF                |
|                                     | `echo $USER$HOME$PWD`            | djh/home/djh/...         |
|                                     | `echo "$USER"_test`              | djh_test                 |
|                                     | `echo A"$USER"B`                 | AdjhB                    |
| **Double quotes**                   | `echo "$USER"`                   | djh                      |
|                                     | `echo "Hello $USER"`             | Hello djh                |
|                                     | `echo "$USER$HOME"`              | djh/home/djh             |
| **Simple quotes (pas d’expansion)** | `echo '$USER'`                   | $USER                    |
|                                     | `echo 'hello $USER'`             | hello $USER              |
|                                     | `echo '$HOME and $PWD'`          | $HOME and $PWD           |
| **Mélange de quotes**               | `echo "$USER'$HOME'"`            | djh'/home/djh'           |
|                                     | `echo "$USER"toto'$HOME'$PATH`   | djhtoto$HOME/usr/...     |
|                                     | `echo '$USER'"$HOME"'$PWD'`      | $USER/home/djh$PWD       |
| **$?**                              | `ls` + `echo $?`                 | 0                        |
|                                     | erreur syntaxe puis `echo $?`    | 2                        |
|                                     | commande inconnue puis `echo $?` | g_exit_status            |
| **$$**                              | `echo $$`                        | PID minishell            |
| **Redirections + expansion**        | `echo hi > $FILE`                | crée out.txt             |
|                                     | `echo hi > "$USER".txt`          | crée djh.txt             |
|                                     | `cat < "$HOME"/file.txt`         | ouvre /home/djh/file.txt |
| **Heredoc**                         | `<< EOF`                         | expand=1                 |
|                                     | `<< "EOF"`                       | expand=0                 |
| **Arguments vides**                 | `EMPTY="" ; echo "$EMPTY"`       | ""                       |
|                                     | `echo $EMPTY`                    | (argument vide)          |
|                                     | `echo "$EMPTY""$EMPTY"`          | ""                       |
| **Séquences complexes**             | `echo $$$USER`                   | PIDdjh                   |
|                                     | `echo "$""USER"`                 | `$USER`                  |
|                                     | `echo '"$USER"'`                 | "$USER"                  |
| **Non supporté (littéral)**         | `echo ${USER}`                   | ${USER}                  |
|                                     | `echo $[1+1]`                    | $[1+1]                   |
|                                     | `echo $USER:home`                | djh:home                 |


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
