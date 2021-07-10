program Exercicio012;

var numero: longint;
    count: integer;

begin
  read(numero);

  while numero <> 0 do begin
    count := 1;
    while count <= 10 do begin
      write(numero * count, ' ');
      count := count + 1;
    end;
    read(numero);
  end;
end.