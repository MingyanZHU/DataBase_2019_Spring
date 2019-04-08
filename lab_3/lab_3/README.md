# 基本表
- 分公司表(Branch)(<u>公司编号(Branch_no)</u>, 街道(Street), 城市(City), 邮编(Postcode))
- 分公司电话表(Branch_Tel)(<u>公司编号(Branch_no)</u>, <u>电话号码(Tel)</u>)
- 员工表(Staff)(<u>员工编号(Staff_no)</u>, 员工名字(Staff_name), 职位(Staff_position), 员工性别(Staff_gender), 主管编号(Staff_superior), 员工工资(Staff_salary), 所在分公司(Staff_branch))
- 经理表(Manager)(<u>员工编号(Staff_no)</u>, 公司编号(Branch_no), 经理奖金(Manager_bonus), 经历任职日期(Manager_start))
- 出租的房产(PropertyForRent)(<u>Property_no</u>,Street,City,Postcode,Type,Rooms,Rent,Owner_no,Staff_no)
- 私人业主(PrivateOwner)(<u>Owner_no</u>,Name,Address,Tel_no)
- 企业业主(BusinessOwner)(<u>Owner_no</u>,Name,Address,Tel_no, Type, Contact)
- 客户(Client)(<u>Client_no</u>, name, Tel_no, Preftype, Maxrent)
- 报纸(Newspaper)(<u>Name</u>, Tel_no, Address, Contact_name)
- 广告(Advertisement)(<u>Newspaper_name</u>, <u>Ad_date</u>, Property_no, Ad_rent)
- 看房(Viewing)(<u>Client_no</u>,<u>Propertyno</u>,<u>View_date</u>,commnt)
- 租约(Lease)(<u>Lease_no</u>, Client_no, Property_no, Rent, Deposit, Deposit_whether, Payment, Lease_length, Lease_start, Lease_end)

# 参考
- [DreamHome_Ref_Data来源](http://www.ccs.neu.edu/home/ekanou/teaching/spring04/CSG102/dreamHome/)
