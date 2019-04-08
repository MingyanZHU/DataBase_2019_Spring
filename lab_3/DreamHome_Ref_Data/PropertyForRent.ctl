LOAD DATA
INFILE PropertyForRent.dat
APPEND INTO TABLE propertyforrent
FIELDS TERMINATED BY ','
(propertyno,street,city,postcode,type,rooms,rent,ownerno,staffno,branchno)