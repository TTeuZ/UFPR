program Exercicio01;

var 
    x, n1, n2, sinal, contador_sinal, qual_n: LongInt;
    r_1, r_2, divergencia: double;
    fatorial, i: longint;

begin
  read(x);
  n1 := 5; n2 := 6; sinal := 1; fatorial := 6; i := 4; contador_sinal := 1; qual_n := 1;
  r_1 := ((n1*x) / 1);
  r_2 := r_1 - ((n2*x / 2));
  divergencia := abs(r_2 - r_1);

  while (divergencia >= 0.001) do begin
    r_1 := r_2;

    if (contador_sinal <= 2) then begin
      sinal := 1;

      if (qual_n = 1) then begin
        n1 := n1 + 6;
        r_2 := r_1 + (sinal*((n1*x) / fatorial));
        qual_n := 2;
      end else begin
        n2 := n2 + 6;
        r_2 := r_1 + (sinal*((n2*x) / fatorial));
        qual_n := 1;
      end;

      contador_sinal := contador_sinal + 1;
    end
    else begin
      sinal := -1;

      if (qual_n = 1) then begin
        n1 := n1 + 6;
        r_2 := r_1 + (sinal*((n1*x) / fatorial));
        qual_n := 2;
      end else begin
        n2 := n2 + 6;
        r_2 := r_1 + (sinal*((n2*x) / fatorial));
        qual_n := 1;
      end;

      contador_sinal := 1;
    end;

    if i > 3 then begin
      fatorial := 1;
      i := 2;
    end else begin
      fatorial := fatorial * i;
      i := i + 1;
    end;

    divergencia := abs(r_2 - r_1);
  end;
  writeln(r_2:0:4);
end.