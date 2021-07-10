program QuadradoMagico1;
type matriz = array[0..100, 0..100] of integer;
var m: matriz;
    count, linhas, colunas, somatorio: integer;
    eh_magico: Boolean;

procedure ler_matriz (var w: matriz; var linhas, colunas: integer);
var i,j: integer;
begin
  read(linhas);
  colunas := linhas;
  for i := 1 to linhas do
    for j := 1 to colunas do
      read(w[i,j])
end;

function get_somatorio(var m: matriz; linha, colunas: integer): integer;
var i, somatorio: integer;
begin
  somatorio := 0;
  for i := 1 to colunas do 
    somatorio := somatorio + m[linha, i];
  get_somatorio := somatorio;
end;

function verifica_linha (var m: matriz; linha, colunas, somatorio: integer): Boolean;
var i, sum: integer;
begin
  sum := 0;
  for i := 1 to colunas do
    sum := sum + m[linha, i];
  if sum = somatorio then
    verifica_linha := true
  else
    verifica_linha := false;
end;

function verifica_coluna (var m: matriz; coluna, linhas, somatorio: integer): Boolean;
var i, sum: integer;
begin
  sum := 0;
  for i := 1 to linhas do
    sum := sum + m[i, coluna];
  if sum = somatorio then
    verifica_coluna := true
  else
    verifica_coluna := false;
end;

function verifica_diagonal (var m: matriz; qual, linhas, colunas, somatorio: integer): Boolean;
var i, j, sum, valor_atual: integer;
begin
  sum := 0;
  if qual = 1 then begin
    j := 1;
    for i:= 1 to linhas do begin
      valor_atual := m[i,j];
      sum := sum + valor_atual;
      j := j + 1;
    end;
    if sum = somatorio then
      verifica_diagonal := true
    else
      verifica_diagonal := false;
  end else begin
    j := colunas;
    for i := 1 to linhas do begin
      valor_atual := m[i,j];
      sum := sum + valor_atual;
      j := j - 1;
    end;
    if sum = somatorio then
      verifica_diagonal := true
    else
      verifica_diagonal := false;
  end;
end;

begin
  eh_magico := true;
  ler_matriz(m, linhas, colunas);
  somatorio := get_somatorio(m, 1, colunas);
  
  count := 2;
  while (count <= linhas) and eh_magico do begin
    eh_magico := verifica_linha(m, count, colunas, somatorio);
    count := count + 1;
  end;

  count := 1;
  while (count <= colunas) and eh_magico do begin
    eh_magico := verifica_coluna(m, count, linhas, somatorio);
    count := count + 1;
  end;

  count := 1;
  while (count <= 2) and eh_magico do begin
    eh_magico := verifica_diagonal(m, count, linhas, colunas, somatorio);
    count := count + 1;
  end;

  if eh_magico then
    writeln('sim')
  else 
    Writeln('nao');
end.