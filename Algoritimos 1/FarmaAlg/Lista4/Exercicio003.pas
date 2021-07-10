program Exercicio003;

var numero, numeroAnterior: longint;
    first, serie: boolean;

begin
  read(numero);
  numeroAnterior := 0; first := true; serie := true;

  while numero <> 0 do begin
    if first then begin
      numeroAnterior := numero;
      first := false;
    end
    else begin
      numeroAnterior := numeroAnterior * numeroAnterior;
      if numero = numeroAnterior then
        first := true
      else
        serie := false
    end;
    read(numero);
  end;

  if first then
    writeln('1')
  else
    writeln('0')
end.