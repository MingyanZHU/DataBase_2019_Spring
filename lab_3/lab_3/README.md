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

# Branch视图(分公司视图)
## 数据录入
1. 录入一个新的分公司情况
2. 录入某个分公司中一名新员工的情况
3. 录入客户和房产之间新的租约情况
4. 录入在报纸上刊登广告的情况
## 数据删除
5. 删除某个分公司的情况
6. 删除工作在某个分公司的一名员工的情况
7. 删除给定租约的情况
8. 删除给定报纸的广告情况
## 数据查询
1. 列出给定城市所有分公司的情况
2. 按照员工名字的顺序, 列出给定分公司员工的名字,职务,工资和管理房产的总数.
3. 确定给定某个员工分管的房产总数
4. 列出刊登过广告的房产的详细情况
5. 列出由企业业主提供的房产的情况
6. 等等...

# Staff视图(员工视图)
## 数据录入
1. 录入某个待租的的新房产及其业主的情况
2. 录入一名新客户的情况
3. 录入一名客户查看房产的情况
4. 录入客户对房产签约的情况

## 数据删除
1. 删除一处房产的情况
2. 删除一名业主的情况
3. 删除一名客户的情况
4. 删除一名客户查看过一处房产的情况
5. 删除一份租约的情况

## 数据查询
1. 按字典序列出所有助理的情况
2. 列出没有给出评论的房产的情况
3. 等等...




# 参考
- [DreamHome_Ref_Data来源](http://www.ccs.neu.edu/home/ekanou/teaching/spring04/CSG102/dreamHome/)
