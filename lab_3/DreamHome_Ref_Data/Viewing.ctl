LOAD DATA
INFILE Viewing.dat
APPEND INTO TABLE viewing
FIELDS TERMINATED BY ','
(clientno,propertyno,viewdate,commnt)