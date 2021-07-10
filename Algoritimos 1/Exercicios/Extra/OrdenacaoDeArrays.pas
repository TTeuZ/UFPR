program OrdenacaoDeArrays;
type vetor = array[1..200] of integer;
var vet: vetor;
    i: integer;

procedure ordena_vet(var vet: vetor; n: integer);
var j, aux: integer;
begin
  j := 1;
  while j <= n - 1 do begin
    if (vet[j] > vet[j+1]) then begin
      aux := vet[j+1];
      vet[j+1] := vet[j];
      vet[j] := aux;
    end;
    if (vet[j-1] > vet[j]) then begin
      aux := vet[j];
      vet[j] := vet[j-1];
      vet[j-1] := aux;
      j := j - 1;
    end else 
      j := j + 1;
  end;
end;

begin
  vet[1] := 9; vet[2] := 8; vet[3] := 7; vet[4] := 6; vet[5] := 2; vet[6] := 1;

  for i := 1 to 6 do begin
    write(vet[i], ' ');
  end;

  writeln(' ');

  ordena_vet(vet, 6);
  for i := 1 to 6 do begin
    write(vet[i], ' ');
  end;
  writeln(' ');
end.