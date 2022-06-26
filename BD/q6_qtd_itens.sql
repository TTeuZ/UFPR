select N_NAME, count(L_LINENUMBER) from LINEITEM inner join ORDERS on LINEITEM.L_ORDERKEY = ORDERS.O_ORDERKEY inner join CUSTOMER on ORDERS.O_CUSTKEY = CUSTOMER.C_CUSTKEY inner join NATION on CUSTOMER.C_NATIONKEY = NATION.N_NATIONKEY group by N_NAME order by count(O_ORDERKEY) desc limit 10;