program Exercicio010;

var numero, i, mult: integer;
    triangular: boolean;

begin
  read(numero);
  i := 0; mult := 0; triangular := false;

  while (mult <= numero) and not triangular do begin
    mult := i * (i + 1) * (i + 2);

    if mult = numero then
      triangular := true;
      
    i := i + 1;
  end;

  if triangular then
    writeln('1')
  else
    writeln('0')
end.