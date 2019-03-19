import java.sql.*;
import java.util.Scanner;

public class Main {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/COMPANY";
    private static final String USER = "root";
    private static final String PASSWORD = "mysql";

    private static final String PARA_PNO = "%PNO%";
    private static final String PARA_SALARY = "%SALARY%";
    private static final String PARA_PNAME = "%PNAME";
    private static final String PARA_DNAME = "%DNAME";
    private static final String PARA_ENAME = "%ENAME%";
    private static final String PARA_N = "%N%";
    private static final String PARA_HOURS = "%HOURS%";

    private static final String[] queries = {"SELECT ESSN FROM WORKS_ON WHERE PNO = \"" + PARA_PNO + "\"",
            "SELECT ENAME FROM EMPLOYEE, WORKS_ON, PROJECT WHERE EMPLOYEE.ESSN = WORKS_ON.ESSN AND PROJECT.PNO = WORKS_ON.PNO AND PROJECT.PNAME = \"" + PARA_PNAME + "\"",
            "SELECT ENAME, ADDRESS FROM EMPLOYEE, DEPARTMENT WHERE EMPLOYEE.DNO = DEPARTMENT.DNO AND DEPARTMENT.DNAME = \"" + PARA_DNAME + "\"",
            "SELECT ENAME, ADDRESS FROM EMPLOYEE, DEPARTMENT WHERE EMPLOYEE.DNO = DEPARTMENT.DNO AND DEPARTMENT.DNAME = \"" + PARA_DNAME + "\" AND SALARY < " + PARA_SALARY,
            "SELECT ENAME FROM EMPLOYEE WHERE ESSN NOT IN (SELECT DISTINCT ESSN FROM WORKS_ON WHERE WORKS_ON.PNO =\"" + PARA_PNO + "\")",
            "SELECT ENAME, DNAME FROM EMPLOYEE, DEPARTMENT WHERE EMPLOYEE.DNO = DEPARTMENT.DNO AND EMPLOYEE.SUPERSSN IN (SELECT ESSN FROM EMPLOYEE WHERE ENAME = \"" + PARA_ENAME + "\")",
            "SELECT ESSN FROM WORKS_ON WHERE PNO = \"" + PARA_PNO + "1\" AND ESSN IN (SELECT ESSN FROM WORKS_ON WHERE PNO = \"" + PARA_PNO + "2\")",
            "SELECT DNAME FROM EMPLOYEE, DEPARTMENT WHERE EMPLOYEE.DNO = DEPARTMENT.DNO GROUP BY DEPARTMENT.DNO HAVING AVG(SALARY) < " + PARA_SALARY,
            "SELECT ENAME FROM EMPLOYEE, WORKS_ON WHERE EMPLOYEE.ESSN = WORKS_ON.ESSN GROUP BY EMPLOYEE.ESSN HAVING COUNT(PNO) >= " + PARA_N + " AND SUM(HOURS) <= " + PARA_HOURS};

    public static void main(String[] args) {
        Connection connection = null;
        Statement statement = null;
        Scanner cin = new Scanner(System.in);
        try {
            // 注册JDBC驱动
            Class.forName(JDBC_DRIVER);

            // 打开连接
            System.out.println("Connecting to MySql Server...");
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            if (!connection.isClosed()) {
                System.out.println("Connection Successful!");
                // 执行查询
                System.out.println("Instances Statement Object..."); // 实例化Statement对象
                statement = connection.createStatement();
                ResultSet resultSet = null;
                int count = 0;
                // Query 1
                String query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input pno:");
                String pno = cin.nextLine();
                query = query.replace(PARA_PNO, pno);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ESSN"));

                // Query 2
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input pname:");
                String pname = cin.nextLine();
                query = query.replace(PARA_PNAME, pname);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME"));

                // Query 3
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input dname:");
                String dname = cin.nextLine();
                query = query.replace(PARA_DNAME, dname);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("ADDRESS"));

                // Query 4
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input dname:");
                dname = cin.nextLine();
                System.out.println("Please input salary:");
                int salary = Integer.parseInt(cin.nextLine());
                query = query.replace(PARA_DNAME, dname).replace(PARA_SALARY, String.valueOf(salary));
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("ADDRESS"));

                // Query 5
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input pno");
                pno = cin.nextLine();
                query = query.replace(PARA_PNO, pno);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME"));

                // Query 6
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input ename");
                String ename = cin.nextLine();
                query = query.replace(PARA_ENAME, ename);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("DNAME"));

                // Query 7
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input pno1");
                pno = cin.nextLine();
                query = query.replace(PARA_PNO+1, pno);
                System.out.println("Please input pno2");
                pno = cin.nextLine();
                query = query.replace(PARA_PNO+2, pno);
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ESSN"));

                // Query 8
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input salary:");
                salary = Integer.parseInt(cin.nextLine());
                query = query.replace(PARA_SALARY, String.valueOf(salary));
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("DNAME"));

                // Query 9
                query = queries[count++];
                System.out.println("Query " + count);
                System.out.println("Please input n:");
                int n = Integer.parseInt(cin.nextLine());
                query = query.replace(PARA_N, String.valueOf(n));
                System.out.println("Please input salary:");
                int hours = Integer.parseInt(cin.nextLine());
                query = query.replace(PARA_HOURS, String.valueOf(hours));
                resultSet = statement.executeQuery(query);
                while (resultSet.next())
                    System.out.println(resultSet.getNString("ENAME"));


                resultSet.close();

            } else {
                System.out.println("Connection Failed, maybe mysql is close.");
                System.out.println("GoodBye~");
            }
        } catch (ClassNotFoundException | SQLException e) {
            // 处理JDBC错误 处理Class.forName错误
            e.printStackTrace();
        } finally {
            try {
                if (statement != null)
                    statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }

            try {
                if (connection != null)
                    connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
//
//P1
//SQL Project
//International Department
//International Department
//4000
//P2
//张红
//P1
//P2
//3000
//3
//8


