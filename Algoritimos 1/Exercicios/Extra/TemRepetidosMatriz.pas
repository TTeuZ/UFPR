program TemRepetidosMatriz;
type matriz = array[1..50, 1..50] of integer;

function tem_repetidos (var m: matriz; linha, coluna: integer;): boolean;
var i, j, p, q: integer;
    repetiu: Boolean;
begin
  repetiu := false; i := 1;
  while (i <= linha) and not repetiu do begin
    j := 1;
    while (j <= coluna) and not repetiu do begin
      p := 1;
      while (p <= linha) and not repetiu do begin
        q := 1;
        while (q <= coluna) and not repetiu do begin
          if (m[p,q] = m[i,j]) and ((p <> i) or (q <> j)) then
            repetiu := true;
          q := q + 1;
        end;
        p := p + 1;
      end;
      j := j + 1;
    end;
    i := i + 1;
  end;
  tem_repetidos := repetiu;
end;

begin
end.

// possivel melhora de codigo:
// nao olhar para oq ue ja passou, no caso da posição i,j, sempre começar a analise de posiçoes a frente dela.