program ElementosNulos;
type matriz = array[1..100, 1..100] of real; // maneria de instanciar uma matriz, é um array de arrays
var linhas, colunas, linhas_nulas, colunas_nulas, count: integer;
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

function eh_linha_nula (var m: matriz; linha, colunas: integer): boolean;
var pos_coluna: integer;
    eh_vazia: boolean;
begin
  pos_coluna := 1; eh_vazia := true;
  while (pos_coluna <= colunas) and eh_vazia do begin
    if (m[linha, pos_coluna]) <> 0 then
      eh_vazia := false;
    pos_coluna := pos_coluna + 1;
  end;
  eh_linha_nula := eh_vazia;
end;

function eh_coluna_nula (var m: matriz; coluna, linhas: integer): Boolean;
var pos_linha: integer;
    eh_vazia: boolean;
begin
  pos_linha := 1; eh_vazia := true;
  while (pos_linha <= linhas) and eh_vazia do begin
    if (m[pos_linha, coluna]) <> 0 then
      eh_vazia := false;
    pos_linha := pos_linha + 1;
  end;
  eh_coluna_nula := eh_vazia;
end;

begin
  ler_matriz(m, linhas, colunas); linhas_nulas := 0; colunas_nulas := 0;
  for count := 1 to linhas do begin
    if eh_linha_nula(m, count, colunas) then
      linhas_nulas := linhas_nulas + 1;
  end;
  for count := 1 to colunas do begin
    if eh_coluna_nula(m, count, linhas) then
      colunas_nulas := colunas_nulas + 1;
  end;

  writeln('linhas: ', linhas_nulas);
  writeln('colunas: ', colunas_nulas);
end.