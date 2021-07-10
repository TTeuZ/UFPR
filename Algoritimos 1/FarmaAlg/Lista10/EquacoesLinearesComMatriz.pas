program EquacoesLinearesComMatriz;
type matriz = array[1..100, 1..100] of real; 
     vetor = array[1..100] of real;
var coeficientesEquacao: matriz;
    respostasInformadas, ladoEsquerdoEquacao: vetor;
    linha, coluna: integer;

procedure ler_vetor (var vet: vetor; linha: integer);
var i: integer;
begin
  for i := 1 to linha do
    read(vet[i]);
end;

procedure ler_coeficientes (var m: matriz; linha, coluna: integer);
var i,j: integer;
begin
  for i := 1 to linha do
    for j := 1 to coluna do
      read(m[i,j])
end;

function verifica_linha(var m: matriz; var ladoEsquerdo, respostasInformadas: vetor; linha, colunas: integer): Boolean;
var vLadoDireito, vLadoEsquerdo: real;
    i: integer;
begin
  vLadoDireito := 0;
  for i := 1 to colunas do begin
    vLadoDireito := vLadoDireito + (coeficientesEquacao[linha, i] * respostasInformadas[i]);
  end;
  vLadoEsquerdo := ladoEsquerdo[linha];
  if vLadoDireito = vLadoEsquerdo then
    verifica_linha := true
  else 
    verifica_linha := false;
end;

function eh_resultado(var m: matriz; var ladoEsquerdo, respostasInformadas: vetor; linha, coluna: integer): Boolean;
var i: integer;
    resposta: Boolean;
begin
  i := 1; resposta := true;
  while (i <= linha) and resposta do begin
    resposta := verifica_linha(m, ladoEsquerdo, respostasInformadas, i, coluna);
    i := i + 1;
  end;
  eh_resultado := resposta;
end;

begin
  read(linha, coluna);
  ler_vetor(respostasInformadas, linha);
  ler_coeficientes(coeficientesEquacao, linha, coluna);
  ler_vetor(ladoEsquerdoEquacao, linha);

  if eh_resultado(coeficientesEquacao, ladoEsquerdoEquacao, respostasInformadas, linha, coluna) then
    writeln('sim')
  else 
    writeln('nao');
end.