program Series002;

var numero, count: integer;
    soma: real;

begin
  read(numero);
  count := 1;

  while count < numero do begin
    soma := soma + ((numero - count) / (count));
    count := count + 1;
  end;

  writeln(soma:0:2);
end.