import org.apache.commons.cli.*;

import java.sql.*;
import java.util.Objects;


public class COMPANY_Query {
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/COMPANY";
    private static final String USER = "root";
    private static final String PASSWORD = "mysql";

    private static final String PARA_PNO = "%PNO%";
    private static final String PARA_SALARY = "%SALARY%";
    private static final String PARA_PNAME = "%PNAME%";
    private static final String PARA_DNAME = "%DNAME%";
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
        Options options = new Options();
        Option number = new Option("q", "number", true, "Number of paras");
        number.setRequired(true);
        options.addOption(number);

        Option para = new Option("p", "para", true, "Parameters");
        para.setArgs(Option.UNLIMITED_VALUES);
        para.setRequired(true);
        options.addOption(para);

        CommandLineParser parser = new DefaultParser();
        HelpFormatter formatter = new HelpFormatter();
        CommandLine cmd;
        try {
            cmd = parser.parse(options, args);
            int num = Integer.parseInt(cmd.getOptionValue("number"));
            String[] paras = cmd.getOptionValues("para");

//            System.out.println(num);
//            System.out.println(Arrays.toString(paras));

            Connection connection = null;
            Statement statement = null;
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
                    String query;
                    if (num == 1) {
                        // Query 1
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_PNO, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ESSN");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ESSN"));
                    } else if (num == 2) {
                        // Query 2
                        assert paras.length == 1;
                        query = queries[num - 1];
                        System.out.println("Query " + num);
                        query = query.replace(PARA_PNAME, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ENAME");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME"));
                    } else if (num == 3) {
                        // Query 3
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_DNAME, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ENAME");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("ADDRESS"));
                    } else if (num == 4) {
                        // Query 4
                        query = queries[num - 1];
                        assert paras.length == 2;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_DNAME, paras[0]).replace(PARA_SALARY, paras[1]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ENAME\tADDRESS");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("ADDRESS"));
                    } else if (num == 5) {
                        // Query 5
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_PNO, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ENAME");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME"));
                    } else if (num == 6) {
                        // Query 6
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_ENAME, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ENAME\tDNAME");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME") + "\t" + resultSet.getNString("DNAME"));
                    } else if (num == 7) {
                        // Query 7
                        query = queries[num - 1];
                        assert paras.length == 2;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_PNO + 1, paras[0]).replace(PARA_PNO + 2, paras[1]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("ESSN");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ESSN"));
                    } else if (num == 8) {
                        // Query 8
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_SALARY, paras[0]);
                        resultSet = statement.executeQuery(query);
                        System.out.println("DNAME");
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("DNAME"));
                    } else if (num == 9) {
                        // Query 9
                        query = queries[num - 1];
                        assert paras.length == 1;
                        System.out.println("Query " + num);
                        query = query.replace(PARA_N, paras[0]);
                        query = query.replace(PARA_HOURS, paras[1]);
                        System.out.println("ENAME");
                        resultSet = statement.executeQuery(query);
                        while (resultSet.next())
                            System.out.println(resultSet.getNString("ENAME"));
                    }


                    Objects.requireNonNull(resultSet).close();

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
        } catch (ParseException e) {
            System.out.println(e.getMessage());
            formatter.printHelp("utility-name", options);

            System.exit(1);
        }
    }
}
