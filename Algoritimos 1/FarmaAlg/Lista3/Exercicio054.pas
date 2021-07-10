program Exercicio054;

var mediaDosLados, antigoLado, count: integer;
    first, resultado: boolean;

begin
  read (mediaDosLados);
  first := true;
  resultado := true;

  while mediaDosLados <> 0 do begin
    count := count + 1;
    if first then begin
      antigoLado := mediaDosLados;
      first := false;
    end
    else begin
      if antigoLado = mediaDosLados then begin
        antigoLado := mediaDosLados;
      end
      else begin
        resultado := false;
        mediaDosLados := 0;
      end;
    end;
    read(mediaDosLados);
  end;

  if count >= 3 then begin
    if resultado then
      writeln('SIM')
    else
      writeln('NAO')
  end
  else 
    writeln('NAO')
end.