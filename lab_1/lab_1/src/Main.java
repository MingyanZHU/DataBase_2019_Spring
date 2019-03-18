import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

class Employee {
    String ename, essn, address, super_ssn;
    int salary, dno;

    public Employee(String ename, String essn, String address, String super_ssn, int salary, int dno) {
        this.ename = ename;
        this.essn = essn;
        this.address = address;
        this.super_ssn = super_ssn;
        this.salary = salary;
        this.dno = dno;
    }

    @Override
    public String toString() {
        return ename + "\t" + essn + "\t" + address + "\t" + super_ssn + "\t" + salary + "\t" + dno;
    }
}

class Department {
    String dname, mgrssn, mgr_start_date;
    int dno;

    public Department(String dname, String mgrssn, String mgr_start_date, int dno) {
        this.dname = dname;
        this.mgrssn = mgrssn;
        this.mgr_start_date = mgr_start_date;
        this.dno = dno;
    }

    @Override
    public String toString() {
        return dname + "\t" + dno + "\t" + mgrssn + "\t" + mgr_start_date;
    }
}

class Project {
    String pname, plocation;
    int pno, dno;

    public Project(String pname, String plocation, int pno, int dno) {
        this.pname = pname;
        this.plocation = plocation;
        this.pno = pno;
        this.dno = dno;
    }

    @Override
    public String toString() {
        return pname + "\t" + pno + "\t" + plocation + "\t" + dno;
    }
}

class Works_on {
    String essn;
    int pno, hours;

    public Works_on(String essn, int pno, int hours) {
        this.essn = essn;
        this.pno = pno;
        this.hours = hours;
    }

    @Override
    public String toString() {
        return essn + "\t" + pno + "\t" + hours;
    }
}

public class Main {
    private static final int MAX_SALARY = 10000;
    private static final int BASE_SALARY = 1000;
    private static final int MAX_RELATIONS = 200;

    public static void main(String[] args) {
        Random random = new Random();

        List<Employee> employeeList = new ArrayList<>();
        List<String> locationList = new ArrayList<>();
        List<Department> departmentList = new ArrayList<>();
        List<Project> projectList = new ArrayList<>();

        try {
            // 获得项目列表
            BufferedReader bufferedReader = new BufferedReader(new FileReader("./source_file/department_name.txt"));
            String s;
            int count = 0;
            while ((s = bufferedReader.readLine()) != null) {
                departmentList.add(new Department(s, "", randomDateString(), ++count));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            // 获得工程列表
            BufferedReader bufferedReader = new BufferedReader(new FileReader("./source_file/project_name_location.txt"));
            String s;
            int count = 0;
            while ((s = bufferedReader.readLine()) != null) {
                String[] values = s.split(" ");
                projectList.add(new Project(values[0].replace("_", " "), values[1], ++count, random.nextInt(departmentList.size()) + 1));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            // 获得员工居住地址
            BufferedReader bufferedReader = new BufferedReader(new FileReader("./source_file/employee_location.txt"));
            String s;
            while ((s = bufferedReader.readLine()) != null) {
                locationList.add(s);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            // 获得员工姓名和身份证号
            BufferedReader bufferedReader = new BufferedReader(new FileReader("./source_file/employee_id.txt"));
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("./source_file/employees.txt"));

            String s;
            while ((s = bufferedReader.readLine()) != null) {
                String[] values = s.split(" ");
                int address = random.nextInt(locationList.size());
                employeeList.add(new Employee(values[0], values[1].replaceAll("\\s", ""), locationList.get(address)
                        , "", random.nextInt(MAX_SALARY) + BASE_SALARY, random.nextInt(departmentList.size()) + 1));
            }
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        for (Employee employee : employeeList) {
            int leader = random.nextInt(employeeList.size());
            employee.super_ssn = employeeList.get(leader).essn;
        }

        for (Department department : departmentList) {
            int leader = random.nextInt(employeeList.size());
            department.mgrssn = employeeList.get(leader).super_ssn;
        }


        Works_on[] works_ons = new Works_on[employeeList.size()];
        int count = 0;
        for (Employee employee : employeeList) {
            int hours = 6 + random.nextInt(6);
            int pid = random.nextInt(projectList.size());
            works_ons[count++] = new Works_on(employee.essn, projectList.get(pid).pno, hours);
        }

        try {
            BufferedWriter employeeWriter = new BufferedWriter(new FileWriter("./source_file/employees.txt"));
            for (Employee employee : employeeList)
                employeeWriter.write(employee.toString() + "\n");
            employeeWriter.close();

            BufferedWriter departmentWriter = new BufferedWriter(new FileWriter("./source_file/departments.txt"));
            for (Department department : departmentList)
                departmentWriter.write(department.toString() + "\n");
            departmentWriter.close();

            BufferedWriter projectWriter = new BufferedWriter(new FileWriter("./source_file/projects.txt"));
            for (Project project : projectList)
                projectWriter.write(project.toString() + "\n");
            projectWriter.close();

            BufferedWriter work_onWriter = new BufferedWriter(new FileWriter("./source_file/work_on.txt"));
            for (Works_on works_on : works_ons)
                work_onWriter.write(works_on.toString() + "\n");
            work_onWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String randomDateString() {
        Random rand = new Random();
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
        Calendar cal = Calendar.getInstance();
        cal.set(2004, 0, 1);
        long start = cal.getTimeInMillis();
        cal.set(2016, 0, 1);
        long end = cal.getTimeInMillis();
        Date d = new Date(start + (long) (rand.nextDouble() * (end - start)));
        return format.format(d);
    }
}
