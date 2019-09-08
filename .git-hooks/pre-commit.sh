#!/bin/sh

# Executa o analisador estático antes de permitir o commit
# Se executar sem erros permite o commit.

for i in $(git diff --cached --name-only | grep -E "*.cpp")
do
    cppcheck $i --error-exitcode=1
    if [ $? -ne 0 ]; then
        echo -e "\e[31mCan't commit before errors are corrected\e[0m"
        exit 1 
    fi
done