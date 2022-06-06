#ifndef HASH_H
#define HASH_H

#define M 11
/*
* Inicializa as valores da tabela, prennchendo os slots com o valor -1
*/
void inicialize_hash_table (int hash[][M]);

/*
* Faz uma busca do valor indicado em 'key' dentro da hash
* Caso encontre, retorna a posição
* Caso não encontre, retorna -1
*/
int hash_search (int key, int t1[][M], int t2[][M]);

/*
* Faz a inserção do valor indicado em 'key' na hash.
* Segue as definições indicadas, nçao havendo re-hashing ou sobreposição de valores.
*/
void hash_insert (int key, int t1[][M], int t2[][M]);

/*
* Faz a exlusão do valor indicado em 'key' na hash.
* Caso o valor excluido esteja na T1, marcamos o slot com o valor -2, que indica 'exluido'
* Assim, evitando problemas na busca.
*/
void hash_delete (int key, int t1[][M], int t2[][M]);

/*
* Printa o resultado da hash
* Funciona da seguinte maneira:
* - Passa pela hash T1, e ao encontrar um valor diferente de -1 || -2 adiciona de maneira ordenada sua chave no array key_array
* - Da mesma maneira, seguindo a ordenação do key_array, adiciona os valores da coluna e 'numero da hash' nos print_arrays
*   column_array e hash_array respectivamente
* - Realiza o mesmo processo para a hash t2
* Desta maneira, conseguimos obter as informações ordenadas de forma correta para o print da hash como pedido.
*/
void hash_print (int t1[][M], int t2[][M]);

#endif