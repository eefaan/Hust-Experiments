package java_lab2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Stage;

public class Main extends Application {
	public static DBConnector db_con = null;

	@Override
	public void start(Stage primaryStage) throws Exception{
		// Initialize connector
		try{
			if(db_con == null)
				db_con = new DBConnector();
			db_con.connectDB("localhost", 3306, "java_lab2", "java", "java");
		}
		catch(ClassNotFoundException ce){
			System.err.print("Cannot load sql driver. Details:\n");
			ce.printStackTrace();
            System.exit(1);
		}

        Parent root = FXMLLoader.load(getClass().getResource("Login.fxml"));
        primaryStage.setTitle("挂号管理系统");
		// Scene scene = new Scene(root, 300, 275);
        primaryStage.setMinWidth(400);
        primaryStage.setMinHeight(190);
		primaryStage.setScene(new Scene(root));
        primaryStage.show();
		// listen close button click event
		primaryStage.setOnCloseRequest(event->{
			System.out.println("closing from left-top button...\n");
			db_con.disconnectDB();
		});
	}

	public static void main(String[] args) {
		launch(args);
	}
}
