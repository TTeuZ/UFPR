program MDCEuclides;

var n1, n2, resto: integer;

begin
  read(a,b);

  if (a <> 0) and (b <> 0) then begin
    resto := a mod b;
    while resto <> 0 do begin
      a := b;
      b := resto;
      resto := a mod b;
    end;
    writeln('mdc: ', b);
  end;
end.