# Pipex

## Introduction

The Pipex project provides an opportunity to explore a UNIX mechanism by implementing it in your program. The goal is to handle pipes and execute shell commands using the given set of arguments.

## Mandatory Part

### Pipex Program

- Program Name: pipex
- Files: Makefile, _.h, _.c
- Makefile: NAME, all, clean, fclean, re
- Arguments: file1 cmd1 cmd2 file2
- External Functions: open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
- Libft Authorized: Yes

### Examples

```sh
$> ./pipex infile "ls -l" "wc -l" outfile
# Should behave like: < infile ls -l | wc -l > outfile

$> ./pipex infile "grep a1" "wc -w" outfile
# Should behave like: < infile grep a1 | wc -w > outfile
```

## Bonus Part

### Additional Features

- Handle multiple pipes:

```sh
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
# Should behave like: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

Support « and » when the first parameter is "here_doc":

```sh
$> ./pipex here_doc LIMITER cmd cmd1 file
# Should behave like: cmd << LIMITER | cmd1 >> file

```
