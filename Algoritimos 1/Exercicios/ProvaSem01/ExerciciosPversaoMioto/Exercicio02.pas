program Exercicio02;

var number, big_number, count, big_count, divs: integer;

begin
  read(number);
  big_count := 0; big_number := 0;
  while number <> 0 do begin
    count := 1; divs := 1;
    while divs <= (number div 2) do begin
      if (number mod divs = 0) then
        count := count + 1;
      divs := divs + 1;
    end;
    
    if count > big_count then begin
       big_count := count;
       big_number := number;
    end;
    
    read(number);
  end;
  writeln(big_number);
end.