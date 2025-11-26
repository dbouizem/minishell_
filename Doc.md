
# **Commande : `env -i ./minishell`**

## `env -i` : Lancer un programme avec zéro variable d’environnement

Normalement, ton shell dispose de variables telles que :

```
PATH
PWD
HOME
USER
SHLVL
...
```

Mais l’option `-i` de `env` signifie **ignore environment**, ce qui revient à **vider complètement l’environnement** avant de lancer le programme.

Ainsi, la commande suivante :

```bash
env -i ./minishell
```

permet de lancer **ton minishell sans aucune variable d’environnement**, comme si le système était vierge.

---

## Pourquoi ce test est-il crucial ?

Parce que dans le cadre du projet **Minishell 42**, ton shell doit être capable de **fonctionner même si l’environnement est totalement absent**.

Or, sans environnement, plusieurs éléments essentiels disparaissent :

- `PWD` : impossible de connaître le répertoire courant
- `SHLVL` : le niveau du shell est perdu
- `_` : variable standard absente

C’est pourquoi ton shell doit être capable de **reconstruire un environnement minimal** pour fonctionner correctement.

---

## Ce que ton minishell doit recréer automatiquement

Quand il détecte un environnement vide, il doit initialiser les variables suivantes :

| Variable | Valeur attendue                          |
|----------|------------------------------------------|
| `PWD`    | Répertoire courant via `getcwd()`        |
| `SHLVL`  | 1                                        |
| `_`      | Chemin du programme (`./minishell`)      |

Optionnellement, il peut afficher un avertissement :

```
minishell: warning: empty environment, creating minimal environment
```

---

## Exemple concret

### 🔴 Sans environnement (via `env -i`)

```bash
env -i ./minishell
```

Ton minishell reçoit :

```
(no environment)
```

### 🟢 Il doit alors créer :

```
PWD=/home/user
SHLVL=1
_=/usr/bin/env  # ou ./minishell selon ton implémentation
```

Et ensuite afficher normalement :

```
minishell$
```

---

## Résumé rapide

| Commande             | Action effectuée                                      |
|----------------------|--------------------------------------------------------|
| `env -i ./minishell` | Lance ton minishell sans variables d’environnement    |
| Minishell doit       | Recréer `PWD`, `SHLVL`, `_` automatiquement           |
| Objectif             | Respecter le comportement d’un shell standard         |

---
========================================================================================
# `stdin is not a terminal` – Qu’est-ce que c’est ?

C’est un message d’erreur **optionnel** qu’un programme peut choisir d’afficher si `stdin` ne provient **pas d’un terminal** (par exemple, d’un pipe, d’un fichier ou d’une redirection).

 Ce message **n’est pas requis** par le sujet Minishell 42.

---

## Quand `stdin` est un terminal

Lorsque tu lances ton shell normalement :

```bash
./minishell
```

Alors `stdin` provient de ton clavier, donc :

```c
isatty(STDIN_FILENO) == 1
```

---

## Quand `stdin` n’est pas un terminal

Cas typiques :

```bash
echo "ls" | ./minishell
./minishell < script.sh
./minishell 0<&-
```

Dans ces situations :

```c
isatty(STDIN_FILENO) == 0
```

Mais cela **ne signifie pas qu’il y a une erreur**. C’est un comportement **attendu** pour un shell.

---

## Ce message n’apparaît que si tu l’implémentes

Sous Linux, ce message **n’apparaît jamais automatiquement**. Il n’existe que si tu l’ajoutes toi-même dans ton code :

```c
if (!isatty(STDIN_FILENO)) {
    fprintf(stderr, "stdin is not a terminal\n");
    exit(1);
}
```

👉 Ton minishell **ne doit pas contenir ce code**.

---

## Doit-on afficher ce message dans Minishell ?

### ❌ **Jamais.**

Si tu l’affiches, tu enfreins le sujet, car cela empêcherait ton shell de fonctionner dans des pipes ou scripts.

---

## Résumé visuel

| Situation                  | Source de `stdin` | Action de minishell         | Message affiché ? |
|----------------------------|-------------------|------------------------------|-------------------|
| `./minishell`              | Terminal          | Prompt + interaction         | ❌ Non            |
| `echo "ls" | ./minishell` | Pipe              | Lecture + exécution          | ❌ Non            |
| `./minishell < script.sh`  | Fichier           | Lecture + exécution          | ❌ Non            |
| `./minishell 0<&-`         | Aucun             | Quitter directement          | ❌ Non            |

---

## Conclusion

**“stdin is not a terminal” n’est pas requis.**
C’est un message que **toi seul** peux choisir d’afficher.
Dans le cadre du projet Minishell 42, **tu ne dois pas l’afficher**.

---
========================================================================================
# Interaction interactive vs non-interactive

| Mode         | Source de l’entrée | `isatty` | Exemple                     |
|--------------|--------------------|----------|-----------------------------|
| Interactif   | Clavier            | 1        | `./minishell`               |
| Non interactif | Pipe, fichier    | 0        | `echo "ls" | ./minishell` |

---

## Pourquoi cette distinction est importante ?

### En mode interactif :
- Afficher un prompt
- Utiliser `readline`
- Gérer `Ctrl+C` pour afficher une nouvelle ligne

### En mode non interactif :
- Ne **pas** afficher de prompt
- Ne **pas** utiliser `readline`
- Lire les lignes et les exécuter directement

---
========================================================================================
## À propos de `readline`

`readline` est une bibliothèque puissante qui permet :

- L’édition de ligne (touches fléchées, suppression, etc.)
- L’historique des commandes
- La gestion de `Ctrl+A`, `Ctrl+E`, `Ctrl+R`, etc.
- Une expérience utilisateur proche d’un vrai shell

Sans `readline`, ton shell serait limité à une lecture basique via `fgets()` ou `getline()`.

---
========================================================================================
# Logique du Lexer

## Flux global en trois étapes

```
┌─────────────────────────────────────────────┐
│ ÉTAPE 1 : Vérification des guillemets      │
│ has_quote_error()                           │
│ → Si guillemet non fermé → return NULL     │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ ÉTAPE 2 : Parcourir la chaîne caractère    │
│           par caractère                     │
│ while (input[i])                            │
│   process_char()                            │
└──────────────────┬──────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────┐
│ ÉTAPE 3 : Pour chaque caractère,           │
│           créer le bon token                │
│ - Si espace     → handle_spaces()          │
│ - Si |, <, >    → handle_pipe_or_redir()   │
│ - Si autre      → handle_word()            │
└─────────────────────────────────────────────┘
```

---

## Étape 1 : Vérification des guillemets

```c
if (has_quote_error(input))
    return (NULL);
```

Permet d’éviter de tokenizer une commande mal formée dès le départ.

**Exemple** :
```bash
echo "hello
```

→ Guillemet non fermé → erreur immédiate.

---

## Étape 2 : Parcours caractère par caractère

```c
i = 0;
while (input[i])
    process_char(input, &i, &head, &current);
```

Chaque caractère est analysé pour déterminer sa nature.

---

## Étape 3 : Création des tokens

```c
static void process_char(char *input, int *i, t_token **head, t_token **current)
{
    if (is_whitespace(input[*i]))
        handle_spaces(input, i, head, current);
    else if (is_special_char(input[*i]))
        handle_pipe_or_redir(input, i, head, current);
    else
        handle_word(input, i, head, current);
}
```

---

## Exemple : `"echo hello"`

### Phase 1 : Vérification des guillemets

✅ Aucune erreur → on continue.

### Phase 2 : Tokenisation

1. `'e'` → `handle_word()` → extrait `"echo"`
2. `' '` → `handle_spaces()` → token `" "`
3. `'h'` → `handle_word()` → extrait `"hello"`

Résultat final :

```
[WORD:"echo"] → [SPACES:" "] → [WORD:"hello"] → NULL
```

---

## Résumé du découpage

| Fonction                 | Rôle                              |
|--------------------------|------------------------------------|
| `handle_spaces()`        | Traite les espaces/tabulations     |
| `handle_pipe_or_redir()` | Traite `|`, `<`, `>`              |
| `handle_word()`          | Traite les mots, quotes, variables |

---
========================================================================================
# `extract_word_without_quotes()`

## Pourquoi cette fonction ?

Un mot dans un shell peut être composé de plusieurs parties :

```bash
echo hello'world'"test"123
     └──────────────────┘
     UN SEUL MOT avec 4 parties :
     1. hello      (normal)
     2. 'world'    (simple quote)
     3. "test"     (double quote)
     4. 123        (normal)
```

---

## Logique interne

La fonction :

1. Parcourt le mot partie par partie
2. Extrait chaque segment
3. Concatène le tout
4. S’arrête à un espace ou caractère spécial

---

## Exemple complet : `echo hello'world'"test"`

1. `echo` → mot simple
2. `hello'world'"test"` → concaténation de 3 parties :
   - `hello` (normal)
   - `'world'` (quoted)
   - `"test"` (quoted)

Résultat final : `hello'world'"test"` → UN SEUL token.

---

## Schéma mental

```
extract_word_without_quotes()
    ↓
┌───────────────────────────────┐
│ Boucle sur chaque partie      │
│ du mot                        │
└──────────┬────────────────────┘
           │
           ▼
   process_word_part()
           │
     ┌─────┴─────┐
     │           │
     ▼           ▼
Quote ?      Normal ?
     │           │
     ▼           ▼
handle_quoted  handle_normal
    _part()       _part()
     │           │
     └─────┬─────┘
           │
           ▼
    Concatène à result
           │
           ▼
    Continue ou STOP
```

---

## Résumé final

| Objectif | Description |
|----------|-------------|
| Gérer les quotes | Un mot peut contenir `'...'` et `"..."` |
| Concaténer les parties | `hello'world'"test"` = UN SEUL mot |
| Garder les quotes | Pour l’expansion ultérieure |
| Arrêt intelligent | Sur espace ou caractère spécial |

---

