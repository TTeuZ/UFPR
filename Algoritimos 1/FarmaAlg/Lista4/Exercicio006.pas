program Exercicio006;

var k, count, numeros, sum, i: longint;
begin
  read(k);
  numeros := 6; count := 1; sum := 0;

  while count <= k do begin
    for i := 1 to (numeros - 1) do begin
      if numeros mod i = 0 then
        sum := sum + i;
    end;
    if sum = numeros then begin
      write(numeros, ' ');
      count := count + 1;
    end;
    numeros := numeros + 1;
    sum := 0;
  end;
end.