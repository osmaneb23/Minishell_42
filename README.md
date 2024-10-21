# Minishell

<<<<<<< HEAD
## Tâches à accomplir

### 1. Apprendre à utiliser readline
- [ ] Créer un programme simple utilisant readline()
- [ ] Tester et comprendre les fonctions associées (rl_clear_history, rl_on_new_line, etc.)
- [ ] Lire le man de readline pour bien comprendre son fonctionnement

### 2. Analyser la ligne de commande
- [ ] Implémenter la tokenisation (séparer la commande en "mots")
- [ ] Identifier le type de chaque token
- [ ] Gérer les guillemets et les caractères d'échappement

### 3. Comprendre et implémenter les concepts de base
- [ ] Étudier les descripteurs de fichiers (fd)
- [ ] Comprendre STDIN, STDOUT et STDERR
- [ ] Apprendre à utiliser pipe(), dup2() et fork()

### 4. Développer les fonctionnalités du shell
- [ ] Implémenter l'exécution des commandes simples
- [ ] Gérer les variables d'environnement
- [ ] Implémenter les redirections (>, <, >>)
- [ ] Faire les pipes (|)
- [ ] Gérer les built-ins (cd, echo, pwd, export, unset, env, exit)

### 5. Gestion des erreurs et cas particuliers
- [ ] Implémenter la gestion des signaux (Ctrl+C, Ctrl+D, Ctrl+\)
- [ ] Gérer les cas d'erreur (commandes introuvables, permissions, etc.)

### 6. Tests et débogage
- [ ] Créer des tests unitaires pour chaque fonctionnalité
- [ ] Utiliser les 800 tests fournis pour vérifier le comportement
- [ ] Déboguer en comparant systématiquement avec bash --posix

## Rappels importants
- Toujours se référer au manuel GNU Bash
- Lancer bash avec l'option --posix pour les tests
- Comparer systématiquement le comportement de notre shell avec bash

## Ressources utiles

0. **Man Bash** : [GNU Manual for Bash](https://www.gnu.org/software/bash/manual/bash.html)

1. **Guide complet Minishell** : [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell)

2. **Tests Minishell** : [Google Sheets - Tests Minishell](https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0)

3. **Conseils pour Minishell** : [Medium - Conseils pour recommencer Minishell](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)

4. **Apprendre Git** : [Learn Git Branching](https://learngitbranching.js.org/)

5. **Checklist Minishell** : [Google Sheets - Checklist Minishell](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0)
=======
## 1. Utilisation de Readline
### Objectifs :
- [ ] **Créer un programme simple avec `readline()`** :
  - Lire une ligne d'entrée utilisateur.
  - Afficher le résultat.
  - Utiliser `rl_clear_history`, `rl_on_new_line`, etc. pour comprendre le comportement.
  
- [ ] **Comprendre les fonctions associées** :
  - Lire le man de `readline`.
  - Tester différents cas d'utilisation pour voir comment le buffer se comporte.
  - Voir comment fonctionne la gestion de l'historique.

### Ressources :
- `man readline`
- Documentation GNU : https://tiswww.case.edu/php/chet/readline/rltop.html

---

## 2. Analyse de la ligne de commande
### Objectifs :
- [ ] **Tokenisation** :
  - Séparer une ligne de commande en "mots".
  - Gérer les cas spécifiques (ex : espaces multiples, tabulations).
  
- [ ] **Identifier chaque token** :
  - Ex : commandes, arguments, opérateurs (`|`, `>`, `>>`, etc.).
  
- [ ] **Gestion des guillemets et caractères d'échappement** :
  - Support des guillemets simples (`'`) et doubles (`"`).
  - Prendre en compte les caractères d'échappement (`\`).

### Ressources :
- `man bash` (section sur les quotes et les expansions)
- Test cases à implémenter pour cette section

---

## 3. Concepts de base : Fichiers et Processus
### Objectifs :
- [ ] **Comprendre les descripteurs de fichiers (fd)** :
  - Étudier comment manipuler STDIN, STDOUT, STDERR via les fds.
  
- [ ] **Utilisation de `pipe()`, `dup2()` et `fork()`** :
  - Tester des programmes simples pour chaque appel système.
  - Essayer de faire communiquer deux processus via un `pipe()`.
  
- [ ] **Étudier le fonctionnement des redirections et des pipes** :
  - Comment rediriger l'entrée/sortie des processus.
  - Cas pratiques avec `dup2()` pour rediriger vers un fichier ou un pipe.

### Ressources :
- `man pipe`, `man dup2`, `man fork`
- Tutoriels système Unix (liens à trouver pour des exemples)

---

## 4. Développement des fonctionnalités du Shell
### Objectifs :
- [ ] **Exécution de commandes simples** :
  - Appels systèmes pour exécuter une commande (`execve`).
  
- [ ] **Gestion des variables d'environnement** :
  - Implémenter `getenv()` et `setenv()` pour lire et modifier l'environnement.
  
- [ ] **Redirections (>, <, >>)** :
  - Gérer les différents types de redirections (sortie, entrée, append).
  
- [ ] **Pipes (|)** :
  - Implémenter la gestion des pipelines entre plusieurs commandes.
  
- [ ] **Built-ins** :
  - Implémenter les commandes internes (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`).
  - Reproduire le comportement de `bash --posix`.

### Ressources :
- `man execve`, `man getenv`, `man setenv`
- Exemples pratiques pour les built-ins

---

## 5. Gestion des erreurs et cas particuliers
### Objectifs :
- [ ] **Gestion des signaux** :
  - Implémenter la gestion des signaux : `Ctrl+C`, `Ctrl+D`, `Ctrl+\`.
  
- [ ] **Gestion des erreurs** :
  - Messages d'erreurs pour les commandes introuvables, permissions refusées, etc.
  - Vérification des retours des appels systèmes.

### Ressources :
- `man signal`
- Liste des erreurs système (`errno`)

---

## 6. Tests et débogage
### Objectifs :
- [ ] **Tests unitaires** :
  - Créer des tests unitaires pour chaque fonctionnalité : exécution de commandes, redirections, pipes, etc.
  
- [ ] **Utiliser les 800 tests fournis** :
  - Vérifier la compatibilité et les comportements attendus avec les tests fournis.
  
- [ ] **Déboguer et comparer avec `bash --posix`** :
  - Tester chaque fonctionnalité avec Bash pour identifier les écarts de comportement.

### Ressources :
- 800 tests fournis dans les documents du projet
- Comparaison avec Bash via `--posix`

---

## Notes et Rappels Généraux
- **Se référer au manuel GNU Bash** pour toute ambiguïté.
- **Toujours tester avec `bash --posix`** pour aligner le comportement.
- **Utiliser des tests systématiques** à chaque étape du développement (tokenisation, pipes, etc.).

### Ressources :
- **[GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)**
- **[GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)**
- **[42 Minishell Docs](https://harm-smits.github.io/42docs/projects/minishell)**
- **[Tests Minishell](https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0)**
- **[Checklist Minishell](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0)**
- **[Conseils pour Minishell](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)**
- **[Apprendre Git](https://learngitbranching.js.org/)**
- **[Petit guide d'un Github](https://github.com/Hqndler/42-minishell)**
>>>>>>> origin/Osmane
