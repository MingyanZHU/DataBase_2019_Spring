LOAD DATA
INFILE PrivateOwner.dat
APPEND INTO TABLE Privateowner
FIELDS TERMINATED BY ','
(ownerno,fname,lname,address,telno)