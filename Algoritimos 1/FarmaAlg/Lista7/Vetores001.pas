program Vetores001;

var n, count:integer;
    vetor: array[0..200] of real;
    numerador, denominador, resultado: double;
begin
  read(n);
  count := 0; numerador := 0; denominador := 0;


  while count <= (n - 1) do begin
    read(vetor[count]);

    if (count = 0) or (count mod 2 = 0) then begin
      if (vetor[count] > 0) then
        numerador := numerador + vetor[count]
    end else begin
      if (vetor[count] < 0) then
        denominador := denominador + vetor[count]
    end;

    count := count + 1;
  end;

  if n = 0  then
    writeln('vetor vazio')
  else if denominador = 0 then
    writeln('divisao por zero') 
  else begin
    resultado := numerador / denominador;
    writeln(resultado:0:2);
  end;
end.