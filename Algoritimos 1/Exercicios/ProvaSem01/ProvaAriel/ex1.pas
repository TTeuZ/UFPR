program ex1;
    var years: integer;
        weight, cornQtd: double;
begin
    years:= 0;
    cornQtd:= 150;
    weight:= cornQtd*0.001;

    while weight < 100000 do
    begin
        cornQtd:= cornQtd*0.9*2*150;
        weight:= cornQtd*0.001;
        years:= years + 1;        
    end;
    writeln(years);
end.