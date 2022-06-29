select      count(distinct(C_CUSTKEY)) 
from        ORDERS 
inner join  CUSTOMER on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY 
where       O_COMMENT like '%special request%' and 
            O_COMMENT not like '%unusual package%';
