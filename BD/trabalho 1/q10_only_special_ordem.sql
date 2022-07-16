select      count(distinct(C_CUSTKEY))
from (
    select      distinct(C_CUSTKEY)
    from        ORDERS
    inner join  CUSTOMER on O_CUSTKEY = C_CUSTKEY 
    where       O_COMMENT like '%special request%'
    except
    select      distinct(C_CUSTKEY)
    from        ORDERS
    inner join  CUSTOMER on O_CUSTKEY = C_CUSTKEY 
    where       O_COMMENT like '%unusual package%'
);