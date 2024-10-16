# Minishell

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

0. **Man Bash** : [git@github.com:osmaneb23/Minishell_42.git](https://www.gnu.org/software/bash/manual/bash.html)

1. **Guide complet Minishell** : [42 Docs - Minishell](https://harm-smits.github.io/42docs/projects/minishell)

2. **Tests Minishell** : [Google Sheets - Tests Minishell](https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0)

3. **Conseils pour Minishell** : [Medium - Conseils pour recommencer Minishell](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)

4. **Apprendre Git** : [Learn Git Branching](https://learngitbranching.js.org/)

5. **Checklist Minishell** : [Google Sheets - Checklist Minishell](https://docs.google.com/spreadsheets/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/edit?gid=0#gid=0)
