# php_bloom_filter
布隆过滤器是用来检索一个元素是否在一个集合中,由很长的二进制向量和一组映射函数组成，在爬虫或采集系统中可用于检索一个URL是否已经被访问到

# 安装和配置
-----
~~~
phpize
./configure [--enable-redis-igbinary]
make && make install
~~~

在php.ini中加入
~~~
extension=bloom_filter.so
~~~

# 一个简单的列子
~~~
$bloom = bloom_filter_create(5000);
bloom_filter_add($bloom,'http://localhost');
if(bloom_filter_check($bloom,'http://localhost')){
	echo 'in';
}else{
	echo 'not in';
}
bloom_filter_destory($bloom);
~~~


### bloom_filter_create
-----
_**Description**_: 创建一个布隆过滤器实例

##### *Parameters*
*INTEGER*: 长度，以字节为单位

##### *Return value*
*resource*: 资源，失败则返回NULL

##### *Example*
~~~
bloom_filter_create(5000);
~~~


### bloom_filter_add
-----
_**Description**_: 向布隆过滤器添加

##### *Parameters*
*resource*: 过滤器实例
*STRING*: 字符串

##### *Return value*
*BOOL*: true or false

##### *Example*
~~~
bloom_filter_check($bloom,'http://localhost');
~~~

