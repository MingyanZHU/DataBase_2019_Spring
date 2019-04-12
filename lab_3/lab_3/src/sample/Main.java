package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.sql.*;
import java.util.Objects;

public class Main extends Application {

    // JDBC 驱动名及数据库 URL
    private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/DreamHome";

    // 数据库的用户名与密码，需要根据自己的设置
    private static final String USER = "root";
    private static final String PASS = "mysql";

    public static Connection connection;
    public static Statement statement;

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("DreamHome");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show();
    }

    public static void main(String[] args) {
        try {
            // 注册 JDBC 驱动
            Class.forName(JDBC_DRIVER);

            // 打开链接
            System.out.println("连接数据库...");
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            // 执行查询

            if (!connection.isClosed()) {
                System.out.println("Connection Successful!");

                System.out.println(" 实例化Statement对象...");
                statement = connection.createStatement();

                launch(args);
            }
            statement.close();
            connection.close();
        } catch (Exception se) {
            // 处理 JDBC 错误
            se.printStackTrace();
        }// 处理 Class.forName 错误
        finally {
            // 关闭资源
            try {
                if (statement != null) statement.close();
            } catch (SQLException ignored) {
            }// 什么都不做
            try {
                if (connection != null) connection.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
        System.out.println("Goodbye!");
    }
}
