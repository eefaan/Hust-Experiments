package java_lab2;

import com.jfoenix.controls.*;
import com.jfoenix.controls.datamodels.treetable.RecursiveTreeObject;
import com.sun.javafx.robot.impl.FXRobotHelper;
import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.util.StringConverter;
import javafx.event.*;

import javafx.scene.control.*;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;


public class DoctorController {
    // Register Item Define
    private static final class Register extends RecursiveTreeObject<Register> {
        public StringProperty number;
        public StringProperty namePatient;
        public StringProperty dateTimeDisplay;
        public StringProperty isSpecialistDisplay;
        public Register(String number, String namePatient, Timestamp dateTime, boolean isSpec){
            this.number = new SimpleStringProperty(number);
            this.namePatient = new SimpleStringProperty(namePatient);
            this.dateTimeDisplay = new SimpleStringProperty(dateTime.toLocalDateTime().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss")));
            this.isSpecialistDisplay = new SimpleStringProperty(isSpec ? "专家号" : "普通号");
        }
    }

    // Income Item Define
    private static final class Income extends RecursiveTreeObject<Income> {
        public StringProperty departmentName;
        public StringProperty doctorNumber;
        public StringProperty doctorName;
        public StringProperty registerType;
        public StringProperty registerPopulation;
        public StringProperty incomeSum;
        public Income(String depName, String docNum, String docName, boolean isSpec, int regNumPeople, Double incomSum){
            this.departmentName = new SimpleStringProperty(depName);
            this.doctorNumber = new SimpleStringProperty(docNum);
            this.doctorName = new SimpleStringProperty(docName);
            this.registerType = new SimpleStringProperty(isSpec ? "专家" : "普通");
            this.registerPopulation = new SimpleStringProperty(Integer.toString(regNumPeople));
            this.incomeSum = new SimpleStringProperty(String.format("%.2f", incomSum));
        }
    }

    String doctorName = "";
    String doctorNum = "";

    @FXML private Label labelWelcome;
    @FXML private Label labelName;
    @FXML private Label labelAccount;
    @FXML private JFXDatePicker pickerDateStart;
    @FXML private JFXDatePicker pickerDateEnd;
    @FXML private JFXTimePicker pickerTimeStart;
    @FXML private JFXTimePicker pickerTimeEnd;

    @FXML private JFXTabPane mainPane;
    @FXML private Tab tabRegister;
    @FXML private Tab tabIncome;

    @FXML private JFXTreeTableView<Register> tableRegister;
    @FXML private TreeTableColumn<Register, String> columnRegisterNumber;
    @FXML private TreeTableColumn<Register, String> columnRegisterPatientName;
    @FXML private TreeTableColumn<Register, String> columnRegisterDateTime;
    @FXML private TreeTableColumn<Register, String> columnRegisterType;
    private TreeItem<Register> rootRegister;

    @FXML private JFXTreeTableView<Income> tableIncome;
    @FXML private TreeTableColumn<Income, String> columnIncomeDepartmentName;
    @FXML private TreeTableColumn<Income, String> columnIncomeDoctorNumber;
    @FXML private TreeTableColumn<Income, String> columnIncomeDoctorName;
    @FXML private TreeTableColumn<Income, String> columnIncomeRegisterType;
    @FXML private TreeTableColumn<Income, String> columnIncomeRegisterPopulation;
    @FXML private TreeTableColumn<Income, String> columnIncomeSum;
    private TreeItem<Income> rootIncome;

    private ObservableList<Register> listRegister = FXCollections.observableArrayList();
    private ObservableList<Income> listIncome = FXCollections.observableArrayList();

    @FXML JFXCheckBox checkBoxAllTime;
    @FXML JFXCheckBox checkBoxToday;
    @FXML JFXButton buttonFilter;
    @FXML JFXButton buttonExit;

    @FXML
    void initialize(){
        // set two date converter (formatter)
        pickerDateStart.setConverter(new DateConverter());
        pickerDateEnd.setConverter(new DateConverter());
        // default to current date
        pickerDateStart.setValue(LocalDate.now());
        pickerDateEnd.setValue(LocalDate.now());

        // set time selector to 24h
        pickerTimeStart.set24HourView(true);
        pickerTimeEnd.set24HourView(true);
        // default to 00:00 to 23:59
        pickerTimeStart.setValue(LocalTime.MIN);
        pickerTimeEnd.setValue(LocalTime.MAX);

        // initiailze register list
        columnRegisterNumber.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Register, String> param) -> param.getValue().getValue().number);
        columnRegisterPatientName.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Register, String> param) -> param.getValue().getValue().namePatient );
        columnRegisterDateTime.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Register, String> param) -> param.getValue().getValue().dateTimeDisplay );
        columnRegisterType.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Register, String> param) -> param.getValue().getValue().isSpecialistDisplay );

        rootRegister = new RecursiveTreeItem<>(listRegister, RecursiveTreeObject::getChildren);
        tableRegister.setRoot(rootRegister);
        tableRegister.setCenterShape(true);


        // template
        // listRegister.add(new Register("a", "b", new Timestamp(1000),true));
        columnIncomeDepartmentName.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().departmentName);
        columnIncomeDoctorNumber.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().doctorNumber);
        columnIncomeDoctorName.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().doctorName);
        columnIncomeRegisterType.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().registerType);
        columnIncomeRegisterPopulation.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().registerPopulation);
        columnIncomeSum.setCellValueFactory(
                (TreeTableColumn.CellDataFeatures<Income, String> param) -> param.getValue().getValue().incomeSum);

        rootIncome = new RecursiveTreeItem<>(listIncome, RecursiveTreeObject::getChildren);
        tableIncome.setRoot(rootIncome);

        Platform.runLater(new Runnable(){
            @Override public void run(){
                String sql = "";
                ResultSet rs = null;

                // initialize the welcome inform
                Stage stage = (Stage) labelWelcome.getScene().getWindow();
                doctorNum = (String) stage.getUserData();
                try{
                    sql = "SELECT * FROM T_KSYS " +
                                 "WHERE T_KSYS.YSBH = \'" + doctorNum + "\'";
                    rs = Main.db_con.runQueryCommand(sql);
                    if(!rs.next()){}
                    else{
                        doctorName = rs.getString("YSMC");
                        System.out.println("Login success, YSMC: " + doctorName);
                    }
                }catch(Exception e){
                    e.printStackTrace();
                }
                labelWelcome.setText(new String("欢迎您，"));
                labelName.setText(String.format("%s 医生！", doctorName));
                labelAccount.setText(String.format("您的工号是：%s", doctorNum));

                // initialize the page
                // buttonFilter.fire();
            }
        });
    }

    @FXML
    private void buttonFilterPressed() {
        if(mainPane.getSelectionModel().getSelectedItem() == tabRegister) {
            String sql = "";
            ResultSet rs = null;
            if(checkBoxAllTime.isSelected()){
                sql = "SELECT * FROM T_GHXX, T_BRXX, T_HZXX " +
                      "WHERE T_GHXX.YSBH = \'" + doctorNum + "\' " +
                      "AND T_GHXX.BRBH = T_BRXX.BRBH " +
                      "AND T_GHXX.HZBH = T_HZXX.HZBH";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            }
            else if(checkBoxToday.isSelected()){
                java.util.Date date = Calendar.getInstance().getTime();
                DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
                String strDate = dateFormat.format(date);
                sql = "SELECT * FROM T_GHXX, T_BRXX, T_HZXX " +
                      "WHERE T_GHXX.YSBH = \'" + doctorNum + "\' " +
                      "AND T_GHXX.RQSJ >= \'" + strDate + "\' " +
                      "AND T_GHXX.BRBH = T_BRXX.BRBH " +
                      "AND T_GHXX.HZBH = T_HZXX.HZBH";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            }
            else{
                String dateStart = pickerDateStart.getValue().format(DateTimeFormatter.ofPattern("yyyy-MM-dd")) +
                                    pickerTimeStart.getValue().format(DateTimeFormatter.ofPattern(" HH:mm:ss"));
                String dateEnd = pickerDateEnd.getValue().format(DateTimeFormatter.ofPattern("yyyy-MM-dd")) +
                                    pickerTimeEnd.getValue().format(DateTimeFormatter.ofPattern(" HH:mm:ss"));
                sql = "SELECT * FROM T_GHXX, T_BRXX, T_HZXX " +
                      "WHERE T_GHXX.YSBH = \'" + doctorNum + "\' " +
                      "AND T_GHXX.RQSJ >= \'" + dateStart + "\' " +
                      "AND T_GHXX.RQSJ <= \'" + dateEnd + "\' " +
                      "AND T_GHXX.BRBH = T_BRXX.BRBH " +
                      "AND T_GHXX.HZBH = T_HZXX.HZBH";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            }

            try {
                listRegister.clear();
                while (rs.next()) {
                    listRegister.add(new Register(
                        // TODO: getstring from resultSet
                        rs.getString("T_GHXX.GHBH"),
                        rs.getString("T_BRXX.BRMC"),
                        rs.getTimestamp("T_GHXX.RQSJ"),
                        rs.getBoolean("T_HZXX.SFZJ")
                    ));
                }
            } catch (SQLException e) {
                e.printStackTrace();
                return;
            }
        }
        else if (mainPane.getSelectionModel().getSelectedItem() == tabIncome) {
            String sql = "";
            ResultSet rs = null;
            if (checkBoxAllTime.isSelected()) {
                sql = "SELECT * FROM T_KSYS, T_GHXX, T_KSXX " +
                      "WHERE T_KSYS.YSBH = T_GHXX.YSBH " +
                      "AND T_KSYS.KSBH = T_KSXX.KSBH";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            } else if (checkBoxToday.isSelected()) {
                java.util.Date date = Calendar.getInstance().getTime();
                DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
                String strDate = dateFormat.format(date);
                sql = "SELECT * FROM T_KSYS, T_GHXX, T_KSXX " +
                      "WHERE T_KSYS.YSBH = T_GHXX.YSBH " +
                      "AND T_KSYS.KSBH = T_KSXX.KSBH " +
                      "AND T_GHXX.RQSJ >= \'" + strDate + "\' ";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            } else {
                String dateStart = pickerDateStart.getValue().format(DateTimeFormatter.ofPattern("yyyy-MM-dd")) +
                                    pickerTimeStart.getValue().format(DateTimeFormatter.ofPattern(" HH:mm:ss"));
                String dateEnd = pickerDateEnd.getValue().format(DateTimeFormatter.ofPattern("yyyy-MM-dd")) +
                                    pickerTimeEnd.getValue().format(DateTimeFormatter.ofPattern(" HH:mm:ss"));
                sql = "SELECT * FROM T_KSYS, T_GHXX, T_KSXX " +
                      "WHERE T_KSYS.YSBH = T_GHXX.YSBH " +
                      "AND T_KSYS.KSBH = T_KSXX.KSBH " +
                      "AND T_GHXX.RQSJ >= \'" + dateStart + "\' " +
                      "AND T_GHXX.RQSJ <= \'" + dateEnd + "\' ";
                System.out.println(sql);
                rs = Main.db_con.runQueryCommand(sql);
            }

            try {
                listIncome.clear();
                int flag = 0;
                String KSMC_temp = "";
                String YSBH_temp = "";
                String YSMC_temp = "";
                boolean HZLB_temp = false;
                int GHRC_temp = 0;
                double SRHJ_temp = 0;

                while (rs.next()) {
                    flag = 1;
                    if(YSBH_temp.equals("")){// initialize
                        KSMC_temp = rs.getString("T_KSXX.KSMC");
                        YSBH_temp = rs.getString("T_KSYS.YSBH");
                        YSMC_temp = rs.getString("T_KSYS.YSMC");
                        HZLB_temp = rs.getBoolean("T_KSYS.SFZJ");
                        GHRC_temp += 1;
                        SRHJ_temp += rs.getDouble("T_GHXX.GHFY");
                    }
                    else if(YSBH_temp.equals(rs.getString("T_KSYS.YSBH"))){// count the income
                        GHRC_temp += 1;
                        SRHJ_temp += rs.getDouble("T_GHXX.GHFY");
                    }
                    else{// insert last record to table and init those temp varables
                        listIncome.add(new Income(
                                KSMC_temp,
                                YSBH_temp,
                                YSMC_temp,
                                HZLB_temp,
                                GHRC_temp,
                                SRHJ_temp
                            )
                        );
                        KSMC_temp = rs.getString("T_KSXX.KSMC");
                        YSBH_temp = rs.getString("T_KSYS.YSBH");
                        YSMC_temp = rs.getString("T_KSYS.YSMC");
                        HZLB_temp = rs.getBoolean("T_KSYS.SFZJ");
                        GHRC_temp = 1;
                        SRHJ_temp = rs.getDouble("T_GHXX.GHFY");
                    }
                }
                if(flag == 1){
                    // insert the last record
                    listIncome.add(new Income(
                            KSMC_temp,
                            YSBH_temp,
                            YSMC_temp,
                            HZLB_temp,
                            GHRC_temp,
                            SRHJ_temp
                        )
                    );
                }
            } catch (SQLException e) {
                e.printStackTrace();
                return;
            }
        }
    }

    @FXML
    private void tabSelectionChanged(Event event) {
        if(((Tab)(event.getTarget())).isSelected());
    }

    @FXML
    private void buttonExitClicked() throws IOException {
        Scene scene = new Scene(FXMLLoader.load(getClass().getResource("Login.fxml")));
        FXRobotHelper.getStages().get(0).setScene(scene);
    }

    @FXML
    void checkBoxAllTimeSelected(){
        if (checkBoxAllTime.isSelected()) {
            checkBoxToday.setSelected(false);
            pickerDateStart.setDisable(true);
            pickerDateEnd.setDisable(true);
            pickerTimeStart.setDisable(true);
            pickerTimeEnd.setDisable(true);
        } else if (!checkBoxToday.isSelected()) {
            pickerDateStart.setDisable(false);
            pickerDateEnd.setDisable(false);
            pickerTimeStart.setDisable(false);
            pickerTimeEnd.setDisable(false);
        }
    }

    @FXML
    void checkBoxTodaySelected(){
        if (checkBoxToday.isSelected()) {
            checkBoxAllTime.setSelected(false);
            pickerDateStart.setDisable(true);
            pickerDateEnd.setDisable(true);
            pickerTimeStart.setDisable(true);
            pickerTimeEnd.setDisable(true);
        } else if(!checkBoxAllTime.isSelected()){
            pickerDateStart.setDisable(false);
            pickerDateEnd.setDisable(false);
            pickerTimeStart.setDisable(false);
            pickerTimeEnd.setDisable(false);
        }
    }

    @FXML
	private void logout_fire(){
		try{
			Stage oldstage = (Stage) buttonExit.getScene().getWindow();
			oldstage.close();

			Stage stage = new Stage();
			Parent root = FXMLLoader.load(getClass().getResource("Login.fxml"));
	        stage.setTitle("挂号管理系统");
	        stage.setMinWidth(400);
	        stage.setMinHeight(190);
			stage.setScene(new Scene(root));
	        stage.show();
			// listen close button click event
			stage.setOnCloseRequest(event->{
				System.out.println("closing from left-top button...\n");
				Main.db_con.disconnectDB();
			});
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}

class DateConverter extends StringConverter<LocalDate> {
    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    @Override
    public String toString(LocalDate localDate) {
        if(localDate != null){
            return formatter.format(localDate);
        } else {
            return "";
        }
    }

    @Override
    public LocalDate fromString(String s) {
        if(s != null && !s.isEmpty()) {
            return LocalDate.parse(s, formatter);
        } else {
            return null;
        }
    }
}
