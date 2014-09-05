# php_bloom_filter
��¡����������������һ��Ԫ���Ƿ���һ��������,�ɺܳ��Ķ�����������һ��ӳ�亯����ɣ��������ɼ�ϵͳ�п����ڼ���һ��URL�Ƿ��Ѿ������ʵ�

# ��װ������
-----
~~~
phpize
./configure [--enable-redis-igbinary]
make && make install
~~~

��php.ini�м���
~~~
extension=bloom_filter.so
~~~

# һ���򵥵�����
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
_**Description**_: ����һ����¡������ʵ��

##### *Parameters*
*INTEGER*: ���ȣ����ֽ�Ϊ��λ

##### *Return value*
*resource*: ��Դ��ʧ���򷵻�NULL

##### *Example*
~~~
bloom_filter_create(5000);
~~~


### bloom_filter_add
-----
_**Description**_: ��¡���������

##### *Parameters*
*resource*: ������ʵ��
*STRING*: �ַ���

##### *Return value*
*BOOL*: true or false

##### *Example*
~~~
bloom_filter_check($bloom,'http://localhost');
~~~

