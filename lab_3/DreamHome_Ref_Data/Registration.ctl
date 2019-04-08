LOAD DATA
INFILE Registration.dat
APPEND INTO TABLE registration
FIELDS TERMINATED BY ','
(clientno,branchno,staffno,datejoined)