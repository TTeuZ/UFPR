program PermutacaoEmMatriz;
type matriz = array[0..100, 0..100] of integer;
var m: matriz;
    n, linhas, colunas, i: integer;
    eh_permuta: boolean;

procedure ler_matriz (var w: matriz; var n, linhas, colunas: integer);
var i,j: integer;
begin
  read(n);
  linhas := n; colunas := n;
  for i := 1 to n do
    for j := 1 to n do
      read(w[i,j])
end;

function verifica_coluna (var m: matriz; coluna, linha, linhas: integer): boolean;
var i: integer;
    possivel_permuta: boolean;
begin
  i := 1; possivel_permuta := true;
  while (i <= linhas) and possivel_permuta do begin
    if m[i, coluna] = 1 then begin 
      if i <> linha then
        possivel_permuta := false;
    end else if m[i, coluna] <> 0 then
      possivel_permuta := false;
    i := i + 1;
  end;
  verifica_coluna := possivel_permuta;
end;

function verifica_linha (var m: matriz; linha, linhas, colunas: integer): boolean;
var i, count: integer;
    possivel_permuta: boolean;
begin
  i := 1; possivel_permuta := true; count := 0;
  while (i <= colunas) and possivel_permuta do begin
    if m[linha, i] = 1 then begin
      possivel_permuta := verifica_coluna(m, i, linha, linhas);
      count := count + 1;
    end
    else if m[linha, i] <> 0 then
      possivel_permuta := false;
    i := i + 1;
  end;
  if count = 0 then
    possivel_permuta := false;
  verifica_linha := possivel_permuta;
end;

begin
  ler_matriz(m, n, linhas, colunas); eh_permuta := true; i := 1;
  while (i <= linhas) and eh_permuta do begin
    eh_permuta := verifica_linha(m, i, linhas, colunas);
    i := i + 1;
  end;

  if eh_permuta then
    writeln('sim')
  else 
    WriteLn('nao');
end.