#!/bin/bash

#Variavel que armazena a url dos dados abertos da C3SL
C3SL_URL=http://dadosabertos.c3sl.ufpr.br/curitiba/156
# Variavel que armazena o caminho para o meu diretorio de nobackup
NOBACKUP_DIR=/nobackup/bcc/pmla20/156
# Variavel que armazena todas as strings das CSVs necessárias para a execução do codigo
USEFUL_URLS=`cat $NOBACKUP_DIR/index.html | grep -e href | cut -d'"' -f8 | grep -v Historico | grep -v _201 | grep -e 2021-*`

# Função responsável por verificar se os diretorios/arquivos ja existem/foram baixados, caso não existam, ela faz dos downloads necessários
push_csvs() {
        if [ ! -d $NOBACKUP_DIR/urls ]
        then
                mkdir $NOBACKUP_DIR/urls
        fi
        for url in $USEFUL_URLS
        do
                if [ ! -f $NOBACKUP_DIR/urls/$url ]
                then
                        wget -P $NOBACKUP_DIR/urls $C3SL_URL/$url
                fi
        done
}

#Main Script
push_csvs