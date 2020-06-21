package java_lab2;

import java.sql.*;

public class DBConnector {
    private Connection conn = null;
    private Statement stmt = null;

    public DBConnector() throws ClassNotFoundException {
        // 注册 JDBC 驱动
        Class.forName("com.mysql.jdbc.Driver");
        System.out.print("JDBC Driver Registed Success!\n");
    }

    public void connectDB(String hostName, Integer port, String dbName, String userName, String password){
        try{
            // 构造 DB 链接
            String url = "jdbc:mysql://" + hostName +
                         ":" + port +
                         "/" + dbName;
            // 打开链接
            System.out.println("Connecting DB...\n");
            conn = DriverManager.getConnection(url,userName,password);
            stmt = conn.createStatement();

            // my DEBUG
            String sql;
            sql = "SELECT BRBH, BRMC, DLKL, YCJE FROM T_BRXX";
            System.out.print(sql+"\n");
            ResultSet rs;
            rs = stmt.executeQuery(sql);
            // 展开结果集数据库
            while(rs.next()){
                // 通过字段检索
                String name = rs.getString("BRMC");
                // 输出数据
                System.out.print("name: " + name);
                System.out.print("\n");
            }
        }
        catch(SQLException se){
            // 处理 JDBC 错误
            se.printStackTrace();
        }
        catch(Exception e){
            // 处理 Class.forName 错误
            e.printStackTrace();
        }
    }

    public void disconnectDB(){
        try{
            stmt.close();
            conn.close();
            System.out.println("Goodbye!");
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public ResultSet runQueryCommand(String sql){
        try{
            // 执行查询
            return stmt.executeQuery(sql);
        }
        catch (SQLException e) {
            return null;
        }
    }

    public int runUpdateCommand(String sql) {
    	try {
    		return stmt.executeUpdate(sql);
    	}
    	catch (SQLException e) {
    		return -1;
    	}
    }

    public PreparedStatement createPS(String sql){
        try {
        	return conn.prepareStatement(sql);
        }
        catch (SQLException e) {
        	return null;
        }
    }
}
