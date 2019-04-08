LOAD DATA
INFILE Branch.dat
APPEND INTO TABLE branch
FIELDS TERMINATED BY ','
(branchno,street,city,postcode)