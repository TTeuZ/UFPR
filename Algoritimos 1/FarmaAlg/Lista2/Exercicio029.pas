program Exercicio029;

var i: integer;
    a, b, c: real;

begin
  read(i, a, b, c);

  case i of
    1: begin
      if a > b then begin
        if b > c then begin
           write(c:0:0, ' ');
           write(b:0:0, ' ');
           writeln(a:0:0)
        end
        else begin
          write(b:0:0, ' ');
          if a > c then begin
            write(c:0:0, ' ');
            writeln(a:0:0);
          end
          else begin
            write(a:0:0, ' ');
            writeln(c:0:0);
          end;
        end;
      end
      else begin
        if a > c then begin
          write(c:0:0, ' ');
          write(a:0:0, ' ');
          writeln(b:0:0, ' ')
        end
        else begin
          write(a:0:0, ' ');
          if b > c then begin
            write(c:0:0, ' ');
            writeln(b:0:0);
          end
          else begin
            write(b:0:0, ' ');
            writeln(c:0:0);
          end;
        end;
      end;
    end;
    2: begin
      if a > b then begin
        if b > c then begin
           write(a:0:0, ' ');
           write(b:0:0, ' ');
           writeln(c:0:0)
        end
        else begin
          write(a:0:0, ' ');
          write(c:0:0, ' ');
          writeln(b:0:0);
        end;
      end
      else begin
        if a > c then begin
          write(b:0:0, ' ');
          write(a:0:0, ' ');
          writeln(c:0:0, ' ')
        end
        else begin
          if b > c then begin
            write(b:0:0, ' ');
            write(c:0:0, ' ');
            writeln(a:0:0);
          end
          else begin
            write(c:0:0, ' ');
            write(b:0:0, ' ');
            writeln(a:0:0);
          end;
        end;
      end;
    end;
    3: begin
      if a > b then begin
        if a > c then
          writeln(b:0:0, ' ', a:0:0, ' ', c:0:0)
        else
          writeln(a:0:0, ' ', c:0:0, ' ', b:0:0)
      end
      else begin
        if b > c then
          writeln(a:0:0, ' ', b:0:0, ' ', c:0:0)
        else 
          writeln(a:0:0, ' ', c:0:0, ' ', b:0:0)
      end;
    end;
  end;
end.