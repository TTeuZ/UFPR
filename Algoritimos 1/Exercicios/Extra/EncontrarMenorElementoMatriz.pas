program EncontrarMenorElementoMatriz;
type matriz = array[1..50, 1..50] of integer;

function acha_menor_matriz (var m: matriz; linha, coluna: integer);
var i, j: integer;
    menor: integer;
begin
  menor := m[1,1];
  for i := 1 to linha do
    for j := 1 to coluna do
      if m[linha, coluna] < menor then
        menor := m[linha, coluna]; 
end;

begin
end.