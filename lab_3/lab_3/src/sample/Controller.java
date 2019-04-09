package sample;

import javafx.collections.FXCollections;
import javafx.event.Event;
import javafx.scene.control.*;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import static sample.Main.connection;
import static sample.Main.statement;

public class Controller {

    public Tab tabInputBranch = new Tab();
    public Tab tabInputStaff = new Tab();
    public Tab tabInputLease = new Tab();
    public Tab tabInputAd = new Tab();
    public ChoiceBox inputAdNewspaperName = new ChoiceBox();
    public ChoiceBox inputAdPropertyNo = new ChoiceBox();
    public TextField inputStaffNo = new TextField();
    public TextField inputStaffName = new TextField();
    public ChoiceBox inputStaffPosition = new ChoiceBox();
    public TextField inputStaffSuperior = new TextField();
    public TextField inputStaffSalary = new TextField();
    public ChoiceBox inputStaffBranch = new ChoiceBox();
    public Button inputStaffBut = new Button();
    public ChoiceBox inputStaffGender = new ChoiceBox();
    public TextField inputAdDate = new TextField();

    public TextField inputAdRent = new TextField();
    public Button inputAdAddBut = new Button();
    public TextField inputLeaseNo = new TextField();
    public ChoiceBox inputLeaseClientNo = new ChoiceBox();
    public ChoiceBox inputLeasePropertyNo = new ChoiceBox();
    public TextField inputLeaseRent = new TextField();
    public ChoiceBox inputLeaseWhetherDeposit = new ChoiceBox();
    public TextField inputLeaseDeposit = new TextField();
    public ChoiceBox inputLeasePayment = new ChoiceBox();
    public TextField inputLeaseLength = new TextField();
    public TextField inputLeaseStartDate = new TextField();
    public TextField inputLeaseEndDate = new TextField();
    public TextField inputBranchNo = new TextField();
    public TextField inputBranchStreet = new TextField();
    public TextField inputBranchCity = new TextField();
    public TextField inputBranchPostcode = new TextField();
    public Button inputBranchAddBut = new Button();
    public Button inputLeaseAdBut = new Button();
    public Tab tabDeleteBranch = new Tab();
    public ChoiceBox deleteBranchNo = new ChoiceBox();
    public Label deleteBranchStreet = new Label();
    public Label deleteBranchCity = new Label();
    public Label deleteBranchPostcode = new Label();
    public Button deleteBranchButton = new Button();
    public Button deleteBranchDetailButton = new Button();
    public ChoiceBox deleteStaffNo = new ChoiceBox();
    public TextArea deleteStaffContext = new TextArea();
    public Button deleteStaffDetailButton = new Button();
    public Button deleteStaffButton = new Button();
    public Tab tabDeleteStaff = new Tab();
    public Tab tabSearchBranch = new Tab();
    public ChoiceBox searchBranchCity = new ChoiceBox();
    public TextArea searchBranchAnswer = new TextArea();
    public Button searchBranchButton = new Button();
    public Tab overAverageAdProperty = new Tab();
    public TextArea overAverageAnswer = new TextArea();


    private void formatErrorAlert(String errorMessage) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Format Error");

        // alert.setHeaderText("Results:");
        alert.setContentText(errorMessage);

        alert.showAndWait();
    }

    private void constraintViolation(String errorMessage) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Constraint violation");

        // alert.setHeaderText("Results:");
        alert.setContentText(errorMessage);

        alert.showAndWait();
    }

    private void successAddTuple() {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Success Add Tuple");

        alert.setContentText("Success Add Tuple!!!");
        alert.showAndWait();
    }

    private void successDeleteTuple() {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Delete Successfully");
        alert.setContentText("删除成功!!!");
        alert.showAndWait();
    }

    public void BranchInputChanged(Event event) throws SQLException {
        if (tabInputAd.isSelected()) {
//            System.out.println("Choose Input Ad");
            String sql = "Select Name from Newspaper";

            ResultSet resultSet = statement.executeQuery(sql);
            List<String> newspaperName = new ArrayList<>();
            while (resultSet.next())
                newspaperName.add(resultSet.getString("Name"));
            inputAdNewspaperName.setItems(FXCollections.observableArrayList(newspaperName));
            resultSet.close();

            sql = "SELECT Property_no from PropertyForRent";
            resultSet = statement.executeQuery(sql);
            List<String> propertyNo = new ArrayList<>();
            while (resultSet.next())
                propertyNo.add(resultSet.getString("Property_no"));
            inputAdPropertyNo.setItems(FXCollections.observableArrayList(propertyNo));
            resultSet.close();

            inputAdDate.setPromptText("YYYY-MM-DD");
            inputAdRent.setPromptText("Positive Integer($)");
        } else if (tabInputLease.isSelected()) {
            inputLeaseNo.setPromptText("Rxx, xx is the number id");

            String sql = "SELECT Client_no from Client";
            ResultSet resultSet = statement.executeQuery(sql);
            List<String> clientNo = new ArrayList<>();
            while (resultSet.next())
                clientNo.add(resultSet.getString("Client_no"));
            inputLeaseClientNo.setItems(FXCollections.observableArrayList(clientNo));
            resultSet.close();

            sql = "select Property_no from PropertyForRent";
            resultSet = statement.executeQuery(sql);
            List<String> propertyNo = new ArrayList<>();
            while (resultSet.next())
                propertyNo.add(resultSet.getString("Property_no"));
            inputLeasePropertyNo.setItems(FXCollections.observableArrayList(propertyNo));
            resultSet.close();

            inputLeaseRent.setPromptText("Positive integer($/month)");
            inputLeaseDeposit.setPromptText("3 times of rent");
            inputLeaseLength.setPromptText("Using Day");
            inputLeaseStartDate.setPromptText("YYYY-MM-DD");
            inputLeaseEndDate.setPromptText("YYYY-MM-DD");

            inputLeasePayment.setItems(FXCollections.observableArrayList("Alipay", "Wechat", "cash", "Credit card"));
            inputLeaseWhetherDeposit.setItems(FXCollections.observableArrayList("Yes", "No"));
        } else if (tabInputStaff.isSelected()) {
            inputStaffNo.setPromptText("SXxx, X is capital, xx is number");
            inputStaffPosition.setItems(FXCollections.observableArrayList("Manager", "Assistant"));
            inputStaffGender.setItems(FXCollections.observableArrayList("M", "F", "X"));
            inputStaffSalary.setPromptText("Positive Number($)");

            String sql = "SELECT Branch_no from Branch";
            ResultSet resultSet = statement.executeQuery(sql);
            List<String> branchNo = new ArrayList<>();
            while (resultSet.next())
                branchNo.add(resultSet.getString("Branch_no"));
            inputStaffBranch.setItems(FXCollections.observableArrayList(branchNo));

        } else if (tabInputBranch.isSelected()) {
            inputBranchNo.setPromptText("Bxxx, xxx is number id");
        }
    }

    public void BranchDeleteChanged() throws SQLException {
        if (tabDeleteBranch.isSelected()) {
            String sql = "select Branch_no from Branch";
            ResultSet resultSet = statement.executeQuery(sql);
            List<String> branchNo = new ArrayList<>();
            while (resultSet.next())
                branchNo.add(resultSet.getString("Branch_no"));
            deleteBranchNo.setItems(FXCollections.observableArrayList(branchNo));
            resultSet.close();
        } else if (tabDeleteStaff.isSelected()) {
            String sql = "select * from Staff";
            ResultSet resultSet = statement.executeQuery(sql);
            List<String> branchNo = new ArrayList<>();
            while (resultSet.next())
                branchNo.add(resultSet.getString("Staff_no"));
            deleteStaffNo.setItems(FXCollections.observableArrayList(branchNo));
            resultSet.close();

            deleteStaffContext.setEditable(false);
        }
    }

    public void BranchSearchChanged() throws SQLException {
        if (tabSearchBranch.isSelected()) {
            String sql = "select DISTINCT City from Branch";
            ResultSet resultSet = statement.executeQuery(sql);
            List<String> cities = new ArrayList<>();
            while (resultSet.next())
                cities.add(resultSet.getString("City"));
            searchBranchCity.setItems(FXCollections.observableArrayList(cities));
            resultSet.close();

            searchBranchAnswer.setEditable(false);
        } else if (overAverageAdProperty.isSelected()){
            String sql = ""; // TODO 嵌套查询
//            ResultSet resultSet = statement.executeQuery(sql);
            constraintViolation("TODO!!!!");
            overAverageAnswer.setEditable(false);
        }
    }

    public void searchBranchButton() {
        String city = (String) searchBranchCity.getSelectionModel().getSelectedItem();
        String sql = "select * from Branch where City = \"" + city + "\"";
        try {
            ResultSet resultSet = statement.executeQuery(sql);
            int columns = resultSet.getMetaData().getColumnCount();
            StringBuilder builder = new StringBuilder();
            while (resultSet.next()){
                for(int i = 1;i<columns;i++){
                    builder.append(resultSet.getString(i) + "|");
                }
                builder.append("\n");
            }
            resultSet.close();
            searchBranchAnswer.setText(builder.toString());
        } catch (SQLException e) {
            constraintViolation(e.getMessage());
        }
    }

    public void DeleteBranchDetailButton() {
        String branch_no = (String) deleteBranchNo.getSelectionModel().getSelectedItem();
        String sql2 = "select * from Branch where Branch_no = \"" + branch_no + "\";";
        try {
            ResultSet resultSet1 = statement.executeQuery(sql2);
            while (resultSet1.next()) {
                deleteBranchCity.setText(resultSet1.getString("City"));
                deleteBranchPostcode.setText(resultSet1.getString("Postcode"));
                deleteBranchStreet.setText(resultSet1.getString("Street"));
            }
            resultSet1.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void DeleteStaffDetailButton() {
        String staff_no = (String) deleteStaffNo.getSelectionModel().getSelectedItem();
        String sql = "select * from Staff where Staff_no = \"" + staff_no + "\";";
        try {
            ResultSet resultSet = statement.executeQuery(sql);
            StringBuilder stringBuilder = new StringBuilder();
            while (resultSet.next()) {
                stringBuilder.append(resultSet.getString("Staff_no") + "\n");
                stringBuilder.append(resultSet.getString("Staff_name") + "\n");
                stringBuilder.append(resultSet.getString("Staff_position") + "\n");
                stringBuilder.append(resultSet.getString("Staff_superior") + "\n");
                stringBuilder.append(resultSet.getString("Staff_salary") + "\n");
                stringBuilder.append(resultSet.getString("Staff_branch") + "\n");
            }
            deleteStaffContext.setText(stringBuilder.toString());
        } catch (SQLException e) {
            e.getMessage();
        }
    }

    public void DeleteStaffButton() {
        String staff_no = (String) deleteStaffNo.getSelectionModel().getSelectedItem();
        String sql = "delete from Staff where Staff_no = ?";
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, staff_no);

            preparedStatement.execute();

            successDeleteTuple();
        } catch (SQLException e) {
            if (e.getMessage().contains("foreign"))
                constraintViolation("由于外键约束不能删除!");
            else
                constraintViolation(e.getMessage());
        }
    }

    public void DeleteBranchButton() {
        String branch_no = (String) deleteBranchNo.getSelectionModel().getSelectedItem();
        String sql = "delete from Branch where Branch_no = ?";
        try {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, branch_no);

            preparedStatement.execute();

            successDeleteTuple();
        } catch (SQLException e) {
            if (e.getMessage().contains("foreign"))
                constraintViolation("由于外键约束不能删除!");
            else
                constraintViolation(e.getMessage());
        }
    }

    public void AdInputAdd() {
        //        formatErrorAlert(newspaperName + " " + adDate + " "+ propertyNo + " " + adRent);

        String newspaperName = (String) inputAdNewspaperName.getSelectionModel().getSelectedItem();
        String adDate = inputAdDate.getText();
        String propertyNo = (String) inputAdPropertyNo.getSelectionModel().getSelectedItem();
        String adRent = inputAdRent.getText();
        try {
//            SimpleDateFormat format = new SimpleDateFormat("YYYY-MM-DD");
//            inputAdDate.setTextFormatter(new TextFormatter<>(new DateTimeStringConverter(format), format.parse("1970-12-31")));
            String sql = "insert into Advertisement (Newspaper_name, Ad_date, Property_no, Ad_rent)" +
                    "Values(?,?,?,?);";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, newspaperName);
            preparedStatement.setString(2, adDate);
            preparedStatement.setString(3, propertyNo);
            preparedStatement.setString(4, adRent);
            preparedStatement.executeUpdate();

            successAddTuple();
        } catch (SQLException e) {
            constraintViolation("Input Advertisement Failed!");
        }
//        catch (ParseException e) {
////            e.printStackTrace();
//            formatErrorAlert(Arrays.toString(new String[]{newspaperName, adDate, propertyNo, adRent}));
//        }
    }

    public void LeaseInputAdd() {
        String leaseNo = inputLeaseNo.getText();
        String clientNo = (String) inputLeaseClientNo.getSelectionModel().getSelectedItem();
        String propertyNo = (String) inputLeasePropertyNo.getSelectionModel().getSelectedItem();
        String rent = inputLeaseRent.getText();
        String deposit = inputLeaseDeposit.getText();
        String whether = ((String) inputLeaseWhetherDeposit.getSelectionModel().getSelectedItem()).substring(0, 1);
        String payment = (String) inputLeasePayment.getSelectionModel().getSelectedItem();
        String leaseLength = inputLeaseLength.getText();
        String leaseStartDate = inputLeaseStartDate.getText();
        String leaseEndDate = inputLeaseEndDate.getText();

        try {
            String sql = "insert into Lease (lease_no, client_no, property_no, rent, deposit, deposit_whether, payment, lease_length, lease_start_date, lease_end_date) " +
                    "VALUES (?,?,?,?,?,?,?,?,?,?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            preparedStatement.setString(1, leaseNo);
            preparedStatement.setString(2, clientNo);
            preparedStatement.setString(3, propertyNo);
            preparedStatement.setInt(4, Integer.valueOf(rent));
            preparedStatement.setInt(5, Integer.valueOf(deposit));
            preparedStatement.setString(6, whether);
            preparedStatement.setString(7, payment);
            preparedStatement.setString(8, leaseLength);
            preparedStatement.setString(9, leaseStartDate);
            preparedStatement.setString(10, leaseEndDate);

            preparedStatement.executeUpdate();

            successAddTuple();
        } catch (SQLException e) {
            constraintViolation(e.getMessage());
        } catch (NumberFormatException e) {
            formatErrorAlert("Rent " + rent + ", Deposit " + deposit);
        }
    }

    public void StaffInputAdd() {
        String staffNo = inputStaffNo.getText();
        String staffName = inputStaffName.getText();
        String staffPosition = (String) inputStaffPosition.getSelectionModel().getSelectedItem();
        String staffGender = (String) inputStaffGender.getSelectionModel().getSelectedItem();
        String staffSuperior = inputStaffSuperior.getText();
        String staffSalary = inputStaffSalary.getText();
        String staffBranch = (String) inputStaffBranch.getSelectionModel().getSelectedItem();

        try {
            String sql = "insert into Staff (Staff_no, Staff_name, Staff_position, Staff_gender, Staff_superior, Staff_salary, Staff_branch) " +
                    "values (?,?,?,?,?,?,?)";

            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            preparedStatement.setString(1, staffNo);
            preparedStatement.setString(2, staffName);
            preparedStatement.setString(3, staffPosition);
            preparedStatement.setString(4, staffGender);
            preparedStatement.setInt(6, Integer.valueOf(staffSalary));
            preparedStatement.setString(7, staffBranch);

            if (staffSuperior != null && staffBranch.length() != 0)
                preparedStatement.setString(5, staffSuperior);
            preparedStatement.executeUpdate();

            successAddTuple();
        } catch (SQLException e) {
            constraintViolation(e.getMessage());
        } catch (NumberFormatException e) {
            formatErrorAlert("Salary " + staffSalary);
        }
    }

    public void BranchInputAdd() {
        String branchNo = inputBranchNo.getText();
        String street = inputBranchStreet.getText();
        String city = inputBranchCity.getText();
        String postcode = inputBranchPostcode.getText();

        try {

            String sql = "insert into Branch (Branch_no, Street, City, Postcode) VALUES (?,?,?,?)";
            PreparedStatement preparedStatement = connection.prepareStatement(sql);

            preparedStatement.setString(1, branchNo);
            preparedStatement.setString(2, street);
            preparedStatement.setString(3, city);
            preparedStatement.setString(4, postcode);
            preparedStatement.executeUpdate();

            successAddTuple();
        } catch (SQLException e) {
            constraintViolation(e.getMessage());
        }
    }

}