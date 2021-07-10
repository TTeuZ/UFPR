program Ex1M2;

var anos: integer;
    peso, graos: double;

begin
  anos := 0;
  peso := 0.150;
  graos := 150;

  while peso < 100000 do begin
    graos := graos + (graos*0.9*2*150);
    peso := peso + (graos*0.001);
    anos := anos + 1;
  end;
  WriteLn(anos);
end.