program Exercicio031;

var saldo: integer;
    credito: string;
begin
  read(saldo);

  if (saldo > 600) then
    credito := '40%'
  else
    begin
      if (saldo > 400) then
        credito := '30%'
      else
        begin
          if (saldo > 200) then
            credito := '20%'
          else
            credito := '0'
        end
    end;

  writeln(saldo);
  writeln(credito);
end.