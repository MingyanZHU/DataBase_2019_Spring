LOAD DATA
INFILE Client.dat
APPEND INTO TABLE client
FIELDS TERMINATED BY ','
(clientno,fname,lname,telno,preftype,maxrent)