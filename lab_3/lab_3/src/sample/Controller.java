package sample;

import javafx.scene.control.TextArea;

import java.sql.ResultSet;
import java.sql.SQLException;

import static sample.Main.statement;

public class Controller {

    public TextArea Branch_Search_SQL_Input;
    public TextArea Branch_Search_Output;

    public void testButton() {
        try {
            String sql;
//            sql = "SELECT Staff_name FROM Staff";
            sql = Branch_Search_SQL_Input.getText();
            ResultSet rs = null;
            rs = statement.executeQuery(sql);
            StringBuilder stringBuilder = new StringBuilder();
            // 展开结果集数据库
            while (rs.next()) {
                // 通过字段检索
                String name = rs.getString("Staff_name");

                // 输出数据
//                System.out.println(name);
                stringBuilder.append(name).append("\n");
            }
//             完成后关闭
            rs.close();
            Branch_Search_Output.setText(stringBuilder.toString());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
