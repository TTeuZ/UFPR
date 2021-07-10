program RepeticaoEmMatriz;
type matriz = array[1..100, 1..100] of integer; 
var linhas, colunas: integer;
    m: matriz;

procedure ler_matriz (var w: matriz; var n,m: integer);
var i,j: integer;
begin
  read(n);
  read(m);
  for i := 1 to n do
    for j := 1 to m do
      read(w[i,j])
end;

function tem_repetido (var m: matriz; linhas, colunas: integer): Boolean;
var valor_atual, linha, coluna, count_linha, count_coluna: integer;
    repetiu: Boolean;
begin
  linha := 1; coluna := 1; count_linha := 1; count_coluna := 2; repetiu := false;
  while (linha <= linhas) and (coluna <= colunas) do begin
    valor_atual := m[linha, coluna];
    while (count_linha <= linhas) and not repetiu do begin
      while (count_coluna <= colunas) and not repetiu do begin
        if valor_atual = m[count_linha, count_coluna] then
          repetiu := true;
        count_coluna := count_coluna + 1;
      end;
      count_coluna := 1;
      count_linha := count_linha + 1;
    end;

    if (coluna < colunas) then begin
      coluna := coluna + 1;
      count_coluna := coluna + 1;
      count_linha := linha;
    end else begin
      coluna := 1;
      count_coluna := coluna + 1;
      linha := linha + 1;
      count_linha := linha;
    end;
  end;
  tem_repetido := repetiu;
end;

begin
  ler_matriz(m, linhas, colunas);
  if tem_repetido(m, linhas, colunas) then
    writeln('sim')
  else 
    writeln('nao');
end.