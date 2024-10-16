Nome: Paulo Mateus Luza Alves
GRR: GRR20203945

# Como reproduzir

## Setup externo
O arquivo 'docker-compose.yml' foi modificado para adicionar o ip 10.9.0.6 (trusted-server) no arquivo .rhosts da maquina 10.9.0.5 (x-terminal). Portando, caso o projeto seja executado com este docker-compose nenhuma ação externa é necessária.

Porem, caso outro docker-compose seja utiliziado, para o ataque ser realizado é necessário adicionar o arquivo .rhosts contendo o IP 10.9.0.6 (trusted-server) na raiz da máquina 10.9.0.5 (x-terminal).

Para isso, fora do ambiente docker, e dentro da pasta do projeto, execute o comando

sudo docker exec -it x-terminal-10.9.0.5 sh -c 'echo "10.9.0.6" >> ~/.rhosts'

Ou, caso prefira, acesse a máquina x-terminal manualmente e adicione o arquivo dentro da pasta /root/ contendo o IP 10.9.0.6 (trusted-server).

## Executando o ataque
Para executar o ataque, acesse a máquina 10.9.0.1 (seed-attacker) com o comando

sudo docker exec -it seed-attacker bash

Dentro da máquina atacante acesse o diretório volumes e execute o comando 

python3 attack.py. 

Este script irá realizar todo o processo de abertura do backdoor no x-terminal. Após a finalização dele, basta acessar a máquina 10.9.0.5 (x-terminal) a partir da máquina 100.9.0.1 (seed-attacker) com o seguinte comando.

rsh 10.9.0.5

Caso queira verificar o funcionamento completo basta testar a conexão antes e depois de rodar o script.

# Detalhando o script
O único script utilizado é o attack.py. Nele você encontrará comentários e prints das fases da execução. Porém, fazendo um breve resumo temos as seguintes etapas

1. Preparação do ambiente.
Primeiro, o script desativa as configurações de ip_foward e send_redirects da máquina atacante, para que o arp spoofing possa funcionar corretamente.

2. Execução do spoofing
Nesta etapa, é criado uma thread separada que fica constantemente mandando pacotes de spoofing para o 10.9.0.5 (x-terminal). O objetivo é fazer com que todos os pacotes que seriam enviados para o 10.9.0.6 (trusted-server) sejam enviados para nós.

3. Envio dos pacotes
Esta é a etapa final, onde o script realiza a conexão RSH completa personificando o 10.9.0.6 (trusted-server) e abrindo o backdoor no 10.9.0.5 (x-terminal).

A sequência de conexão e envio de pacotes é a seguinte:
- 3-way-handshake entre as portas 1023 (seed-attacker) e 514 (x-terminal)
- Estabelecimento de conexão RSH
- 3-way-handshake entre as portas 1022 (seed-attacker) e 1023/1022 (x-terminal). Conexão na porta STDERR
- Fechamento da conexão RSH
- Fechamento da conexão na porta STDERR