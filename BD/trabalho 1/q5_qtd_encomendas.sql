select   N_NAME, count(O_ORDERKEY) as ORDER_QTD
from     ORDERS, CUSTOMER, NATION
where    C_CUSTKEY = O_CUSTKEY and 
         N_NATIONKEY = C_NATIONKEY
group by N_NAME
order by ORDER_QTD desc;
