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

# Função que pega todas as CSVs e transforma elas de data para UTF8, retirando os caracteres indesejados
clean_csv() {
        CSVS=`ls /nobackup/bcc/pmla20/156/urls`
        for csv in $CSVS
        do
                iconv -f ISO8859-1 -t UTF8 $NOBACKUP_DIR/urls/$csv -o $NOBACKUP_DIR/urls/$csv
                dos2unix $NOBACKUP_DIR/urls/$csv
                sed -i 's/\x00/ /g' $NOBACKUP_DIR/urls/$csv
        done
}

#Função que pega todos os arquivos na pasta, filtra pela coluna de assuntos e os envia agrupados por repetições para um arquivo subjects.txt
get_all_subjects() {
        CSVS=`ls /nobackup/bcc/pmla20/156/urls`
        for csv in $CSVS
        do
                cut -d';' $NOBACKUP_DIR/urls/$csv -f6 | tail -n +3 >> passage.txt
        done
        cat passage.txt | sed -r '/^\s*$/d' | uniq -c > subjects.txt
        rm passage.txt
}

#Função que pega todos os arquivos na pasta, filtra pela coluna de subdivisões e os envia agrupados por repetições para um arquivo subdivs.txt
get_all_subdiv() {
        CSVS=`ls /nobackup/bcc/pmla20/156/urls`
        for csv in $CSVS
        do
                cut -d';' $NOBACKUP_DIR/urls/$csv -f7 | tail -n +3 >> passage.txt
        done
        cat passage.txt | sed -r '/^\s*$/d' | uniq -c > subdivs.txt
        rm passage.txt
}

#Main Script
push_csvs
clean_csv
get_all_subjects
get_all_subdiv

#Tentativa sem usar arquivo de passagem
# VALUES="$VALUES $(cut -d';' $NOBACKUP_DIR/urls/$csv -f6 | tail -n +3)"
# cat $VALUES | uniq -c > teste.txt