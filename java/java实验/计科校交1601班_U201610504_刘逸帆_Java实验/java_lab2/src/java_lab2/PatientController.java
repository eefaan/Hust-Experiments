package java_lab2;

import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ComboBox;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Stage;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.InputEvent;

import java.sql.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class PatientController {
	@FXML ComboBox<String> ksmc;
    @FXML ComboBox<String> ysxm;
    @FXML ComboBox<String> hzlb;
    @FXML ComboBox<String> hzmc;
    @FXML TextField jkje;
    @FXML TextField yjje;
    @FXML TextField zlje;
    @FXML TextField ghhm;
    @FXML Button submit;
    @FXML Button clear;
    @FXML Button quit;

    private String ksmc_temp = "";
    private String ysxm_temp = "";
    private String hzlb_temp = "";
    private String hzmc_temp = "";

    /**
     * The constructor.
     * The constructor is called before the initialize() method.
     */
    public PatientController() {
    }


    @FXML
    private void initialize(){
        yjje.setEditable(false);
        zlje.setEditable(false);
        ghhm.setEditable(false);


        ksmc.setOnMouseClicked(mouseEvent -> {
        	set_ksmc();
        });
        ysxm.setOnMouseClicked(mouseEvent -> {
        	set_ysxm();
        });
        hzlb.setOnMouseClicked(mouseEvent -> {
        	set_hzlb();
        });
        hzmc.setOnMouseClicked(mouseEvent -> {
        	set_hzmc();
        });


        ksmc.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> arg0, String oldvalue,String newvalue) {
                if(newvalue!=null){
                    ksmc_temp = newvalue;
               	    // System.out.println(newvalue);
                }
                ksmc.getEditor().setText(ksmc_temp);
                ksmc.getEditor().positionCaret(ksmc.getEditor().getText().length());
            }
        });
        ysxm.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> arg0, String oldvalue,String newvalue) {
                if(newvalue!=null){
                    ysxm_temp = newvalue;
               	    // System.out.println(newvalue);
                }
                ysxm.getEditor().setText(ysxm_temp);
                ysxm.getEditor().positionCaret(ysxm.getEditor().getText().length());
            }
        });
        hzlb.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> arg0, String oldvalue,String newvalue) {
                if(newvalue!=null){
                    hzlb_temp = newvalue;
               	    // System.out.println(newvalue);
                }
                hzlb.getEditor().setText(hzlb_temp);
                hzlb.getEditor().positionCaret(hzlb.getEditor().getText().length());
                set_yjje();
				set_zlje();
            }
        });
        hzmc.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> arg0, String oldvalue,String newvalue) {
                if(newvalue!=null){
                    hzmc_temp = newvalue;
               	    // System.out.println(newvalue);
                }
                hzmc.getEditor().setText(hzmc_temp);
                hzmc.getEditor().positionCaret(hzmc.getEditor().getText().length());
                set_yjje();
				set_zlje();
            }
        });



        ksmc.setOnKeyReleased(keyEvent -> {
            if (keyEvent.getCode().isDigitKey() || keyEvent.getCode().isLetterKey() || keyEvent.getCode()==KeyCode.BACK_SPACE) {
                ksmc_temp = ksmc.getEditor().getText();
                ksmc.show();
                set_ksmc();
            }
        });
		ksmc.setOnKeyPressed(keyEvent -> {
			if (keyEvent.getCode() == KeyCode.ENTER)
                ysxm.requestFocus();
		});
        ysxm.setOnKeyReleased(keyEvent -> {
            if (keyEvent.getCode().isDigitKey() || keyEvent.getCode().isLetterKey() || keyEvent.getCode()==KeyCode.BACK_SPACE) {
                ysxm_temp = ysxm.getEditor().getText();
                ysxm.show();
                set_ysxm();
            }
        });
		ysxm.setOnKeyPressed(keyEvent -> {
			if (keyEvent.getCode() == KeyCode.ENTER)
                hzlb.requestFocus();
		});
        hzlb.setOnKeyReleased(keyEvent -> {
            if (keyEvent.getCode().isDigitKey() || keyEvent.getCode().isLetterKey() || keyEvent.getCode()==KeyCode.BACK_SPACE) {
                hzlb_temp = hzlb.getEditor().getText();
                hzlb.show();
                set_hzlb();
				// set_yjje();
            }
        });
		hzlb.setOnKeyPressed(keyEvent -> {
			if (keyEvent.getCode() == KeyCode.ENTER)
                hzmc.requestFocus();
		});
        hzmc.setOnKeyReleased(keyEvent -> {
            if (keyEvent.getCode().isDigitKey() || keyEvent.getCode().isLetterKey() || keyEvent.getCode()==KeyCode.BACK_SPACE) {
                hzmc_temp = hzmc.getEditor().getText();
                hzmc.show();
                set_hzmc();
				// set_yjje();
            }
        });
		hzmc.setOnKeyPressed(keyEvent -> {
			if (keyEvent.getCode() == KeyCode.ENTER)
                jkje.requestFocus();
		});
        jkje.setOnKeyReleased(keyEvent -> {
			if (keyEvent.getCode().isDigitKey() || keyEvent.getCode().isLetterKey() || keyEvent.getCode()==KeyCode.BACK_SPACE) {
				set_zlje();
			}
        });
		jkje.setOnKeyPressed(keyEvent -> {
			if (keyEvent.getCode() == KeyCode.ENTER)
                submit.fire();
		});

        Platform.runLater(new Runnable(){
            @Override public void run(){
                set_ksmc();
				System.out.println("run later");
				ksmc.requestFocus();
            }
        });
    }

    @FXML
    private void set_ksmc() {
    	try{
            String sql = "SELECT * FROM T_KSXX " +
                         "WHERE KSMC LIKE \'%" + ksmc.getEditor().getText() + "%\' " +
                         "OR PYZS LIKE \'%" + ksmc.getEditor().getText() + "%\'";
            System.out.println(sql);
            ResultSet rs = Main.db_con.runQueryCommand(sql);
            if(!rs.next()){// search failed
                // Do nothing but clear the items
                ksmc.getItems().clear();
            }
            else{
                // clear first
                ksmc.getItems().clear();
                // read the first record
                String item_ks_name = rs.getString("KSMC");
                System.out.print(item_ks_name + "\n");
                ksmc.getItems().addAll(item_ks_name);
                // read the rest records
                while(rs.next()){
                    item_ks_name = rs.getString("KSMC");
                    System.out.print(item_ks_name + "\n");
                    ksmc.getItems().addAll(item_ks_name);
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    @FXML
    private void set_ysxm() {
    	try{
            // get ksbh from ksmc(Combobox) and get ksys from T_KSYS
            String sql = "SELECT * FROM T_KSXX, T_KSYS " +
                         "WHERE T_KSXX.KSMC = \'" + ksmc.getEditor().getText() + "\' " +
						 "AND T_KSXX.KSBH = T_KSYS.KSBH";
            System.out.println(sql);
            ResultSet rs = Main.db_con.runQueryCommand(sql);
            if(!rs.next()) {
				// Do nothing but clear the items
                ysxm.getItems().clear();
            }
            else {
                // clear items first
                ysxm.getItems().clear();
                // read the first record
                String item_ks_name = rs.getString("T_KSYS.YSMC");
                System.out.print(item_ks_name + "\n");
                ysxm.getItems().addAll(item_ks_name);
                // read the rest records
                while(rs.next()){
                    item_ks_name = rs.getString("T_KSYS.YSMC");
                    System.out.print(item_ks_name + "\n");
                    ysxm.getItems().addAll(item_ks_name);
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

	// TODO: link YSMC with KSMC
    @FXML
    private void set_hzlb() {
    	try{
            // get ysbh
            String sql_ysbh = "SELECT * FROM T_KSYS " +
                              "WHERE YSMC = \'" + ysxm.getEditor().getText() + "\'";
            System.out.println(sql_ysbh+"\n");
            ResultSet rs = Main.db_con.runQueryCommand(sql_ysbh);
            if(!rs.next()){// search failed
                // Do nothing but clear the items
                hzlb.getItems().clear();
            }
            else{
				// clear items first
                hzlb.getItems().clear();
                int item_ks_name = rs.getInt("SFZJ");
                System.out.print(item_ks_name + "\n");
                if(item_ks_name==1)
                    hzlb.getItems().addAll("专家号");
                hzlb.getItems().addAll("普通号");
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    @FXML
    private void set_hzmc() {
    	try{
            // get ksbh from ksmc(Combobox) and get hzmc from T_HZXX
            String sql = "SELECT * FROM T_KSXX, T_HZXX " +
                         "WHERE KSMC = \'" + ksmc.getEditor().getText() + "\' " +
						 "AND T_HZXX.SFZJ = \'" + (hzlb.getEditor().getText().equals("专家号")?"1":"0") + "\' " +
						 "AND T_KSXX.KSBH = T_HZXX.KSBH " +
						 "AND (T_HZXX.HZMC LIKE \'%" + hzmc.getEditor().getText() + "%\' " +
                         "OR T_HZXX.PYZS LIKE \'%" + hzmc.getEditor().getText() + "%\')";
            System.out.println(sql);
            ResultSet rs = Main.db_con.runQueryCommand(sql);
            if(!rs.next()) {
                hzmc.getItems().clear();
            }
            else{
				// clear items first
                hzmc.getItems().clear();
                // get the first record
                String item_ks_name = rs.getString("T_HZXX.HZMC");
                System.out.print(item_ks_name + "\n");
                hzmc.getItems().addAll(item_ks_name);
                // get the rest records
                while(rs.next()){
                    item_ks_name = rs.getString("T_HZXX.HZMC");
                    System.out.print(item_ks_name + "\n");
                    hzmc.getItems().addAll(item_ks_name);
                }
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    // TODO: use hzlb(ComboBox) and hzmc(ComboBox) to calculate the yjje
    // TODO _ branch: change hzmc to the same for sp or not_sp
    @FXML
    private void set_yjje(){
        try{
            // get sfzj from hzlb(combobox), get ghxx from hzmc(combobox), and then do query
            String sql = "SELECT * FROM T_HZXX " +
                         "WHERE SFZJ = \'" + (hzlb.getEditor().getText().equals("专家号")?"1":"0") + "\' " +
                         "AND HZMC = \'" + hzmc.getEditor().getText() + "\' ";
            System.out.println(sql);
            ResultSet rs = Main.db_con.runQueryCommand(sql);
            if(!rs.next()){// search failed
                // Do nothing but clear the items
                yjje.clear();
            }
            else{
				yjje.clear();
            	yjje.setText(String.valueOf(rs.getFloat("GHFY")));
            }
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    // TODO: read the JKJE and then calculate the refund
	@FXML
	private void set_zlje(){
		if(jkje.getText().equals("") || yjje.getText().equals("")){
			zlje.clear();
			return;
		}
		float zlje_float = Float.parseFloat(jkje.getText()) - Float.parseFloat(yjje.getText());

		zlje_float = (float)(Math.round(zlje_float*100))/100;

		zlje.clear();
		if (zlje_float>=0) {
			zlje.setText(String.valueOf(zlje_float));
		}
		else {
			zlje.setText("支付金额不足");
		}
	}

    // TODO: button submit. clear. logout. 's function
    // TODO _ branch: submit may make notify "cannot submit cause not exist" or "purchase failed"
	@FXML
	private void submit_fire(){
		float yjje_new;
		try{
			// JUDGE if the insert is legal STEP 1 (valid text)
			String sql = "";
			sql = "SELECT * FROM T_KSXX, T_KSYS, T_HZXX " +
				  "WHERE T_KSXX.KSMC = \'" + ksmc.getEditor().getText() + "\' " +
				  "AND T_KSXX.KSBH = T_HZXX.KSBH " +
				  "AND T_KSYS.YSMC = \'" + ysxm.getEditor().getText() + "\' " +
				  "AND T_KSYS.KSBH = T_HZXX.KSBH " +
				  "AND T_HZXX.HZMC = \'" + hzmc.getEditor().getText() + "\' " +
				  (hzlb.getEditor().getText().equals("专家号") ?
				  "AND T_KSYS.SFZJ = 1 AND T_HZXX.SFZJ = 1" :
				  "AND T_HZXX.SFZJ = 0");
		    System.out.println(sql);
			ResultSet rs = Main.db_con.runQueryCommand(sql);
			if(!rs.next()){// T_HZXX search failed
				Alert alert = new Alert(AlertType.INFORMATION);
				alert.setTitle("提示");
				alert.setHeaderText(null);
				alert.setContentText("无此号种，检查输入是否规范或医生资格是否不足!");
				alert.showAndWait();
				return;
			}
			else{
				yjje_new = rs.getFloat("GHFY");
			}

			// JUDGE if the GHRC is limited
			// initialize data of record
			String ghbh_string = "";
			String hzbh_string = "";
			String ysbh_string = "";
			String brbh_string = "";
			int ghrc = 0;
			int thbz = 0;
			float ghfy = 0;
			// assign ghbh_string
			sql = "SELECT * FROM T_GHXX ORDER BY GHBH DESC LIMIT 1";
			System.out.println(sql);
			rs = Main.db_con.runQueryCommand(sql);
			if(!rs.next()){
				// is the first GHXX
				ghbh_string = "000001";
			}
			else{
				// or the last one, then add one
				String append [] = new String[]{"00000","0000","000","00","0",""};
				String last_string = rs.getString("GHBH");
				int int_id =  Integer.parseInt(last_string.substring(1));
				ghbh_string = String.valueOf(int_id + 1);
				ghbh_string = append[ghbh_string.length()-1] + ghbh_string;
				// my DEBUG
				System.out.println(ghbh_string);
			}
			// assign hzbh_string
			sql = "SELECT * FROM T_HZXX " +
				  "WHERE HZMC = \'" + hzmc.getEditor().getText() + "\'" +
				  "AND SFZJ = " + (hzlb.getEditor().getText().equals("专家号")?"1":"0");
			rs = Main.db_con.runQueryCommand(sql);
			if(!rs.next()){}
			else{hzbh_string = rs.getString("HZBH");}
			// assign ysbh_string
			sql = "SELECT * FROM T_KSYS " +
				  "WHERE YSMC = \'" + ysxm.getEditor().getText() + "\'";
			rs = Main.db_con.runQueryCommand(sql);
			if(!rs.next()){}
			else{ysbh_string = rs.getString("YSBH");}
			// assign brbh_string
			Stage stage = (Stage) submit.getScene().getWindow();
			brbh_string = (String) stage.getUserData();
			// assign ghrc
			java.util.Date date = Calendar.getInstance().getTime();
			DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
			String strDate = dateFormat.format(date);
			sql = "SELECT MAX(GHRC) FROM T_GHXX " +
				  "WHERE HZBH = \'" + hzbh_string + "\' " +
				  "AND YSBH = \'" + ysbh_string + "\' " +
				  "AND BRBH = \'" + brbh_string + "\' " +
				  "AND RQSJ >= \'" + strDate + "\'";
			System.out.println(sql);
			rs = Main.db_con.runQueryCommand(sql);
			rs.next();
			ghrc = rs.getInt(1) + 1;
			System.out.println("ghrc: " + ghrc);
			sql = "SELECT * FROM T_HZXX " +
				  "WHERE HZBH = \'" + hzbh_string + "\'";
			System.out.println(sql);
			rs = Main.db_con.runQueryCommand(sql);
			rs.next();
			int temp_max = rs.getInt("GHRS");
			if(ghrc > temp_max){
				Alert alert = new Alert(AlertType.INFORMATION);
	            alert.setTitle("提示");
	            alert.setHeaderText(null);
	            alert.setContentText("当日挂号人次已满!");
	            alert.showAndWait();
				return;
			}
			// assign thbz
			thbz = 0;
			// assign ghfy
			ghfy = Float.parseFloat(yjje.getText());
			// assign date_submit
			java.util.Date date_submit = new java.util.Date();
			java.sql.Timestamp datetime_submit = new java.sql.Timestamp(date_submit.getTime());

			// JUDGE if the insert is legal STEP 3 (purchase success?) purchase with cash or GET YCJE
			if(!yjje.getText().equals(String.valueOf(yjje_new))){
				// the yjje has been changed, user should be alarmed
				Alert alert = new Alert(AlertType.INFORMATION);
	            alert.setTitle("提示");
	            alert.setHeaderText(null);
	            alert.setContentText("应缴金额发生了变化!");
	            alert.showAndWait();
	            return;
			}

			// get balance
	        String account = (String) stage.getUserData();
	        float balance = 0;
			sql = "SELECT * FROM T_BRXX " +
				  "WHERE T_BRXX.BRBH = \'" + account + "\'";
			rs = Main.db_con.runQueryCommand(sql);
			if(!rs.next()){
				// Do nothing
			}
			else{
				balance = rs.getFloat("YCJE");
				System.out.println("balance: " + String.valueOf(balance));
			}
			// purchase with wallet or jkje
			if(jkje.getText().equals("")){
				// if input is "", purchase with wallet
				// JUDEG if the balance is sufficient
				if(balance >= Float.parseFloat(yjje.getText())){
					// if the balance is sufficient
					balance -= Float.parseFloat(yjje.getText());
					sql = "UPDATE T_BRXX " +
						  "SET YCJE = " + Float.toString(balance) + " " +
						  "WHERE BRBH = \'" + account + "\'";
				    System.out.println(sql);
					int i = Main.db_con.runUpdateCommand(sql);
					Alert alert = new Alert(AlertType.INFORMATION);
		            alert.setTitle("提示");
		            alert.setHeaderText(null);
		            alert.setContentText("挂号成功!");
		            alert.showAndWait();
				}
				else{
					// or balance unfit
					Alert alert = new Alert(AlertType.INFORMATION);
		            alert.setTitle("提示");
		            alert.setHeaderText(null);
		            alert.setContentText("账户余额不足!");
		            alert.showAndWait();
		            return;
				}
			}
			else{
				if(Float.parseFloat(jkje.getText()) >= Float.parseFloat(yjje.getText())){
					// purchase with JKJE
					Alert alert = new Alert(AlertType.INFORMATION);
		            alert.setTitle("提示");
		            alert.setHeaderText(null);
		            alert.setContentText("挂号成功!");
		            alert.showAndWait();
				}
				else{
					// or balance unfit
					Alert alert = new Alert(AlertType.INFORMATION);
		            alert.setTitle("提示");
		            alert.setHeaderText(null);
		            alert.setContentText("支付金额不足!");
		            alert.showAndWait();
					return;
				}
			}

			// purchase done. INSERT To DATABASE and then set_ghhm
			// INSERT Record
			sql = "INSERT INTO T_GHXX (ghbh, hzbh, ysbh, brbh, ghrc, thbz, ghfy, rqsj) " +
				  "VALUES(?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement ps = Main.db_con.createPS(sql);
            ps.setString(1, ghbh_string); // ghbh
            ps.setString(2, hzbh_string); // hzbh
            ps.setString(3, ysbh_string); // ysbh
            ps.setString(4, brbh_string); // brbh
            ps.setInt(5, ghrc); // ghrc
            ps.setInt(6, thbz); // thbz
            ps.setFloat(7, ghfy); // ghfy
            ps.setTimestamp(8, datetime_submit); // rqsj
            ps.executeUpdate();
            System.out.println("添加成功！");

			ghhm.setText(ghbh_string);
		}catch(Exception e){
			e.printStackTrace();
		}
	}

	@FXML
	private void clear_fire(){
		// clear the cache
		ksmc_temp = "";
	    ysxm_temp = "";
	    hzlb_temp = "";
	    hzmc_temp = "";
		// clear the textfield
		ksmc.getEditor().clear();
		ysxm.getEditor().clear();
		hzlb.getEditor().clear();
		hzmc.getEditor().clear();
		jkje.clear();
		yjje.clear();
		zlje.clear();
		ghhm.clear();
		// clear the items
		ksmc.getItems().clear();
		ysxm.getItems().clear();
		hzlb.getItems().clear();
		hzmc.getItems().clear();
	}

	@FXML
	private void logout_fire(){
		try{
			Stage oldstage = (Stage) quit.getScene().getWindow();
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
