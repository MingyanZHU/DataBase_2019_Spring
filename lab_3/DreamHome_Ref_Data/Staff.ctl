LOAD DATA
INFILE Staff.dat
APPEND INTO TABLE staff 
FIELDS TERMINATED BY ','
(staffno,fname,lname,position,sex,dob,salary,branchno)