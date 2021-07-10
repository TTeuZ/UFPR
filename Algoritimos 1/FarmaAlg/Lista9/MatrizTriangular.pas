program MatrizTriangular;
type matriz = array[0..100, 0..100] of integer;
var m: matriz;
    n: integer;

procedure ler_matriz (var w: matriz; var n: integer);
var i,j: integer;
begin
  read(n);
  for i := 1 to n do
    for j := 1 to n do
      read(w[i,j])
end;

procedure imprimir_matriz (var w: matriz; n: integer);
var i,j: integer;
begin
  for i := 1 to n do begin
    for j := 1 to n do
      write(w[i,j], ' ');
    writeln;
  end;
end;

function triangular_superior (var m: matriz; n: integer): boolean;
var pos_diagonal, num, pos_linha: integer;
    triangular: boolean;
begin
  pos_diagonal := 2; triangular := true;
  while pos_diagonal <= n do begin
    pos_linha := pos_diagonal - 1;
    while (pos_linha > 0) and  triangular do begin
      num := m[pos_linha, pos_diagonal];
      if (num <> 0) then
        triangular := false;
      pos_linha := pos_linha - 1;
    end;
    pos_diagonal := pos_diagonal + 1;
  end;
  triangular_superior := triangular;
end;

function triangular_inferior (var m: matriz; n: integer): boolean;
var pos_diagonal, num, pos_linha: integer;
    triangular: boolean;
begin
  pos_diagonal := 0; triangular := true;
  while pos_diagonal <= n-1 do begin
    pos_linha := pos_diagonal + 1;
    while (pos_linha < n) and triangular do begin
      num := m[pos_linha, pos_diagonal];
      if (num <> 0) then
        triangular := false;
      pos_linha := pos_linha + 1;
    end;
    pos_diagonal := pos_diagonal + 1;
  end;
  triangular_inferior := triangular;
end;

procedure verifica_triangular (var m: matriz; n: integer);
begin
  if triangular_superior(m, n) then
    writeln('sim')
  else if triangular_inferior(m, n) then
    writeln('sim')
  else writeln('nao');
end;

begin
  ler_matriz(m, n);
  verifica_triangular(m, n);
end.