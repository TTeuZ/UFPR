program Exercicio048;

var a, b, multi: longint;

begin
  read(a, b);
  multi := 1;
  
  if (a mod 2 = 0) or (b mod 2 = 0) or (a > b) then 
    writeln('erro')
  else begin
    while a <= b do begin
      multi := multi * a;
      a := a + 2;
    end;
    writeln(multi);
  end;
end.