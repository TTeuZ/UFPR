program Exercicio062;

var saldo: real;
    count, i: integer;
    saldosNegativos: array[1..100] of real;

begin
  read(saldo);
  count := 0;
  while saldo <> 0 do begin
    if saldo < 0 then begin
      saldosNegativos[count] := saldo;
      count := count + 1;
    end;
    read(saldo);
  end;

  for i := 0 to (count - 1) do begin
    writeln(saldosNegativos[i]:0:2);
  end;
end.