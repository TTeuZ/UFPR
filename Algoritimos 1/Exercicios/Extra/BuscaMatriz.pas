program BuscaMatriz;
type matriz = array[1..50, 1..50] of integer;

function busca (var m: matriz; linha, coluna: integer; numero: integer;): boolean;
var i,j: integer;
    achou: boolean;
begin
  achou := false; i := 1;
  while (i <= linha) and not achou do begin
    j := 1;
    while (j <= coluna) and not achou do begin
      if m[i,j] = numero then
        achou := true;
      j := j + 1;
    end;
    i := i + 1;
  end;
  busca := achou;
end;

function busca2_0 (var m: matriz; linha, coluna, numero: integer; var linha_achou, coluna_achou: integer):boolean;
var i, j: integer;
    achou: Boolean;
begin
  achou := false; i := 1;
  while (i <= linha) and not achou do begin
    j := 1;
    while (j <= coluna) and not achou do begin
      if m[i,j] = numero then begin
        achou := true;
        linha_achou := i;
        coluna_achou := j;
      end;
    j := j + 1;
    end;
    i := i + 1;
  end;
  busca2_0 := achou;
end;

begin
end.