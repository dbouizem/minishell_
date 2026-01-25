# 🐚 **Minishell**

Un shell Unix minimaliste créé dans le cadre du projet **42 School**, implémentant les fonctionnalités essentielles d'un shell interactif.

---

## **À propos**

**Minishell** est une reproduction simplifiée d'un shell Unix, développé dans le cadre du cursus 42. Il permet d'approfondir la compréhension des **processus**, **signaux**, **pipes**, **redirections** et de la gestion d'environnement.

### Objectifs pédagogiques
- Comprendre le fonctionnement interne d'un shell
- Maîtriser les appels système (`fork`, `execve`, `wait`, `pipe`, `dup2`)
- Gérer les signaux (`SIGINT`, `SIGQUIT`)
- Parser et exécuter des commandes complexes
- Implémenter un environnement minimal

---

## **Fonctionnalités**

### **Partie obligatoire**

| Fonctionnalité | Description |
|----------------|-------------|
| **Prompt interactif** | Affichage d'un invite de commande personnalisé |
| **Historique** | Navigation avec `↑` / `↓` via `readline` |
| **Exécution de commandes** | Recherche dans `PATH`, chemins absolus/relatifs |
| **Pipes** | Support des pipelines (`cmd1 | cmd2 | cmd3`) |
| **Redirections** | `<`, `>`, `>>`, `<<` (heredoc) |
| **Variables d'environnement** | Expansion de `$VAR`, `$?`, `$$` |
| **Signaux** | `Ctrl+C`, `Ctrl+D`, `Ctrl+\` conformes à Bash |
| **Builtins** | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |

### **Partie bonus**

| Fonctionnalité | Description |
|----------------|-------------|
| **Opérateurs logiques** | `&&` (ET) et `||` (OU) |
| **Parenthèses** | `()` pour grouper les commandes (sans subshell) |
| **Wildcards** | Expansion de `*` (répertoire courant uniquement) |

---

## Compilation

```bash
git clone https://github.com/votre-username/minishell.git
cd minishell

# Partie obligatoire
make

# Avec les bonus
make bonus

# Nettoyage
make clean      # Supprime les fichiers objets
make fclean     # Supprime les objets et l'exécutable
make re         # Recompile entièrement
```

---

## **Utilisation**

### Lancement

```bash
# Mode interactif
./minishell

# Environnement vide
env -i ./minishell

# Mode non-interactif (script)
echo "ls -la" | ./minishell
```

### Exemples de commandes

```bash
# Commandes simples
minishell$ ls -la
minishell$ echo "Hello World"

# Pipes et redirections
minishell$ cat file.txt | grep "test" > result.txt

# Heredoc
minishell$ cat << EOF
> première ligne
> deuxième ligne
> EOF

# Variables et expansion
minishell$ export NAME="Alice"
minishell$ echo "Bonjour $NAME"

# Opérateurs logiques (bonus)
minishell$ ls && echo "Success"
minishell$ ls /invalid || echo "Failed"

# Wildcards (bonus)
minishell$ echo *.c
minishell$ ls *.txt
```
---

## **Architecture du projet**

### Flux d'exécution

```
1. Lecture de la ligne (readline)
2. Tokenisation (Lexer)
3. Parsing (Parser → AST)
4. Expansion (variables, quotes, wildcards*)
5. Exécution (builtins / fork + execve)
6. Gestion des signaux et nettoyage
```

### Structure des fichiers
```
minishell/
│
├── includes/                     # Fichiers d'en-tête
│   ├── minishell.h              # En-tête principal
│   ├── minishell_bonus.h        # En-tête pour les bonus
│   ├── builtin.h
│   ├── executor.h
│   ├── expander.h
│   ├── parser.h
│   ├── token.h
│   ├── env.h
│   └── colors.h
│
├── src/                         # Code source obligatoire
│   ├── main.c
│   ├── core/                    # Fonctions centrales
│   ├── lexer/                   # Analyse lexicale
│   ├── parser/                  # Analyse syntaxique
│   ├── expander/                # Expansion (variables, quotes)
│   ├── executor/                # Exécution des commandes
│   ├── builtin/                 # Commandes intégrées
│   └── env/                     # Gestion environnement
│
├── src_bonus/                   # Code source des bonus
│   ├── core/
│   ├── executor/
│   ├── expander/
│   ├── lexer/
│   └── parser/
│
├── libft/                       # Librairie personnelle
├── .vscode/                     # Configuration IDE (optionnel)
├── Makefile                     # Fichier de compilation principal
├── README.md                    # Documentation principale
└── .gitignore                   # Fichiers ignorés par Git
```

---

## **Tests**

### Tests manuels

```bash
# Vérification des fonctionnalités de base
./minishell
minishell$ echo $?
minishell$ exit

# Test avec Valgrind
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Tests comparatifs avec Bash
bash -c "commande"  # À comparer avec minishell
```

### Checklist de validation

#### ✅ Compilation
- [ ] `make` sans warnings
- [ ] Norminette OK
- [ ] Pas de relink inutile

#### ✅ Fonctionnalités
- [ ] Prompt et historique
- [ ] Pipes et redirections
- [ ] Expansion de variables
- [ ] Builtins
- [ ] Signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- [ ] Heredoc

#### ✅ Robustesse
- [ ] Pas de segfault
- [ ] Gestion d'erreurs
- [ ] Pas de memory leaks (hors readline)
- [ ] Environnement vide (`env -i`)

---

## 👥 **Auteurs**

<div align="center">

[![GitHub](https://img.shields.io/badge/GitHub-fadzejli-181717?style=for-the-badge&logo=github)](https://github.com/Fazejli)
[![GitHub](https://img.shields.io/badge/GitHub-dbouizem-181717?style=for-the-badge&logo=github)](https://github.com/dbouizem)

</div>

