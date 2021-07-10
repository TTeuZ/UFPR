program PreencherMatriz;
type matriz = array[1..50, 1..10] of real; // maneria de instanciar uma matriz, é um array de arrays
var i, j: integer;
    w: matriz;
begin
  for i := 0 to 50 do
    for j := 1 to 10 do
      read(w[i,j])
end.

procedure ler_matriz (var w: matriz; var n,m: integer);
var i,j: integer;
begin
  read(n); // numero entre 1 e 50 (maximo de linhas da matriz)
  read(m); // numero entre 1 e 10 (maximo de colunas da matriz)
  for i := 1 to n do
    for j := 1 to m do
      read(w[i,j])
end;

procedure imprimir_matriz (var w: matriz; n,m: integer);
var i,j: integer;
begin
  for i := 1 to n do begin
    for j := 1 to m do
      write(w[i,j, ' ']);
    writeln;
  end;
end;

procedure imprimir_transposta (var w: matriz; n,m: integer);
var i,j: integer;
begin
  for i := 1 to m do begin // inverteu n com o m aqui, pois estou travando a coluna, fazendo printar todos os numeros da coluna, gerando assim a transposta
    for j := 1 to n do 
      write(w[j,i], ' ');
    writeln;
  end;
end;

procedure imprimir_uma_linha (var w: matriz; m: integer; linha: integer;);
var j: integer;
begin
  for j := 1 to m do
    write(w[linha, j], ' ');
  writeln;
end;

procedure imprimir_uma_coluna (var w: matriz; n: integer; coluna: integer;);
var j: integer;
begin
  for j := 1 to n do
    writeln(w[j, coluna]);
end;

procedure imprimir_os_pares (var w: matriz; n,m: integer);
var i,j: integer;
begin
  for i := 1 to n do begin
    for j := 1 to m do
      if eh_par(w[i,j]) then // essa funçao verifica se é par, foi feita anteriormente
        write(w[i,j], ' '); 
  end;
  writeln;
end;

procedure imprimir_linha_e_colunas_pares (var w: matriz; n,m: integer);
var i,j: integer;
begin
  for i := 1 to n do begin
    for j := 1 to m do
      if eh_par(i) and eh_par(j) then
        write(w[i,j], ' ');
    writeln;
  end;
end;