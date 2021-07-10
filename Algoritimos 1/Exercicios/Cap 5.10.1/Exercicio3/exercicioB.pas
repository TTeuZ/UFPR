program exercicioB;

var p1, p2, y, z, r, w, a, b, resultado: real;

begin
  read(p1);
  read(p2);
  read(y);
  read(z);
  read(r);
  read(w);
  read(a);
  read(b);
  resultado := (((p1 + p2) / (y - z)) * r) / ((w / (a * b)) + r);
  writeln(resultado);
end.