program Exercicio055;

var n, numeroDeCasas, i, posicao, count: integer;
    m, m2, divisor: longint;

begin
  read(n, m);
  numeroDeCasas := 0;
  count := 0;
  posicao := 0;
  m2 := m;

  while m2 > 0 do begin
    m2 := m2 div 10;
    numeroDeCasas := numeroDeCasas + 1;
  end;

  while numeroDeCasas <> 0 do begin
    divisor := 1;
    for i := 1 to numeroDeCasas do begin
      divisor := divisor * 10;
    end;
    m2 := m;
    m2 := m2 mod divisor;
    m2 := m2 div (divisor div 10);
    
    if m2 = n then
      count := count + 1;

    m2 := m;
    posicao := posicao + 1;
    numeroDeCasas := numeroDeCasas - 1;
  end;

  if count = 0 then
    writeln('NAO')
  else
    writeln(count)
end.