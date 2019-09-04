#!/bin/sh

# Executa o analisador estático antes de permitir o commit
# Se executar sem erros permite o commit.

for i in $(git diff --cached --name-only | grep -E "*.c")
do
    echo "$i"
    printf "%s\n" "$(cppcheck $i | awk '/error/ {print $1}')"
done