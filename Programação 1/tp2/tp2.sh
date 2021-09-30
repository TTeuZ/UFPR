# Pegar todos os nomes  do diretorio /home/bcc

#Resultado: um arquivo chamado nome_de_informats.txt contendo:
#       - Lista ordenada e sem repetições de todos os nomes;
#       - Lista com os 10 nomes que mais ocorrem, juntamente com o nùmero de ocorrência, ordenando do que mais ocorre para o que menos ocorre.
#O formato de saida deve mostrar um prenome por linha para a primeira parte do exercıcio e em seguida as linhas devem ter a quantidade de ocorrencias seguida de um nome.

#! /usr/bin/env bash

USERS_LIST=`ls /home/bcc`

# Primeira parte, gera uma lista ordenada com todos os nomes de /home/bcc sem repetição
finger -s $USERS_LIST | cut -b12-33 | cut -d" " -f1 | tail -n +2 | sort | uniq > nomes_de_informatas.txt

# Segunda parte, geral a lista inferior com os 10 nomes mais utilizados em ordem decrescente.
finger -s $USERS_LIST | cut -b12-33 | cut -d" " -f1 | tail -n +2 | sort | uniq -c | sort -r -n | head -n10 | xargs --max-args=2  >> nomes_de_informatas.txt