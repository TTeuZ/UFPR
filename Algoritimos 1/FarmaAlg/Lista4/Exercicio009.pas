program Exercicio009;

var pa, pb, ta, tb, popAAcres, popBAcres: double;
    count: integer;

begin
  read(pa,pb,ta,tb);
  count := 0;

  if pa > pb then begin
    if ta > tb then
      writeln(0)
    else begin
      while pa > pb do begin
        popAAcres := pa * ta;
        pa := pa + popAAcres;
        popBAcres := pb * tb;
        pb := pb + popBAcres;
        count := count + 1;
      end;
      writeln(count);
    end;
  end
  else begin
    if tb > ta then
      writeln(0)
    else begin
      while pb > pa do begin
        popAAcres := pa * ta;
        pa := pa + popAAcres;
        popBAcres := pb * tb;
        pb := pb + popBAcres;
        count := count + 1;
      end;
      writeln(count);
    end;
  end;
end.