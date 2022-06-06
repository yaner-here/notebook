# Java代码审计
# §2 注入
## §2.1 SQL注入
JDK自带`java.sql.*`包用于建立与SQL的连接。然而SQL种类多种多样，有`Microsoft SQL`、`MySQL`、`MariaDB`、`PostrageSQL`、`SQLite`等，它们被开发时用的语言不同，唯一的共同点是遵循SQL语法，因此仅凭这一个软件包还不够，必须使用各大SQL厂商各自开发的`.jar`格式的`Driver`。
### §2.1.1 原生JDBC
```Java
import java.sql.*;  

public class DatabaseConnector {  
    
    private Connection connection; 
     
    private void open() throws SQLException {  
        connection = DriverManager.getConnection( // 指定数据库端口、用户名、密码
                "jdbc:mariadb://localhost:3306",  
                "admin","admin"  
        );
        if(connection.isValid(5)){ // 判断连接是否成功/超时
            System.out.println("Success");  
        }else{  
            System.out.println("TimeOut");  
        }
        connection.close(); // 关闭连接
    }
    
    public static void main(String[] args){  
        DatabaseConnector connector = new DatabaseConnector();  
        try{  
            connector.open();
	            // 导入jar包时
	            // Success
        }catch (SQLException e){  
            e.printStackTrace();
	            // 未导入jar包时
	            // java.sql.SQLException:
	            // No suitable driver found for jdbc:mariadb://localhost:3306
        }  
    }  
    
}
```
滥用字符串拼接会导致SQL注入：
```java
public class DatabaseConnector{
    // ...
	private void queryByName(String name) throws SQLException {  
	    String sqlCommand = "select * from user where name = " + name;  
	    Statement statement = connection.createStatement(); // 更改ResultSet的特性  
	    ResultSet resultSet = statement.executeQuery(sqlCommand); // Statement实例只能使用一次，生成一个ResultSet实例
	    while(resultSet.next()){  
	        System.out.println("id:" + resultSet.getObject("id"));  
	        System.out.println("name:" + resultSet.getObject("name"));  
	    }  
	}
}
```
`PreparedStatement`类支持替换SQL语句字符串中的占位符`?`，其内部的`setInt()`、`setString()`等方法会对参数进行严格的类型检查和转换，以避免SQL注入：
```java
public class DatabaseConnector{
	// ...
	private void QueryByName_safe(String name) throws SQLException {
		String sqlCommand = "select * from user where name = ?";  
		PreparedStatement preparedStatement = connection.prepareStatement(sqlCommand); // PreparedStatement实例可重复使用，批量生成ResultSet实例
		preparedStatement.setString(1,name); // 将name转换为String，并用其替换第一个占位符
		ResultSet resultSet = preparedStatement.executeQuery();  
// ...
	}
}
```
### §2.1.2 MyBatis框架
`MyBatis`是一个`JDBC`的抽象封装框架，其核心思想是将SQL语句从源文件移动到配置文件中，从而避免源文件出现大量的SQL语句，提高源文件可维护性。其模版大致如下：
```xml
<mapper namespace="UserInfoSection">
	<select id="queryByName" resultType="String" parameterType="String">
		select * from user where name = #{name}
	</select>
</mapper>
```
```java
import org.apache.ibatis.session.SqlSession

public class UserInfoSection {

	private SqlSession sqlSession;

	public UserInfoSection(SqlSession sqlSession){
		this.sqlSession = sqlSession;
	}

	public String queryByName(String name){
		return 
			"id:" +
			this.sqlSession.selectOne("DatabaseConnector.queryByName",name) +
			"name:" +
			name;
	}

}
```
XML中可以使用两种不同的传参方式：`${Parameter}`和`#{Parameter}`。`${Parameter}`采用字符串拼接的方式，会造成SQL注入；而`#{Parameter}`采用预编译的方式，不会有安全风险。在使用`MyBatis`框架的时候应格外注意选择哪种传参方式。
### §2.1.3 Hibernate框架
`Hibernate`框架是一种满足Java持久化API（Java Persistence API，JPA）要求的框架。其它语言传统的SQL查询方式，是将数据库信息通过值传递，赋给目标编程语言的某个实例。而JPA将数据库中的对象**实时**映射到某个实例。例如某次查询之后，数据库的值发生改变，则JPA最终输出的是新的值。
Hibernate使用的不是SQL，而是HQL，二者逻辑相似，但语法上略有区别：
```java

class QueryUserInfo {

	public QueryUserInfo(String parameter){
		Configuration config = new Configuration().configure();
		SessionFactory factory = config.buildSessionFactory();
		Session session = factory.openSession();
		try{
			Transction transction = session.beginTransction();
			String HqlCommand = "FROM USER WHERE NAME = '" + parameter + "'";
			List users = session.createQuery(HqlCommand,User.class).getResultList();
			Iterator iterator = users.iterator();
			while(iterator.hasNext()){
				User user = (User) iterator.next();
				System.out.println(user.toString());
			}
		}catch(HibernateException e){
			if(transaction != null){ transaction.rollback(); }
		}finally{
			session.close();
		}
	}

	public static void main(String[] args){
		QueryUserInfo("abc' or '1'='1"); // HQL注入
	}

}
```
可以使用HQL参数绑定的方式规避该问题：
+ 位置参数
  ```java
  Query<User> query = session.createQuery("FROM USER WHERE NAME = ?1",User.class);
  query.setParameter("name",parameter); // String parameter;
  ```
+ 命名参数