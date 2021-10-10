#!/bin/bash

#Variavel que armazena a url dos dados abertos da C3SL
C3SL_URL=http://dadosabertos.c3sl.ufpr.br/curitiba/156
# Variavel que armazena o caminho para o meu diretorio de nobackup
NOBACKUP_DIR=/nobackup/bcc/$USER/156
# Variavel que armazena todas as strings das CSVs necessárias para a execução do codigo
USEFUL_URLS=`cat $NOBACKUP_DIR/index.html | grep -e href | cut -d'"' -f8 | grep -v -e Historico -e _201 | grep 2021-*`

# Função responsável por verificar se os diretorios/arquivos ja existem/foram baixados, caso não existam, ela faz dos downloads necessários
push_csvs() {
        if [ ! -d $NOBACKUP_DIR/urls ]; then
                mkdir $NOBACKUP_DIR/urls
        fi
        for url in $USEFUL_URLS; do
                if [ ! -f $NOBACKUP_DIR/urls/'utf8'$url ]; then
                        wget -nc -q -P $NOBACKUP_DIR/urls $C3SL_URL/$url
                fi
        done
}

# Função que pega todas as CSVs e transforma elas de data para UTF8, retirando os caracteres indesejados
clean_csv() {
        CSVS=`ls $NOBACKUP_DIR/urls`
        for csv in $CSVS; do
                if file $NOBACKUP_DIR/urls/$csv | grep data; then
                        sed -i 's/\x00/ /g' $NOBACKUP_DIR/urls/$csv
                        iconv -f "ISO8859-1" -t UTF8 $NOBACKUP_DIR/urls/$csv -o $NOBACKUP_DIR/urls/'utf8'$csv
                        rm $NOBACKUP_DIR/urls/$csv
                fi
        done
}

#Função que pega todos os arquivos na pasta, filtra pela coluna de assuntos e os envia agrupados por repetições para um arquivo subjects.txt
get_all_subjects() {
        CSVS=`ls $NOBACKUP_DIR/urls`
        for csv in $CSVS; do
                cut -d';' $NOBACKUP_DIR/urls/$csv -f6 | tail -n +3 >> passage.txt
        done
        cat passage.txt | sed -r '/^\s*$/d' | sort -f | uniq -c -i | sort -r -nr  > ASSUNTO.txt
        rm passage.txt
}

#Função que pega todos os arquivos na pasta, filtra pela coluna de subdivisões e os envia agrupados por repetições para um arquivo subdivs.txt
get_all_subdiv() {
        CSVS=`ls $NOBACKUP_DIR/urls`
        for csv in $CSVS; do
                cut -d';' $NOBACKUP_DIR/urls/$csv -f7 | tail -n +3 >> passage.txt
        done
        cat passage.txt | sed -r '/^\s*$/d' | sort -f | uniq -c -i | sort -r -nr  > SUBDIVISAO.txt
        rm passage.txt
}

#Main Script
push_csvs
clean_csv
get_all_subjects
get_all_subdiv