select distinct(C_MKTSEGMENT) , count(C_MKTSEGMENT) 
from CUSTOMER 
group by C_MKTSEGMENT;
