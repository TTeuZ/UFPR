program proc2 (input, output);   
   procedure p(a, b: integer);
      var c: integer;    
      procedure q(a, b: integer);
         var c: integer;
         begin
            c := 4;
            write(a, b, c);   
         end;
      begin
         c := 1;          
         write(a, b, c);     
         q(6, 5);        
      end;                       
begin                     
   p(3, 2);
end. 
