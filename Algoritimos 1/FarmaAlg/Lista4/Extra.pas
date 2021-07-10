program Extra;

var n, a, a_anterior, maior_count, count, i: integer;

begin
  read(n);
  a_anterior := 0; count := 0;

  i := 1;
  while i <= n do begin
    read(a);
    if a > a_anterior then begin
      count := count + 1;
      maior_count := count;
    end
    else begin
      maior_count := count;
      count := 0;
    end;

    a_anterior := a;
    i := i + 1;
  end;
  writeln(maior_count);
end.