program Exercicio057;  

var numero, maiorMultiplo: longint;

begin
  read(numero);
  maiorMultiplo := 0;

  while numero <> 0 do begin
    if (numero mod 7 = 0) then begin
      if numero > maiorMultiplo then
        maiorMultiplo := numero
    end;
    read(numero);
  end;
  writeln(maiorMultiplo);
end.