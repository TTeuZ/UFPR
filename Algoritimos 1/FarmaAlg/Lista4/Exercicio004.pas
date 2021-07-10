program Exercicio004;

var numero, m1, m2, fibo: integer;
    ehKeith: Boolean;

begin
  read(numero);
  m1 := numero div 10;
  m2 := numero mod 10;
 
  while fibo <= numero do begin
    fibo := m1 + m2;
    m1 := m2;
    m2 := fibo;
    if fibo = numero then
      ehKeith := true;
  end;

  if ehKeith then
    writeln('1')
  else
    writeln('0')
end.