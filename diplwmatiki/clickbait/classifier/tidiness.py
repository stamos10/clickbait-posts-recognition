import pymysql
import math

# gia N=10 selection_score >-0.10703893278913983 kai idf <1.1
def Main():

	try:
		connection=pymysql.connect(host='127.0.0.1', user='root', password='cessna172stam', database='bag_of_words', charset='utf8mb4', cursorclass=pymysql.cursors.DictCursor)
		cur=connection.cursor()
		cur.execute("select * from sweeper where selection_score > -0.10703893278913983 and idf < 1.1")
		features=cur.fetchall()
		for row in features:
			cur.execute("select * from data where Feature = %s", row['feature'])
			old_data = cur.fetchall()
			for row_b in old_data:
				cur.execute("insert into final_data values(%s, %s, %s, %s,  %s)",(row_b['Document_id'], row_b['Feature'], row_b['Section'], row_b['Num'], row_b['Label']))
				print(row_b['Feature'])
				connection.commit()


	except pymysql.Error as e:
		if(connection):
			print ("MySQL Error: %s", e)
			connection.rollback()
	finally:
		if(connection):
			connection.close()






	

if __name__ == '__main__':
	Main()
