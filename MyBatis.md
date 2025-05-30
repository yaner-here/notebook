参考资料：

- [《MyBatis核心技术全解与项目实战》](https://book.douban.com/subject/36799172/)

# §1 基础语法

MyBatis提供了一个JDBC的轻量级封装，是一个半自动的ORM框架。开发者无需手动注册驱动、维护Connection和Statement对象等等。而Hibernate是一个JDBC的重量级封装，是一个全自动的ORM框架。虽然功能完善，但是无法操作底层SQL，而HQL到SQL的转译会产生较大开销，因此学习曲线陡峭。