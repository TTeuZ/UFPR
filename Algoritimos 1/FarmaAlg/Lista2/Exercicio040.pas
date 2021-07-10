program Exercicio040;

var numero, menorNumero, maiorNumero: longint;

begin
  read(numero);
  menorNumero := numero;
  maiorNumero := numero;
  while numero <> 0 do
    begin
      if menorNumero > numero then begin
        menorNumero := numero
      end;
      if numero > maiorNumero then begin
        maiorNumero := numero
      end;
      read(numero);
    end;

    writeln(maiorNumero, ' ', menorNumero);
end.