program Exercicio02;

var a, b, equal, i, multiplicador: longint;

begin
  read(a, b);
  i := 10; multiplicador := 1; equal := 0;

  while (equal <> b) do begin // vai realizando mod até igualar os ultimos digitos de a em b
    equal := b mod i;
    i := i * 10;
    multiplicador := multiplicador * 10; // vai adicionando o multiplicador (10, 100, 1000...)
  end;

  //se voce fizer o mod do maior numero por 10^numeroDecasasDeB
  // voce encontra os ultimos digitos de A com o mesmo tamanho de b
  
  a := a mod multiplicador;

  if (a = b) then // verifica se o valor encontrado é igual a b
    writeln('ENCAIXA')
  else
    writeln('NAO ENCAIXA')
end.