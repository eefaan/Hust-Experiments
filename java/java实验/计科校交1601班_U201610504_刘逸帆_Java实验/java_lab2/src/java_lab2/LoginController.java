package java_lab2;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Stage;
import javafx.scene.input.KeyCode;

import java.sql.*;

public class LoginController {
    @FXML TextField account;
    @FXML PasswordField password;
    @FXML CheckBox doctor_set;
    @FXML CheckBox patient_set;
    @FXML Button login;

    /**
     * The constructor.
     * The constructor is called before the initialize() method.
     */
    public LoginController() {
    }

    /**
     * Initializes the controller class. This method is automatically called
     * after the fxml file has been loaded.
     */
    @FXML
    private void initialize() {
        patient_set.setSelected(true);
        doctor_set.setSelected(false);
        // set "enter" key for textfield
        account.setOnKeyPressed(keyEvent -> {
            if (keyEvent.getCode() == KeyCode.ENTER)
                password.requestFocus();
        });
        password.setOnKeyPressed(keyEvent -> {
            if (keyEvent.getCode() == KeyCode.ENTER)
                login.fire();
        });

        // initial the focus
        Platform.runLater(new Runnable(){
            @Override public void run(){
                account.requestFocus();
            }
        });
    }

    @FXML
    void click_doctor(){
        patient_set.setSelected(!patient_set.isSelected());
    }

    @FXML
    void click_patient(){
        doctor_set.setSelected(!doctor_set.isSelected());
    }

    @FXML
    void click_login(){
        // check account and password
        String account_input = account.getText();
        String password_input = password.getText();
        if(account_input.length() == 0 || password_input.length() == 0){// empty input
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("提示");
            alert.setHeaderText(null);
            alert.setContentText("账号或密码不得为空!");
            alert.showAndWait();
            return;
        }
        else {// check account and password
            System.out.print("account: "+account_input+"\n");
            System.out.print("password: "+password_input+"\n");
            try{
                String sql = "SELECT * FROM " + (patient_set.isSelected()?"T_BRXX ":"T_KSYS ") +
                             "WHERE " + (patient_set.isSelected()?"BRBH ":"YSBH ") + "= \'" + account_input + "\' " +
                             "AND DLKL = \'" + password_input +"\'";
                System.out.println(sql+"\n");
                ResultSet rs = Main.db_con.runQueryCommand(sql);
                if(!rs.next()){// login failed
                    Alert alert = new Alert(AlertType.INFORMATION);
                    alert.setTitle("提示");
                    alert.setHeaderText(null);
                    alert.setContentText("账号或密码错误!");
                    alert.showAndWait();
                    return;
                }
                else{
                    if(patient_set.isSelected()){
                        String name = rs.getString("BRMC");
                        // 输出数据
                        System.out.println("Login Success, BRMC: " + name +"\n");
                    }
                    else{
                        String name = rs.getString("YSMC");
                        // 输出数据
                        System.out.println("Login Success, YSMC: " + name +"\n");
                    }
                }
            }catch(Exception e){
                e.printStackTrace();
            }
        }

        // login success, close login window
        // // my DEBUG
        // Main.db_con.disconnectDB();
        // get a handle to the stage
        Stage stage = (Stage) login.getScene().getWindow();
        // do what you have to do
        // stage.close();

        // check login method
        if(patient_set.isSelected()){// login as patient
            try{
                Parent root = FXMLLoader.load(getClass().getResource("Patient.fxml"));
                root.requestFocus();
                stage.setTitle("Patient Control Center");
                stage.setScene(new Scene(root));
                stage.setUserData(account.getText());
                stage.show();
            }catch(Exception e){
                e.printStackTrace();
            }
        }
        else{// login as doctor
            try{
                Parent root = FXMLLoader.load(getClass().getResource("Doctor.fxml"));
                root.requestFocus();
                stage.setTitle("Patient Control Center");
                stage.setScene(new Scene(root));
                stage.setUserData(account.getText());
                stage.show();
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    }

}
