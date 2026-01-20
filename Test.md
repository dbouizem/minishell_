# 🐚 **MINISHELL – DOCUMENTATION COMPLÈTE**
*Pour voir le rendu formaté : `Ctrl + Shift + V` dans VS Code*

========================================================================================

# 📋 **TABLE DES MATIÈRES**

1. [Phase 1 — Fondations](#-phase-1--fondations)
2. [Phase 2 — Lexer (Tokenisation)](#-phase-2--lexer-tokenisation)
3. [Phase 3 — Parser](#-phase-3--parser)
4. [Phase 4 — Expansion](#-phase-4--expansion)
5. [Phase 5 — Exécution](#-phase-5--exécution)
6. [Phase 6 — Builtins](#-phase-6--builtins)
7. [Phase 7 — Signaux & Heredoc](#-phase-7--signaux--heredoc)
8. [Phase 8 — Opérateurs logiques et parenthèses (Bonus)](#-phase-8--opérateurs-logiques-et-parenthèses-bonus)
9. [Phase 9 — Wildcards `*` (Bonus)](#-phase-9--wildcards--bonus)
10. [Checklist Finale](#-checklist-finale)
11. [Commandes Utiles](#-commandes-utiles)

========================================================================================

Voici ta Phase 1 mise à jour avec la section sur les heredocs et SIGSEGV, parfaitement intégrée dans le même style :

# 🟦 **PHASE 1 — Fondations**

Cette phase consiste à mettre en place l'ossature minimale d'un shell fonctionnel.

## ✔ Objectifs

- Compiler sans erreurs ni warnings (`-Wall -Wextra -Werror`)
- Afficher un **prompt** et attendre une commande
- Lire une ligne avec `readline`
- Ajouter la ligne à l'**historique**
- Gérer les cas limites :
  - `Ctrl+D` (EOF) → quitte le shell
  - `exit` → quitte proprement
  - Environnement vide (`env -i`)
  - Mode non-interactif (`echo "ls" | ./minishell`)
- Aucun crash, comportement stable
- Pas de **memory leaks** (hors readline)

## 🧠 Idée globale

→ Mettre en place un shell minimal capable de s'ouvrir, afficher un prompt, lire des commandes et se fermer proprement.
→ Structure de base : `read → process → execute → cleanup`

## 🧪 Tableau de tests

| Test | Commande / Action | Résultat attendu |
|------|-------------------|------------------|
| **Compilation** | `make` | Aucun warning, aucune erreur, pas de relink |
| **Relink** | `make` (après un premier make) | `make: Nothing to be done for 'all'` |
| **Lancement** | `./minishell` | Prompt `minishell$` affiché |
| **Entrée vide** | `<Enter>` | Nouveau prompt, aucun crash |
| **Espaces seuls** | `   <Enter>` | Nouveau prompt, aucun crash |
| **Historique** | Entrer plusieurs commandes puis `↑` `↓` | Navigation dans l'historique |
| **exit** | `exit` | Fermeture propre du shell |
| **Ctrl+D** | `Ctrl+D` sur prompt vide | Fermeture propre du shell |
| **env vide** | `env -i ./minishell` | Shell démarre, gère l'absence d'environnement |
| **stdin non-terminal** | `echo "ls" \| ./minishell` | Exécute `ls` puis quitte |
| **Valgrind** | `valgrind ./minishell` | Pas de leaks (hors readline) |

**Note env -i (comparaison Bash)**
- `env -i bash` charge encore `/etc/profile` et peut recréer `PATH`, `LESSOPEN`, etc.
- Pour une comparaison pure : `env -i bash --noprofile --norc`
- Minishell peut n'initialiser que `PWD`, `SHLVL=1` et `_` : suffisant pour le sujet.

---

## ⚠️ **Test spécial — Heredoc & SIGSEGV (cas limite)**

Ce test montre que le comportement de minishell face à un **SIGSEGV volontaire** pendant un heredoc est **identique à celui de bash** et n'est **pas un bug**.

### 🎯 Objectif
Comparer minishell et bash lorsqu'ils sont **tués volontairement par SIGSEGV** pendant un heredoc.

### 🔹 Test 1 — minishell
**Terminal A**
```bash
./minishell
cat << EOF
```
(minishell attend l'entrée du heredoc)

**Terminal B**
```bash
pgrep minishell
kill -SEGV <PID>
```

**Résultat attendu**
```
segmentation fault (core dumped) ./minishell
```
➡️ minishell est tué immédiatement, retour au shell parent

### 🔹 Test 2 — bash (référence)
**Terminal A**
```bash
cat << EOF
```
(bash attend l'entrée du heredoc)

**Terminal B**
```bash
pgrep bash
kill -SEGV <PID>
```

**Résultat attendu**
```
segmentation fault (core dumped) bash
```
➡️ bash est tué immédiatement, retour au shell parent

### 🔹 Comparaison
| Point comparé | minishell | bash |
|---------------|-----------|------|
| heredoc lancé | ✅ | ✅ |
| SIGSEGV pendant heredoc | ✅ | ✅ |
| message de fin de job | ✅ | ✅ |
| cleanup possible | ❌ | ❌ |

**Conclusion** : Comportement **identique** entre minishell et bash sur ce cas.

### 🧠 Pourquoi ce n'est PAS un bug
- Le crash est **forcé volontairement**
- Le sujet **ne demande pas** de gérer SIGSEGV
- Même bash ne peut pas nettoyer dans ce cas
- SIGSEGV est un **signal fatal immédiat** → pas de cleanup garanti
- Le message est affiché par le **shell parent**, pas par minishell lui-même

### ⚠️ Note sur le terminal
- Dans une implémentation de heredoc **ligne par ligne** (sans mode raw), le terminal **n'est généralement pas modifié**
- Le terminal reste donc fonctionnel après SIGSEGV (comportement normal)

========================================================================================

# 🟩 **PHASE 2 — Lexer (Tokenisation)**

Cette phase transforme la ligne d'entrée en une liste de **tokens** exploitables.

## ✔ Objectifs

- Découper la ligne en tokens identifiables :
  - **Mots** (`WORD`)
  - **Espaces** (`SPACES`)
  - **Pipes** (`|`)
  - **Redirections** (`<`, `>`, `<<`, `>>`)
  - **Variables** (`$USER`, `$?`)
  - **Quotes simples** (`'...'`)
  - **Quotes doubles** (`"..."`)
- Détecter les **erreurs** : quotes non fermées
- Préserver le contenu **avec les quotes** (suppression ultérieure)
- Aucun crash quelle que soit l'entrée

## 🧠 Idée globale

→ Le lexer lit caractère par caractère et identifie les éléments syntaxiques.
→ Les quotes changent le mode de lecture (`in_single` / `in_double`).
→ C'est une analyse lexicale pure, rien n'est encore exécuté.

## 🧪 Tableau de tests

| Catégorie | Commande | Tokens attendus |
|-----------|----------|-----------------|
| **Simple** | `ls` | `WORD:'ls'` |
| **Arguments** | `ls -la` | `WORD:'ls'` / `SPACES` / `WORD:'-la'` |
| **Espaces multiples** | `ls    -la` | `WORD:'ls'` / `SPACES:'    '` / `WORD:'-la'` |
| **Pipe** | `ls \| grep test` | `WORD:'ls'` / `SPACES` / `PIPE` / `SPACES` / `WORD:'grep'` / `SPACES` / `WORD:'test'` |
| **Redirection <** | `cat < input.txt` | `WORD:'cat'` / `SPACES` / `INPUT:'<'` / `SPACES` / `WORD:'input.txt'` |
| **Redirection >** | `echo hi > out` | `WORD:'echo'` / `SPACES` / `WORD:'hi'` / `SPACES` / `TRUNC:'>'` / `SPACES` / `WORD:'out'` |
| **Redirection <<** | `cat << EOF` | `WORD:'cat'` / `SPACES` / `HEREDOC:'<<'` / `SPACES` / `WORD:'EOF'` |
| **Redirection >>** | `echo hi >> out` | `WORD:'echo'` / `SPACES` / `WORD:'hi'` / `SPACES` / `APPEND:'>>'` / `SPACES` / `WORD:'out'` |
| **Variable** | `echo $USER` | `WORD:'echo'` / `SPACES` / `WORD:'$USER'` |
| **Variable $?** | `echo $?` | `WORD:'echo'` / `SPACES` / `WORD:'$?'` |
| **Variables collées** | `echo $USER$HOME` | `WORD:'echo'` / `SPACES` / `WORD:'$USER$HOME'` |
| **Quotes simples** | `echo 'hello'` | `WORD:'echo'` / `SPACES` / `WORD:''hello''` |
| **Quotes simples + $** | `echo '$USER'` | `WORD:'echo'` / `SPACES` / `WORD:''$USER''` |
| **Quotes doubles** | `echo "hello"` | `WORD:'echo'` / `SPACES` / `WORD:'"hello"'` |
| **Quotes doubles + var** | `echo "$USER"` | `WORD:'echo'` / `SPACES` / `WORD:'"$USER"'` |
| **Quotes non fermées** | `echo "hello` | **Erreur** : `unclosed quote '"'` |
| **Sans espaces** | `cat<input>out` | `WORD:'cat'` / `INPUT:'<'` / `WORD:'input'` / `TRUNC:'>'` / `WORD:'out'` |
| **Pipes multiples** | `ls \| cat \| wc` | `WORD:'ls'` / `PIPE` / `WORD:'cat'` / `PIPE` / `WORD:'wc'` |
| **Quotes + opérateurs** | `echo "x \| y > z"` | `WORD:'echo'` / `SPACES` / `WORD:'"x \| y > z"'` *(un seul WORD)* |
| **tokenize(NULL)** | — | Retourne `NULL` sans crash |

**Note $$ (lexer)**
- Le lexer garde `$$` dans un seul token : `WORD:'$$'`.
- L'expansion PID n'est pas demandee par le sujet ; dans ce projet, `$$` finit par afficher `$` (phase 4).

========================================================================================

# 🟧 **PHASE 3 — Parser**

Cette phase transforme les tokens en structure de commandes exploitable.

## ✔ Objectifs

- Construire une **liste chaînée de commandes** (`t_cmd`)
- Extraire les **arguments** dans un tableau `char **args`
- Extraire les **redirections** dans une liste `t_redir`
- Valider la **syntaxe** :
  - `ls |` → erreur
  - `> sans fichier` → erreur
  - `| |` → erreur
  - Pipe en début : `| ls` → erreur
- Préparer une structure exploitable pour l'exécution

## 🧠 Idée globale

→ Le parser transforme les tokens en arbre de commandes.
→ Chaque commande est un nœud avec ses arguments et redirections.
→ Les pipes séparent les commandes en maillons de pipeline.

## 🧪 Tableau de tests

| Catégorie | Commande | Résultat attendu |
|-----------|----------|------------------|
| **Commande simple** | `ls -la` | 1 cmd ; args = `["ls", "-la", NULL]` |
| **Pipe simple** | `ls \| grep a` | 2 cmds ; `ls` → pipe → `grep a` |
| **Pipe multiple** | `ls \| cat \| wc` | 3 commandes chaînées |
| **Redirection >** | `ls > file` | cmd args = `["ls"]` ; redir : `> "file"` |
| **Redirection <** | `cat < file` | cmd args = `["cat"]` ; redir : `< "file"` |
| **Append >>** | `echo hi >> file` | cmd args = `["echo", "hi"]` ; redir : `>> "file"` |
| **Heredoc <<** | `cat << EOF` | cmd args = `["cat"]` ; redir : `<< "EOF"` |
| **Concat sans espace** | `cat<input>out` | args = `["cat"]` ; redirs : `< "input"`, `> "out"` |
| **Redirs avant cmd** | `< in cat` | redir `< "in"` puis args = `["cat"]` |
| **Args intercalés** | `echo a > f b` | args = `["echo", "a", "b"]` ; redir : `> "f"` |
| **Quote double** | `echo "hi"` | args = `["echo", "\"hi\""]` |
| **Quote simple** | `echo 'hello'` | args = `["echo", "'hello'"]` |
| **Variable** | `echo $HOME` | args = `["echo", "$HOME"]` *(pas d'expansion ici)* |
| **Erreur : redir vide** | `ls >` | **Erreur** : unexpected `newline` |
| **Erreur : pipe final** | `ls \|` | **Erreur** : unexpected `\|` |
| **Erreur : pipe début** | `\| ls` | **Erreur** : unexpected `\|` |
| **Erreur : quote ouverte** | `echo "hi` | **Erreur** : unclosed quote |

---

# 🟨 **PHASE 4 — Expansion**

Cette phase remplace les variables par leurs valeurs et retire les quotes.

## ✔ Objectifs

- Remplacer `$VAR` par sa valeur
- Remplacer `$?` par le code retour
- **Ne PAS** expanser dans les single quotes : `'$USER'` → `$USER`
- **Expanser** dans les double quotes : `"$USER"` → valeur
- Gérer `$` seul ou suivi d'espace → littéral `$`
- **Retirer les quotes** après expansion
- **Ne PAS** expanser le délimiteur du heredoc
- Gérer les variables inexistantes → chaîne vide

## 🧠 Idée globale

→ Parcourir caractère par caractère avec état `in_single` / `in_double`.
→ Si `$` hors single quotes → lire le nom de variable → remplacer.
→ Les quotes sont retirées **après** l'expansion.
→ **Ordre crucial** : expand → remove quotes.

## 🧪 Tableau de tests

| Catégorie | Input (USER=john) | Résultat attendu |
|-----------|-------------------|------------------|
| **Variable simple** | `echo $USER` | `john` |
| **Variable inexistante** | `echo $NOPE` | *(vide)* |
| **Exit status** | `ls ; echo $?` | `0` |
| **Exit status erreur** | `lss ; echo $?` | `127` |
| **Single quotes** | `echo '$USER'` | `$USER` |
| **Double quotes** | `echo "$USER"` | `john` |
| **$ seul** | `echo $` | `$` |
| **$ + espace** | `echo $ test` | `$ test` |
| **Mixte** | `echo "$USER"'$USER'` | `john$USER` |
| **Variable collée** | `echo $USER_test` | *(vide si pas défini)* |
| **Variables multiples** | `echo $USER$HOME` | `john/home/john` |
| **Collée texte** | `echo ABC$USERDEF` | `ABCjohnDEF` |
| **Redir expansion** | `export F=out ; echo hi > $F` | Crée fichier `out` |
| **Heredoc délimiteur** | `<< $EOF` | Délimiteur littéral `$EOF` |
| **Quotes dans redir** | `cat < "$FILE"` | Expansion + suppression quotes |
| **Argument vide** | `EMPTY="" ; echo "$EMPTY"` | `""` (argument vide) |
| **Séquence complexe** | `echo "$USER"'$HOME'$PATH` | `john$HOME/usr/bin...` |

========================================================================================

# 🟦 **PHASE 5 — Exécution**

Cette phase transforme les commandes en **processus réels** via `fork`, `execve` et pipes.

## ✔ Objectifs

- Exécuter une commande simple
- Exécuter un pipeline : `ls | grep x | wc -l`
- Appliquer les redirections : `<`, `>`, `>>`
- Gérer les erreurs (command not found, permissions)
- Propager le code retour `$?`
- **Fermer les file descriptors** correctement
- Restaurer stdin/stdout après exécution
- Chercher les commandes dans le `PATH`

## 🧠 Idée globale

→ Chaque commande du pipeline = 1 processus enfant.
→ Le shell crée N pipes pour N commandes.
→ Le parent attend tous les enfants (`waitpid`) et met à jour `$?`.
→ Les redirections modifient stdin/stdout **avant** `execve`.

## 🧪 Tableau de tests

| Catégorie | Commande | Résultat attendu |
|-----------|----------|------------------|
| **Commande simple** | `ls` | Affiche contenu du répertoire |
| **Chemin absolu** | `/bin/echo ok` | `ok` |
| **Chemin relatif** | `./a.out` | Exécute fichier local |
| **PATH** | `ls` | Trouvé dans `/bin` ou `/usr/bin` |
| **Cmd inexistante** | `blaablaa` | `command not found` + `$?=127` |
| **Pipeline simple** | `echo hi \| wc -c` | `3` |
| **Pipeline long** | `ls \| grep .c \| wc -l` | Fonctionne |
| **Redirection >** | `echo hi > f` | Crée fichier `f` |
| **Redirection >>** | `echo hi >> f` | Ajoute à `f` |
| **Redirection <** | `cat < f` | Lit depuis `f` |
| **Mix pipes + redir** | `cat < f \| grep hi > out` | Fonctionne |
| **Erreur permissions** | `./file_no_x` | `Permission denied` + `$?=126` |
| **PATH vide** | `unset PATH ; ls` | `command not found` + `$?=127` |
| **Restaurer stdout** | `echo hello ; ls` | `ls` s'affiche normalement |
| **Redir multiple** | `echo a > f1 > f2` | Seul `f2` contient `a` |

========================================================================================

# 🟩 **PHASE 6 — Builtins**

Les builtins sont des commandes internes au shell, exécutées **sans `execve`**.

## ✔ Objectifs

- Exécuter les builtins dans le **parent** (commande seule)
- Dans un pipeline → exécuter en **enfant** (pas d'effet sur le shell parent)
- Implémenter :
  - `echo` (avec option `-n`)
  - `cd` (avec chemin relatif ou absolu)
  - `pwd` (sans options)
  - `export` (sans options)
  - `unset` (sans options)
  - `env` (sans options ni arguments)
  - `exit` (sans options)

## 🧠 Idée globale

→ Les builtins qui modifient l'environnement (`cd`, `export`, `unset`) **doivent** être exécutés dans le parent.
→ Dans un pipeline, leur effet est local au processus enfant (comme bash).
→ Détection : vérifier si `cmd->args[0]` correspond à un builtin.

## 🧪 Tableau de tests

| Builtin | Commande | Résultat attendu |
|---------|----------|------------------|
| **echo** | `echo hello` | `hello` |
| **echo -n** | `echo -n hi` | `hi` (sans newline) |
| **echo multi -n** | `echo -n -n -n test` | `test` (sans newline) |
| **cd** | `cd /tmp ; pwd` | `/tmp` |
| **cd relatif** | `cd .. ; pwd` | Répertoire parent |
| **cd erreur** | `cd doesnotexist` | Message d'erreur + `$?=1` |
| **pwd** | `pwd` | Chemin courant |
| **export** | `export A=10 ; echo $A` | `10` |
| **export update** | `export A=5 ; export A=7 ; echo $A` | `7` |
| **export sans =** | `export A` | Pas d'erreur (bash ajoute la variable vide) |
| **unset** | `export A=5 ; unset A ; echo $A` | *(vide)* |
| **unset inexistant** | `unset NOPE` | Pas d'erreur |
| **env** | `env` | Affiche toutes les variables |
| **exit** | `exit` | Quitte minishell |
| **exit code** | `exit 42` | Code retour = `42` |
| **exit erreur** | `exit abc` | `numeric argument required` + `exit 2` |
| **exit multi args** | `exit 1 2` | `too many arguments` + **NE QUITTE PAS** + `$?=1` |
| **builtin en pipeline** | `export A=5 \| cat` | `A` n'existe pas dans le shell parent |

========================================================================================

# 🟥 **PHASE 7 — Signaux & Heredoc**

Cette phase rend le shell **vraiment interactif**, conforme à bash.

## ✔ Objectifs

### Signaux interactifs
- `Ctrl+C` → affiche nouveau prompt sur nouvelle ligne (ne quitte pas)
- `Ctrl+D` → quitte le shell
- `Ctrl+\` → ne fait rien (pas de core dump)

### Signaux en exécution
- **Enfant** → comportement par défaut (SIGINT tue le processus)
- **Parent** → ignore SIGINT et SIGQUIT pendant l'exécution

### Heredoc (`<<`)
- Lire les lignes jusqu'au délimiteur
- **Ne PAS** ajouter à l'historique
- Gérer l'expansion selon les quotes :
  - `<< EOF` → expansion activée
  - `<< "EOF"` ou `<< 'EOF'` → pas d'expansion
- Gérer `Ctrl+C` → heredoc interrompu proprement

## 🧠 Idée globale

→ Une variable globale `volatile sig_atomic_t g_signal_received` stocke le signal.
→ Les handlers modifient cette variable, le shell réagit ensuite.
→ Heredoc = partie la plus technique : fichier temporaire + `readline` + signaux.

## 🧪 Tableau de tests

| Catégorie | Action | Résultat attendu |
|-----------|--------|------------------|
| **Ctrl+C prompt vide** | `Ctrl+C` | Nouvelle ligne + nouveau prompt |
| **Ctrl+D prompt vide** | `Ctrl+D` | Quitte le shell |
| **Ctrl+\ prompt vide** | `Ctrl+\` | Rien |
| **Ctrl+C avec texte** | Taper `abc` puis `Ctrl+C` | Efface la ligne, nouveau prompt |
| **Ctrl+D avec texte** | Taper `abc` puis `Ctrl+D` | Rien (ne quitte pas) |
| **Ctrl+C cmd bloquante** | `cat` puis `Ctrl+C` | Tue `cat`, revient au prompt |
| **Ctrl+\ cmd bloquante** | `cat` puis `Ctrl+\` | Tue `cat` avec `Quit (core dumped)` + `$?=131` |
| **Heredoc simple** | `cat << EOF` | Lit jusqu'à `EOF` |
| **Heredoc expansion** | `cat << EOF` puis `$USER` | `$USER` est expansé |
| **Heredoc no expand** | `cat << "EOF"` puis `$USER` | `$USER` littéral |
| **Heredoc quote simple** | `cat << 'EOF'` puis `$USER` | `$USER` littéral |
| **Ctrl+C heredoc** | `cat << EOF` puis `Ctrl+C` | Stop heredoc + `$?=130` |
| **Redir + heredoc** | `cat << EOF > out` | `out` contient le texte |
| **Multi heredoc** | `cat << A << B` | Seul le dernier est utilisé |

========================================================================================

# 🟪 **PHASE 8 — Opérateurs logiques et parenthèses (Bonus)**

Cette phase consiste à implémenter les opérateurs de contrôle `&&` (ET) et `||` (OU),
ainsi que les parenthèses `()` pour grouper les commandes et modifier la priorité
d'évaluation, **sans créer de sous-shells**.

## ✔ Objectifs

- Implémenter les opérateurs logiques `&&` et `||` avec la bonne **priorité** (priorité naturelle de gauche à droite, modifiable par les parenthèses).
- Implémenter les **parenthèses `()`** pour grouper des commandes.
- **Pas de sous-shells** : l'exécution doit se faire dans le processus courant du shell.
- Gérer les **erreurs de syntaxe** (`&&`, `||` mal placés, parenthèses non fermées) avec un message d'erreur clair et **sans crash**.
- Maintenir le **code de retour `$?`** correct après chaque exécution.
- Assurer la **stabilité** : pas de segfault, pas de leaks mémoire supplémentaires.
- Le comportement doit **coller à celui de Bash** pour les mêmes commandes.

## 🧠 Idée globale

→ Étendre l'arbre de syntaxe abstraite (AST) pour y ajouter des **nœuds de type `AND_OR`** et `PAREN`.
→ Le `parser` doit gérer ces nouveaux opérateurs et structures.
→ L'`exécuteur` doit évaluer les branches gauche/droite en fonction du résultat (`0` pour vrai, autre pour faux) de la branche précédente.
→ Les parenthèses sont traitées comme un regroupement qui force l'évaluation de leur contenu en priorité, mais sans `fork()` dédié.

## 🧪 Tableau de tests (Comportement vs Bash)

| Test | Commande / Action | Résultat attendu (identique à Bash) | Vérification clé |
|------|-------------------|--------------------------------------|------------------|
| **1. Base `&&` (succès)** | `/bin/true && echo OK` | `OK` | L'exécution continue. |
| **2. Base `&&` (échec)** | `/bin/false && echo KO` | *(rien)* | L'exécution s'arrête. |
| **3. Base `||` (échec)** | `/bin/false \|\| echo OK` | `OK` | L'exécution continue. |
| **4. Base `||` (succès)** | `/bin/true \|\| echo KO` | *(rien)* | L'exécution s'arrête. |
| **5. Priorité naturelle (1)** | `/bin/false && echo A \|\| echo B` | `B` | `&&` a priorité sur `\|\|`. |
| **6. Priorité naturelle (2)** | `/bin/true && echo A \|\| echo B` | `A` | `\|\|` n'est pas exécuté. |
| **7. Parenthèse simple (1)** | `/bin/true && (echo A \|\| echo B)` | `A` | Le contenu des `()` est évalué en bloc. |
| **8. Parenthèse simple (2)** | `/bin/false && (echo A \|\| echo B)` | *(rien)* | Le `&&` bloque. |
| **9. Parenthèse simple (3)** | `/bin/false \|\| (echo A && echo B)` | `A B` | Le `\|\|` déclenche l'exécution du bloc. |
| **10. Parenthèses imbriquées (1)** | `/bin/true && ( /bin/false \|\| (echo X && echo Y) )` | `X Y` | Priorité respectée sur plusieurs niveaux. |
| **11. Parenthèses imbriquées (2)** | `/bin/false \|\| ( /bin/true && (echo 1 && echo 2) )` | `1 2` | |
| **12. Commande réelle (1)** | `ls /doesnotexist && echo OK \|\| echo FAIL` | `FAIL` | Code retour de `ls` déclenche le bon chemin. |
| **13. Commande réelle (2)** | `(ls /doesnotexist \|\| echo RECOVER) && echo END` | `RECOVER END` | Le groupe `()` réussit, donc `&&` s'exécute. |
| **14. Avec pipe (succès)** | `echo hello \| grep hello && echo FOUND` | `hello FOUND` | Interaction correcte pipe + logique. |
| **15. Avec pipe (échec)** | `echo hello \| grep bye \|\| echo NOT_FOUND` | `NOT_FOUND` | |
| **16. Code retour `$?` (1)** | `/bin/false \|\| echo OK ; echo $?` | `OK 0` | `$?` reflète la dernière commande (`echo`). |
| **17. Code retour `$?` (2)** | `/bin/true && /bin/false ; echo $?` | `1` | `$?` reflète l'échec de `/bin/false`. |
| **18. Erreur syntaxe : `&&` en début** | `&& echo test` | `syntax error` (pas de crash) | Détection d'opérateur mal placé. |
| **19. Erreur syntaxe : `\|\|` en fin** | `echo test \|\|` | `syntax error` (pas de crash) | Détection de commande manquante. |
| **20. Erreur syntaxe : Parenthèse ouvrante seule** | `( echo test` | `syntax error` (pas de crash) | Détection de parenthèse non fermée. |
| **21. Erreur syntaxe : Parenthèse fermante seule** | `echo test )` | `syntax error` (pas de crash) | Détection de parenthèse fermante sans ouvrante. |
| **22. Erreur syntaxe : Parenthèses vides** | `()` | `syntax error` (pas de crash) | Détection de groupe vide. |
| **23. Environnement vide** | `env -i ./minishell` puis `echo test && echo ok` | `test ok` | Fonctionne sans env. |
| **24. Mode non-interactif** | `echo "true && echo bonus" \| ./minishell` | `bonus` | Fonctionne en pipe. |
| **25. Valgrind (complexe)** | `valgrind ./minishell` puis tests ci-dessus et `exit` | Pas de nouveaux leaks (hors readline) | Stabilité mémoire. |

---

## 📝 Notes pour l'implémentation et la soutenance

*   **Priorité** : Dans `A && B || C`, l'évaluation est `(A && B) || C`. Les parenthèses permettent de forcer `A && (B || C)`.
*   **Pas de sous-shell** : C'est le point délicat du bonus. Il ne faut pas `fork()` pour les parenthèses, mais simplement évaluer récursivement leur contenu dans le contexte d'exécution courant.
*   **Gestion d'erreur** : En cas d'erreur de syntaxe, afficher un message sur `stderr` (ex: `minishell: syntax error near unexpected token '&&'`), ne pas exécuter la ligne, et mettre `$?` à `2` (comme Bash).
*   **Tests** : Durant la soutenance, exécuter ces tests en **parallèle avec Bash** pour prouver l'identité des comportements.

========================================================================================

# 🟩 **PHASE 9 — Wildcards `*` (Bonus)**

Cette phase consiste à implémenter l'expansion des wildcards `*` (uniquement pour le
répertoire courant), avec un comportement identique à Bash. Les fichiers cachés
(commençant par `.`) ne doivent apparaître que si explicitement demandés par `.*`.

## ✔ Objectifs

- Implémenter l'expansion `*` uniquement pour le **répertoire courant**.
- Respecter le **comportement de Bash** :
  - Expansion en **ordre lexicographique**
  - Exclusion des **fichiers cachés** sauf pour le pattern `.*`
  - En **cas d'absence de match**, le pattern est **conservé tel quel**
  - **Pas d'expansion** dans les quotes (`"*"`, `'*'`)
  - **Pas d'expansion** après expansion de variable (`echo $VAR` où `VAR="*"`)
- Gérer **plusieurs wildcards dans une même commande** (`echo *.txt a*`)
- **Intégration transparente** avec les autres fonctionnalités (pipes, redirections, opérateurs logiques)
- **Pas de crash** sur les cas limites (dossier vide, permissions)
- **Pas de memory leaks** supplémentaires

## 🧠 Idée globale

→ Ajouter une étape d'**expansion de wildcards** après le parsing et avant l'exécution.
→ Pour chaque **argument non-quoté**, vérifier s'il contient `*`.
→ Si oui, scanner le **répertoire courant** et matcher les noms de fichiers.
→ **Remplacer** l'argument par la liste des matches (ou le pattern original si aucun match).
→ Gérer le cas spécial `.*` qui inclut les fichiers cachés.
→ Attention à **l'ordre** : variable expansion → field splitting → wildcard expansion.

## 🧪 Préparation de l'environnement de test

```bash
# Créer un dossier de test propre
mkdir test_wildcard && cd test_wildcard
touch a b c
touch a.txt b.txt c.txt
touch abc abcd
touch .hidden .hidden2
mkdir dir1 dir2
```

## 🧪 Tableau de tests (Comportement vs Bash)

| Test | Commande / Action | Résultat attendu (identique à Bash) | Vérification clé |
|------|-------------------|--------------------------------------|------------------|
| **1. Wildcard simple** | `echo *` | `a abc abcd a.txt b b.txt c c.txt dir1 dir2` (ordre lexicographique) | Exclusion fichiers cachés, ordre correct |
| **2. Avec préfixe (1)** | `echo a*` | `a abc abcd a.txt` | Match avec préfixe |
| **3. Avec préfixe (2)** | `echo ab*` | `abc abcd` | |
| **4. Avec préfixe (3)** | `echo b*` | `b b.txt` | |
| **5. Avec suffixe (1)** | `echo *.txt` | `a.txt b.txt c.txt` | Match avec suffixe |
| **6. Avec suffixe (2)** | `echo *.c` | `*.c` | **Aucun match → pattern conservé** |
| **7. Wildcard milieu** | `echo a*d` | `abcd` | |
| **8. Plusieurs wildcards** | `echo *.txt a*` | `a.txt b.txt c.txt a abc abcd a.txt` | Expansion indépendante par argument |
| **9. Commande réelle (1)** | `ls *` | Liste tous les fichiers visibles + dossiers | Intégration avec `ls` |
| **10. Commande réelle (2)** | `ls a*` | `a abc abcd a.txt` | |
| **11. Fichiers cachés (1)** | `echo .*` | `.hidden .hidden2` | Pattern spécial pour fichiers cachés |
| **12. Fichiers cachés (2)** | `echo .*txt` | `.*txt` | Aucun match → pattern conservé |
| **13. Quotes doubles** | `echo "*"` | `*` | **Pas d'expansion dans les quotes** |
| **14. Quotes simples** | `echo '*.txt'` | `*.txt` | |
| **15. Mix quotes** | `echo "*txt"` | `*txt` | |
| **16. Variable (1)** | `export X=* ; echo $X` | `*` | **Pas d'expansion après variable** |
| **17. Variable (2)** | `export X="*.txt" ; echo $X` | `*.txt` | |
| **18. Avec opérateurs logiques (1)** | `ls *.txt && echo OK` | Liste des `.txt` puis `OK` | Intégration avec `&&` |
| **19. Avec opérateurs logiques (2)** | `ls *.c \|\| echo FAIL` | `FAIL` | Intégration avec `\|\|` |
| **20. Cas limite : suppression** | `echo * ; rm * ; echo *` | Liste → (rien) → `*` | Comportement après vidage du dossier |
| **21. Dossier vide** | (dans dossier vide) `echo *` | `*` | Aucun match → pattern conservé |
| **22. Environnement vide** | `env -i ./minishell` puis `echo *` | Liste des fichiers (sans env) | Fonctionne sans variables d'env |
| **23. Mode non-interactif** | `echo "echo *.txt" \| ./minishell` | `a.txt b.txt c.txt` | Fonctionne en pipe |
| **24. Valgrind** | `valgrind ./minishell` puis tests wildcards | Pas de nouveaux leaks | Stabilité mémoire |

## 🚫 **Tests INTERDITS (selon le sujet)**

Ces fonctionnalités **NE DOIVENT PAS** être implémentées (résultat attendu : le pattern est affiché tel quel) :

| Test | Commande | Résultat attendu |
|------|----------|------------------|
| **Wildcard récursif** | `echo dir1/*` | `dir1/*` |
| **Double wildcard** | `echo **/*` | `**/*` |
| **Wildcard `?`** | `echo a?c` | `a?c` |
| **Classes de caractères** | `echo [ab]*` | `[ab]*` |

## 📝 Notes pour l'implémentation et la soutenance

*   **Ordre d'expansion** : Suivre l'ordre POSIX : 1) Expansion des variables (`$VAR`), 2) Field splitting, 3) Expansion des wildcards.
*   **Fichiers cachés** : Seul le pattern `.*` doit les inclure. Pour `*`, ils doivent être exclus.
*   **Pattern conservé** : Si aucun fichier ne correspond au pattern, **ne pas supprimer l'argument** mais le laisser tel quel (comportement Bash).
*   **Performance** : Pour le répertoire courant uniquement, pas besoin de récursion. Un simple `opendir()`/`readdir()` suffit.
*   **Tests en live** : Pendant la soutenance, créer le dossier de test et exécuter les commandes **côte à côte avec Bash** pour prouver l'identité des résultats.
*   **Intégration** : Vérifier que les wildcards fonctionnent bien avec toutes les autres fonctionnalités (redirections, pipes, opérateurs logiques).

## 🎯 Points clés pour les correcteurs

✔️ **Même comportement que Bash** pour tous les tests ci-dessus
✔️ **Pas d'expansion dans les quotes** (différence majeure avec le comportement sans quotes)
✔️ **Exclusion correcte des fichiers cachés** (sauf pour `.*`)
✔️ **Pattern conservé si aucun match** (pas de suppression silencieuse)
✔️ **Intégration transparente** avec le reste du shell
✔️ **Pas de crash, pas de leaks** sur les cas limites

========================================================================================

# ✅ **CHECKLIST FINALE**

## Avant de soumettre

### Compilation & Normes
- [ ] `make` compile sans warnings avec `-Wall -Wextra -Werror`
- [ ] Pas de relink inutile (`make` deux fois → `Nothing to be done`)
- [ ] Norminette passe sur tous les fichiers
- [ ] Makefile contient : `$(NAME)`, `all`, `clean`, `fclean`, `re`
- [ ] Libft compilée automatiquement

### Mémoire
- [ ] Pas de fuites mémoire (sauf readline)
- [ ] `valgrind --leak-check=full ./minishell` → 0 leaks dans votre code
- [ ] Tous les `malloc` ont un `free` correspondant
- [ ] Pas de double free

### Architecture
- [ ] Une seule variable globale : `volatile sig_atomic_t g_signal_received`
- [ ] Structure `t_shell` avec environnement et exit status
- [ ] Lexer → Parser → Expander → Executor

### Fonctionnalités de base
- [ ] Affichage du prompt
- [ ] Historique fonctionnel (flèches ↑↓)
- [ ] Gestion de `Ctrl+D` (EOF)
- [ ] Ligne vide ou espaces seuls → nouveau prompt
- [ ] Mode non-interactif (`echo "ls" | ./minishell`)

### Lexer
- [ ] Découpage en tokens correct
- [ ] Détection des quotes non fermées
- [ ] Préservation du contenu avec quotes
- [ ] Gestion des espaces multiples
- [ ] Aucun crash sur entrée malformée

### Parser
- [ ] Création de la liste de commandes
- [ ] Extraction des arguments
- [ ] Extraction des redirections
- [ ] Détection des erreurs syntaxiques :
- [ ] Pipe en début/fin
- [ ] Redirection sans fichier
- [ ] Commande vide entre pipes

### Expansion
- [ ] Variables d'environnement expansées (`$USER`, `$HOME`)
- [ ] `$?` retourne le code retour
- [ ] Pas d'expansion dans single quotes
- [ ] Expansion dans double quotes
- [ ] `$` seul reste littéral
- [ ] Variables inexistantes → chaîne vide
- [ ] Suppression des quotes après expansion

### Exécution
- [ ] Commandes simples fonctionnent
- [ ] Chemins absolus (`/bin/ls`)
- [ ] Chemins relatifs (`./a.out`)
- [ ] Recherche dans `PATH`
- [ ] `command not found` → `$?=127`
- [ ] Permission denied → `$?=126`
- [ ] Pipelines fonctionnent (`ls | grep | wc`)
- [ ] File descriptors correctement fermés
- [ ] stdin/stdout restaurés après exécution

### Redirections
- [ ] `<` (input)
- [ ] `>` (output truncate)
- [ ] `>>` (output append)
- [ ] `<<` (heredoc)
- [ ] Redirections multiples
- [ ] Gestion des erreurs (fichier inexistant, permissions)

### Builtins
- [ ] `echo` avec option `-n`
- [ ] `cd` avec chemins relatifs/absolus
- [ ] `pwd` sans options
- [ ] `export` sans options
- [ ] `unset` sans options
- [ ] `env` sans options ni arguments
- [ ] `exit` avec/sans arguments
- [ ] Builtins dans parent (sauf pipeline)
- [ ] Builtins dans pipeline → enfant

### Signaux
- [ ] `Ctrl+C` sur prompt → nouveau prompt
- [ ] `Ctrl+D` sur prompt → quitte
- [ ] `Ctrl+\` sur prompt → rien
- [ ] `Ctrl+C` pendant exécution → tue l'enfant
- [ ] `Ctrl+\` pendant exécution → quit avec core dump
- [ ] Signal handler utilise une variable globale

### Heredoc
- [ ] Lit jusqu'au délimiteur
- [ ] Pas d'ajout à l'historique
- [ ] Expansion si délimiteur non quoté
- [ ] Pas d'expansion si délimiteur quoté (`"EOF"` ou `'EOF'`)
- [ ] `Ctrl+C` interrompt heredoc → `$?=130`
- [ ] Fichier temporaire créé et supprimé
- [ ] Gestion propre des erreurs

### Tests de robustesse
- [ ] Entrées très longues (1000+ caractères)
- [ ] Commandes invalides
- [ ] Environnement vide (`env -i ./minishell`)
- [ ] `PATH` vide ou corrompu
- [ ] Fichiers inexistants
- [ ] Permissions insuffisantes
- [ ] Combinaisons complexes de pipes et redirections

========================================================================================

# 🛠️ **COMMANDES UTILES**

## Compilation & Tests
```bash
# Compilation
make

# Vérifier le relink
make && make

# Norminette
norminette src/ includes/

# Symboles externes utilisés
nm -u ./minishell

# Rechercher tous les usages de signal
grep -Rin "signal" .
```

## Valgrind
```bash
# Test de base
valgrind --leak-check=full ./minishell

# Test détaillé avec log
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./minishell

# Après exécution
cat valgrind.log | grep "ERROR SUMMARY"
```

## Tests de permissions
```bash
# Créer un fichier sans droits d'exécution
touch no_exec
chmod 000 no_exec
./minishell
# Tester : ./no_exec

# Créer un dossier sans droits
mkdir no_access
chmod 000 no_access
# Tester : cd no_access
```

## Tests de signaux
```bash
# Test Ctrl+C pendant sleep
./minishell
# Taper : sleep 10
# Appuyer sur Ctrl+C
# Vérifier : echo $?  (devrait être 130)

# Test Ctrl+\ pendant cat
./minishell
# Taper : cat
# Appuyer sur Ctrl+\
# Vérifier : echo $?  (devrait être 131)
```

## Tests de pipes
```bash
# Pipeline simple
echo "test" | wc -l

# Pipeline long
ls -la | grep "minishell" | wc -l

# Test avec erreur
ls /nonexistent | wc -l
echo $?  # Devrait être 2 (erreur de ls)
```

## Tests d'expansion
```bash
export USER=john
echo $USER          # john
echo "$USER"        # john
echo '$USER'        # $USER
echo $USER$HOME     # john/home/john
echo ABC${USER}DEF  # ABC${USER}DEF (${} non supporté)
```

## Tests de heredoc
```bash
# Heredoc simple
cat << EOF
hello
world
EOF

# Heredoc avec expansion
cat << EOF
User: $USER
Path: $PATH
EOF

# Heredoc sans expansion
cat << "EOF"
$USER
$PATH
EOF
```

## Tests de regression (bugs corriges)
```bash
# 1) Pipe seul
printf '|\n' | ./minishell > /tmp/ms_out 2> /tmp/ms_err
cat /tmp/ms_err
# Attendu: minishell: syntax error near unexpected token |

# 2) Dossier dans PATH -> command not found
rm -rf /tmp/msdir
mkdir -p /tmp/msdir/hello
PATH=/tmp/msdir ./minishell
# Dans minishell:
# hello
# echo $?
# Attendu: minishell: hello: command not found + 127

# 3) PATH non-exec puis exec
mkdir -p /tmp/ms_test
printf '#!/bin/sh\necho BAD\n' > /tmp/ms_test/ls
chmod 644 /tmp/ms_test/ls
PATH=/tmp/ms_test:/bin ./minishell
# Dans minishell:
# ls
# echo $?
# Attendu: sortie normale + 0

# 4) PATH seulement non-exec
PATH=/tmp/ms_test ./minishell
# Dans minishell:
# ls
# echo $?
# Attendu: Permission denied + 126
```

## Log des codes retour
```bash
# Sauvegarder les codes retour
./minishell
# Après chaque commande :
echo "Return code: $?" >> minishell.log

# Analyser
cat minishell.log
```
========================================================================================

# 📚 **RESSOURCES COMPLÉMENTAIRES**

## Documentation officielle
- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://tldp.org/LDP/abs/html/exitcodes.html
- https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- https://harm-smits.github.io/42docs/projects/minishell
- https://harm-smits.github.io/42docs/projects/minishell
- https://www.tutorialspoint.com/compiler_design/compiler_design_lexical_analysis.htm
- https://www.geeksforgeeks.org/c/pipe-system-call/
- https://frederic-lang.developpez.com/tutoriels/linux/prog-shell/?page=les-variables




## Tests recommandés
1. Tester **chaque fonctionnalité séparément** avant de combiner
2. Comparer avec bash : `bash -c "votre_commande"`
3. Valgrind **après chaque nouvelle feature**
4. Tests de régression : garder un script de tests

## Erreurs courantes à éviter
- ❌ Ne pas fermer les file descriptors → processus bloqués
- ❌ Oublier de restaurer stdin/stdout après une redirection
- ❌ Fuites dans les boucles (readline, parsing)
- ❌ Double free sur les redirections/arguments
- ❌ Mauvaise gestion des signaux (modifier structures au lieu de variable globale)
- ❌ Ne pas gérer `PATH` vide ou corrompu
- ❌ Builtins en enfant alors qu'ils doivent modifier le parent (sauf en pipeline)

========================================================================================

# 🎯 **STRATÉGIE DE DÉVELOPPEMENT**

## Ordre recommandé
1. ✅ **Phase 1** : Fondations (structure de base)
2. ✅ **Phase 2** : Lexer (tokenisation)
3. ✅ **Phase 3** : Parser (AST)
4. ✅ **Phase 4** : Expansion (variables)
5. ✅ **Phase 5** : Exécution (commandes simples)
6. ✅ **Phase 6** : Builtins
7. ✅ **Phase 5 suite** : Pipes
8. ✅ **Phase 5 suite** : Redirections
9. ✅ **Phase 7** : Signaux
10. ✅ **Phase 7 suite** : Heredoc
11. ✅ **Phase 8 suite** : Opérateurs logiques et parenthèses (Bonus)
12. ✅ **Phase 8 suite** : wildcards (Bonus)

## Après chaque phase
- [ ] Tests unitaires
- [ ] Valgrind
- [ ] Commit git avec message clair
- [ ] Documenter les cas limites

========================================================================================
