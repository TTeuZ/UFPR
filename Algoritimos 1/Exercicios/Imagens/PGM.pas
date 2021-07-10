program pgm;
const X = 50;
      limiar = 50;
type imagem = array[1..2000, 1..2000] of integer;
var O, D: imagem;   // matriz de Origem e matriz de Destino
    linO, colO, maxO,
    linD, colD, maxD: integer;


procedure ler_pgm (var O: imagem; var linha, coluna, max: integer);
var i, j: integer;
    s: string[2];
begin
  readln(s);
  if s = 'P2' then begin
    read(coluna, linha);
    read(max);
    for i := 1 to linha do 
      for j := 1 to coluna do
        read(O[i,j])
  end else writeln('Formato invalido');
end;

procedure imprimir_pgm (var O: imagem; linha, coluna, max: integer);
var i,j: integer;
begin
  writeln('P2');
  writeln(coluna, ' ', linha);
  writeln(max);
  for i := 1 to linha do begin
    for j := 1 to coluna-1 do
      write(O[i,j], ' ');
    writeln(O[i,coluna]);
  end;
end;

procedure clarear_pgm (var O: imagem; linha, coluna, max, cte: integer);
var i, j: integer;
begin
  for i := 1 to linha do begin
    for j :=1 to coluna-1 do begin
      O[i,j] := O[i,j] + cte;
      if O[i,j] > max then
        O[i,j] := max;
    end;
  end;
end;

function maior_valor (var O: imagem; linha, coluna: integer): integer;
var j, i, m: integer;
begin
  m := O[1,1];
  for i := 1 to linha do
    for j := 1 to coluna do
      if O[i,j] > m then
        m := O[i,j];
   maior_valor := m;
end;

function media_4_vizinhos (var O: imagem; i, j: integer): integer;
var x,y: integer;
begin
  x := 2*i - 1;
  y := 2*j - 1;
  media_4_vizinhos := (O[x,y] + O[x+1,y] + O[x,y+1] + O[x+1,y+1]) div 4;
end;

procedure zoom_pgm (var O: imagem; lO, cO: integer; var D: imagem; var lD, cD, maxD: integer);
var i,j: integer;
begin
  lD := lO div 2;
  cD := cO div 2;
  for i := 1 to lD do 
    for j := 1 to cD do
      D[i,j] := media_4_vizinhos(O, i, j);
  maxD := maior_valor(D, lD, cD);
end;

procedure detectar_bordas(var O, D: imagem; linha, coluna: integer; var max: integer);
var i, j, grad: integer;
begin
  // bordas recebem 0;
  for i := 1 to linha do begin
    D[i, 1] := 0;
    D[i,coluna] := 0;
  end;
  for i := 1 to coluna do begin
    D[1,i] := 0;
    d[linha,i] := 0;
  end;

  for i := 2 to linha-1 do 
    for j := 2to coluna -1 do begin
      grad := abs(O[i,j]*4 - (O[i-1,j] + O[i+1,j] + O[i,j-1] + O[i,j+1]));
      if grad > limiar then
        D[i,j] := 255
      else
        D[i,j] := 0;
    end;
    max := 255;
end;

begin
  ler_pgm(O, linO, colO, maxO);
//   clarear_pgm(O, linO, colO, maxO, X);
//   imprimir_pgm(O, linO, colO, maxO);
//   zoom_pgm(O, linO, colO, D, linD, colD, maxD);
  detectar_bordas(O, D, linO, colO, maxD);
  imprimir_pgm(D, linO, colO, maxD);
end.