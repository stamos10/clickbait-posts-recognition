import pymysql
import math


N = 10

def Main():

	try:
		connection=pymysql.connect(host='127.0.0.1', user='root', password='cessna172stam', database='bag_of_words', charset='utf8mb4', cursorclass=pymysql.cursors.DictCursor)
		cur=connection.cursor()
		cur.execute("select distinct Feature from data")
		features=cur.fetchall()
		for row in features:
			N11=cur.execute("Select count(distinct Document_id) from data where Feature=%s and Label='clickbait'",row['Feature'])
			N11=cur.fetchone()
			if N11 is not None:
				N11 = N11
			else:
				N11 = 0        
			cur.execute("Select count(distinct Document_id) from data where Feature <>%s and Label='clickbait'", row['Feature'],)
			N01=cur.fetchone()
			if N01 is not None:
				N01 = N01
			else:
				N01 = 0
			cur.execute("Select count(distinct Document_id) from data where Feature=%s and Label='no-clickbait'", row['Feature'])
			N10=cur.fetchone()
			if N10 is not None:
				N10 = N10
			else:
				N10 = 0
			cur.execute("Select count(distinct Document_id) from data where Feature<>%s and Label='no-clickbait'", row['Feature'])
			N00=cur.fetchone()
			if N00 is not None:
				N00 = N00
			else:
				N00 = 0
			cur.execute("Select count(distinct Document_id) from data where Feature =%s", row['Feature'])
			N1x=cur.fetchone()
			if N1x is not None:
				N1x = N1x
			else:
				N1x = 0
			cur.execute("Select count(distinct Document_id) from data where Label ='clickbait'")
			Nx1=cur.fetchone()
			if Nx1 is not None:
				Nx1 = Nx1
			else:
				Nx1 = 0
			cur.execute("Select count(distinct Document_id) from data where Feature <>%s", row['Feature'])
			N0x=cur.fetchone()
			if N0x is not None:
				N0x = N0x
			else:
				N0x = 0
			cur.execute("Select count(distinct Document_id) from data where Label ='no-clickbait'")
			Nx0=cur.fetchone()
			if Nx0 is not None:
				Nx0 = Nx0
			else:
				Nx0 = 0
			f_val=feature_selection(N11, N01, N10, N00, N1x, Nx1, N0x, Nx0)
			idf_val=inverse_document_frequency(N1x)
			cur.execute("insert into sweeper values (%s, %s, %s)", (row['Feature'], f_val, idf_val))
			print(row['Feature'], "Features value: ",f_val, "IDF Value: ", idf_val)
			connection.commit()
	except pymysql.Error as e:
		if(connection):
			print ("MySQL Error: %s", e)
			connection.rollback()
	finally:
		if(connection):
			connection.close()



def feature_selection(Naa, N0a, Na0, N00, N1x, Nx1, N0x, Nx0):
	a = 1
	b = 1
	c = 1
	d = 1
	e = 1
	f = 1
	g = 1
	h = 1
	w = 1
	z = 1
	y = 1
	x = 1
	
	if (Naa["count(distinct Document_id)"] > 0):
		a = N * int(Naa["count(distinct Document_id)"])
		w = int(Naa["count(distinct Document_id)"])
	if(N1x["count(distinct Document_id)"] > 0 and Nx1["count(distinct Document_id)"] > 0):	
		b = int(N1x["count(distinct Document_id)"]) * int(Nx1["count(distinct Document_id)"])
	if(N0a["count(distinct Document_id)"] > 0):	
		c = N * int(N0a["count(distinct Document_id)"])
		z = int(N0a["count(distinct Document_id)"])
	if(N0x["count(distinct Document_id)"] > 0 and Nx1["count(distinct Document_id)"] > 0):
		d = int(N0x["count(distinct Document_id)"]) * int(Nx1["count(distinct Document_id)"])
	if(Na0["count(distinct Document_id)"] > 0):
		e = N * int(Na0["count(distinct Document_id)"])
		y = int(Na0["count(distinct Document_id)"])
	if(N1x["count(distinct Document_id)"] > 0 and Nx0["count(distinct Document_id)"] > 0):
		f = int(N1x["count(distinct Document_id)"]) * int(Nx0["count(distinct Document_id)"])
	if(N00["count(distinct Document_id)"] > 0):
		g = N * int(N00["count(distinct Document_id)"])
		x = int(N00["count(distinct Document_id)"])
	if(N0x["count(distinct Document_id)"] > 0 and Nx0["count(distinct Document_id)"] > 0):
		h = int(N0x["count(distinct Document_id)"]) * int(Nx0["count(distinct Document_id)"])

	

	I = (w/N) * math.log(a / b, 2) + (z / N) * math.log(c / d, 2) + (y / N) * math.log(e / f, 2 ) + (x / N) * math.log(g / h, 2)
	I = float(I)
	return abs(I)


def inverse_document_frequency(input):

	if(input["count(distinct Document_id)"] > 0):	
		inp = int(input["count(distinct Document_id)"])
	idft = math.log(N/inp, 10)
	idft = float(idft)
	return idft




	

if __name__ == '__main__':
	Main()
