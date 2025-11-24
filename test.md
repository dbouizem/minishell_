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

## 📋 Préparation
```bash
make re
./minishell
```

---

## ✅ TEST 1: Commande simple
```bash
minishell$ ls
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'ls'
==============
```

---

## ✅ TEST 2: Commande avec arguments
```bash
minishell$ ls -la
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'ls'
SPACES     | ' '
WORD       | '-la'
==============
```

---

## ✅ TEST 3: Espaces multiples
```bash
minishell$ ls    -la
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'ls'
SPACES     | '    '
WORD       | '-la'
==============
```

---

## ✅ TEST 4: Pipe simple
```bash
minishell$ ls | grep test
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'ls'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'grep'
SPACES     | ' '
WORD       | 'test'
==============
```

---

## ✅ TEST 5: Redirections simples
```bash
minishell$ cat < input.txt
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'cat'
SPACES     | ' '
INPUT      | '<'
SPACES     | ' '
WORD       | 'input.txt'
==============
```

```bash
minishell$ echo hello > output.txt
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | 'hello'
SPACES     | ' '
TRUNC      | '>'
SPACES     | ' '
WORD       | 'output.txt'
==============
```

---

## ✅ TEST 6: Redirections doubles
```bash
minishell$ cat << EOF
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'cat'
SPACES     | ' '
HEREDOC    | '<<'
SPACES     | ' '
WORD       | 'EOF'
==============
```

```bash
minishell$ echo hello >> output.txt
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | 'hello'
SPACES     | ' '
APPEND     | '>>'
SPACES     | ' '
WORD       | 'output.txt'
==============
```

---

## ✅ TEST 7: Variables d'environnement
```bash
minishell$ echo $USER
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
VAR        | '$USER'
==============
```

```bash
minishell$ echo $?
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
VAR        | '$?'
==============
```

---

## ✅ TEST 8: Variables collées
```bash
minishell$ echo $USER$HOME
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
VAR        | '$USER'
VAR        | '$HOME'
==============
```

---

## ✅ TEST 9: Guillemets simples (single quotes)
```bash
minishell$ echo 'hello world'
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | ''hello world''
==============
```

```bash
minishell$ echo '$USER'
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | ''$USER''
==============
```

---

## ✅ TEST 10: Guillemets doubles (double quotes)
```bash
minishell$ echo "hello world"
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | '"hello world"'
==============
```

```bash
minishell$ echo "$USER"
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | '"'
VAR        | '$USER'
WORD       | '"'
==============
```

⚠️ **Note:** Pour les quotes doubles avec variables, le comportement peut varier selon ton implémentation.

---

## ✅ TEST 11: Guillemets non fermés
```bash
minishell$ echo "hello
```
**Attendu:**
```
minishell: unclosed quote `"`
```

```bash
minishell$ echo 'hello
```
**Attendu:**
```
minishell: unclosed quote `'`
```

---

## ✅ TEST 12: Commande complexe
```bash
minishell$ cat file.txt | grep "test" | wc -l > result.txt
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'cat'
SPACES     | ' '
WORD       | 'file.txt'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'grep'
SPACES     | ' '
WORD       | '"test"'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'wc'
SPACES     | ' '
WORD       | '-l'
SPACES     | ' '
TRUNC      | '>'
SPACES     | ' '
WORD       | 'result.txt'
==============
```

---

## ✅ TEST 13: Sans espaces
```bash
minishell$ cat<input.txt>output.txt
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'cat'
INPUT      | '<'
WORD       | 'input.txt'
TRUNC      | '>'
WORD       | 'output.txt'
==============
```

---

## ✅ TEST 14: Pipes multiples
```bash
minishell$ ls | cat | cat | cat
```
**Attendu:**
```
=== TOKENS ===
WORD       | 'ls'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'cat'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'cat'
SPACES     | ' '
PIPE       | '|'
SPACES     | ' '
WORD       | 'cat'
==============
```

---

## ✅ TEST 15: Caractères spéciaux dans quotes
```bash
minishell$ echo "cat | grep > test"
```
**Attendu:** Tout doit être dans un seul token WORD
```
=== TOKENS ===
WORD       | 'echo'
SPACES     | ' '
WORD       | '"cat | grep > test"'
==============
```

---

## ❌ TESTS D'ERREURS

### TEST 16: Unclosed quotes
```bash
minishell$ echo "hello
# Doit afficher: minishell: unclosed quote `"`
```

### TEST 17: Input NULL
```bash
# Dans le code, tester avec tokenize(NULL)
# Doit retourner NULL sans crash
```

---

## 🔍 Checklist de validation

- [ ] Commandes simples tokenisées
- [ ] Arguments séparés par SPACES
- [ ] Pipes détectés (PIPE)
- [ ] Redirections simples (<, >)
- [ ] Redirections doubles (<<, >>)
- [ ] Variables $USER, $?, etc.
- [ ] Guillemets simples conservés
- [ ] Guillemets doubles conservés
- [ ] Guillemets non fermés → erreur
- [ ] Pas de crash sur entrée vide/NULL
- [ ] Pas de memory leaks

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

Voici **LE TABLEAU OFFICIEL COMPLET** pour **TESTER la PHASE 4 (EXPANSION)** de ton minishell.
Il couvre **100%** des cas attendus dans cette phase (et seulement ceux-là).

Tu peux t’en servir comme **checklist de validation**.

---

# 🟦📘 **TABLEAU DE TESTS — PHASE 4 : EXPANSION (Minishell 42)**

| Catégorie                                | Commande                         | Résultat attendu (Bash / Minishell Phase 4) |                        |
| ---------------------------------------- | -------------------------------- | ------------------------------------------- | ---------------------- |
| **1. Expansion simple**                  | `echo $USER`                     | `djh`                                       |                        |
|                                          | `echo $HOME`                     | `/home/djh`                                 |                        |
|                                          | `echo $PATH`                     | *(valeur du PATH)*                          |                        |
|                                          | `echo $PWD`                      | *(répertoire courant)*                      |                        |
| **2. Variable inexistante**              | `echo $NOTHING`                  | *(argument vide)*                           |                        |
|                                          | `echo ABC$NOTHINGDEF`            | `ABCDEF`                                    |                        |
|                                          | `echo "$NOTHING"`                | `""`                                        |                        |
| **3. Variables collées**                 | `echo ABC$USERDEF`               | `ABC`                                       |                        |
|                                          | `echo $USER$HOME$PWD`            | `djh/home/djh/...`                          |                        |
|                                          | `echo "$USER"_test`              | `djh_test`                                  |                        |
|                                          | `echo A"$USER"B`                 | `AdjhB`                                     |                        |
| **4. Double quotes : expansion activée** | `echo "$USER"`                   | `djh`                                       |                        |
|                                          | `echo "Hello $USER"`             | `Hello djh`                                 |                        |
|                                          | `echo " $USER "`                 | `djh`                                       |                        |
|                                          | `echo "$USER$HOME"`              | `djh/home/djh`                              |                        |
| **5. Simple quotes : pas d’expansion**   | `echo '$USER'`                   | `$USER`                                     |                        |
|                                          | `echo 'hello $USER'`             | `hello $USER`                               |                        |
|                                          | `echo 'ABC$USERDEF'`             | `ABC$USERDEF`                               |                        |
|                                          | `echo '$HOME and $PWD'`          | `$HOME and $PWD`                            |                        |
| **6. Mélange quotes**                    | `echo "$USER'$HOME'"`            | `djh'/home/djh'`                            |                        |
|                                          | `echo "$USER"toto'$HOME'$PATH`   | `djhtoto$HOME/usr/...`                      |                        |
|                                          | `echo '$USER'"$HOME"'$PWD'`      | `$USER/home/djh$PWD`                        |                        |
| **7. `$?` code retour (PHASE 4)**        | `ls` + `echo $?`                 | `0`                                         |                        |
|                                          | `ls                              | `+`echo $?`                                 | `2` *(erreur syntaxe)* |
|                                          | `toto` + `echo $?`               | **Phase 4** = dernier g_exit_status         |                        |
| **8. `$$` : PID**                        | `echo $$`                        | PID du minishell                            |                        |
| **9. Expansion dans les redirections**   | `FILE=out.txt ; echo hi > $FILE` | crée *out.txt*                              |                        |
|                                          | `echo hi > "$USER".txt`          | crée *djh.txt*                              |                        |
|                                          | `cat < "$HOME"/file.txt`         | ouvre */home/djh/file.txt*                  |                        |
| **10. Heredoc (phase 4)**                | `cat << EOF`                     | delimiter = `EOF`, expand=1                 |                        |
|                                          | `cat << "EOF"`                   | delimiter = `EOF`, expand=0                 |                        |
| **11. Arguments vides**                  | `EMPTY="" ; echo "$EMPTY"`       | `""`                                        |                        |
|                                          | `echo $EMPTY`                    | argument vide (SUPPRESSION plus tard)       |                        |
|                                          | `echo "$EMPTY""$EMPTY"`          | `""`                                        |                        |
| **12. Séquences complexes**              | `echo $$$USER`                   | `PIDdjh` *(minishell)*                      |                        |
|                                          | `echo "$""USER"`                 | `$USER`                                     |                        |
|                                          | `echo '"$USER"'`                 | `"$USER"`                                   |                        |
| **13. Cas non supportés = littéral**     | `echo ${USER}`                   | `${USER}`                                   |                        |
|                                          | `echo $[1+1]`                    | `$[1+1]`                                    |                        |
|                                          | `echo $USER:home`                | `djh:home`                                  |                        |

---

# 🟩 Notes importantes (PHASE 4 uniquement)

### ✔ Tu dois gérer :

* `$VAR`
* `$?`
* `$$`
* quotes `"..."` et `'...'`
* assemblement des arguments
* delimiter du heredoc + flag expand

### ❌ Tu ne dois PAS gérer :

* execution
* PATH
* “command not found” = 127
* suppression automatique des arguments vides
* expansion du contenu du heredoc


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
