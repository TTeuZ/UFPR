program Vetores003;

type vetor = array[-1..200] of integer;
var vet1, vet2: vetor;
    n, i, j, valor: integer;
    ordenado: boolean;

begin
  read(n);
  i := 0; ordenado := true; vet1[-1] := -1000;

  if n = 0 then
    writeln('vetor vazio')
  else begin
    while i < n do begin
      read(valor);
      vet1[i] := valor;
      vet2[n-i] := valor;

      if vet1[i-1] > vet1[i] then begin
        ordenado := false;
      end;

      i := i + 1;
    end;

    if ordenado then
      writeln('sim')
    else
      writeln('nao');

    for j:= 1 to n do begin
      write(vet2[j], ' ');
    end;
    writeln(' ');
  end;
end.